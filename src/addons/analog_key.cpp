#include "addons/analog_key.h"
#include "storagemanager.h"
#include "helper.h"
#include "config.pb.h"

#include "enums.pb.h"

#include "hardware/adc.h"


bool AnalogKeyAddon::available() {
  return Storage::getInstance().getAddonOptions().analogKeyOptions.enabled;
}

void AnalogKeyAddon::setup() {
  const AnalogKeyOptions& analogKeyOptions = Storage::getInstance().getAddonOptions().analogKeyOptions;

  for (uint8_t i = 0; i < MUX_SELECTOR_BITS; i++) {
    gpio_init(muxSelectorPins[i]);
		gpio_set_dir(muxSelectorPins[i], GPIO_OUT);
  }

	adc_gpio_init(MUX_PIN);
	adc_select_input(MUX_PIN - 26);
	gaussLUT.init(GAUSS_CORRECTION_PARAM_A, GAUSS_CORRECTION_PARAM_B, GAUSS_CORRECTION_PARAM_C, GAUSS_CORRECTION_PARAM_D, analogKeyOptions.travelDistance);
}

void AnalogKeyAddon::process() {
  const AnalogKeyOptions& analogKeyOptions = Storage::getInstance().getAddonOptions().analogKeyOptions;
  Gamepad *gamepad = Storage::getInstance().GetGamepad();

  for (uint8_t channel = 0; channel < MUX_CHANNELS; channel++) {
    uint8_t channel_greycoded = (channel >> 1) ^ channel;

    selectMux(channel_greycoded);

		Mask_t buttonMask = analogKeyOptions.analogKeys[channel_greycoded].mask;

		AnalogKey &key = keys[channel_greycoded];

		scanKey(key);
		checkKey(key);

	  if (buttonMask == GAMEPAD_MASK_DU) {
			gamepad->state.dpad |= key.pressed ? GAMEPAD_MASK_UP : 0;
		} else if (buttonMask == GAMEPAD_MASK_DD) {
			gamepad->state.dpad |= key.pressed ? GAMEPAD_MASK_DOWN : 0;
		} else if (buttonMask == GAMEPAD_MASK_DL) {
			gamepad->state.dpad |= key.pressed ? GAMEPAD_MASK_LEFT : 0;
		} else if (buttonMask == GAMEPAD_MASK_DR) {
			gamepad->state.dpad |= key.pressed ? GAMEPAD_MASK_RIGHT : 0;
		} else {
			gamepad->state.buttons |= key.pressed ? buttonMask : 0;
		}
	}
}

void AnalogKeyAddon::bootProcess() {
  const AnalogKeyOptions& analogKeyOptions = Storage::getInstance().getAddonOptions().analogKeyOptions;
  Gamepad *gamepad = Storage::getInstance().GetGamepad();

  for (uint8_t channel = 0; channel < MUX_CHANNELS; channel++) {
    uint8_t channel_greycoded = (channel >> 1) ^ channel;

    selectMux(channel_greycoded);

		Mask_t buttonMask = analogKeyOptions.analogKeys[channel_greycoded].mask;

		AnalogKey &key = keys[channel_greycoded];

		key.pressed = 1350 > adc_read();

	  if (buttonMask == GAMEPAD_MASK_DU) {
			gamepad->state.dpad |= key.pressed ? GAMEPAD_MASK_UP : 0;
		} else if (buttonMask == GAMEPAD_MASK_DD) {
			gamepad->state.dpad |= key.pressed ? GAMEPAD_MASK_DOWN : 0;
		} else if (buttonMask == GAMEPAD_MASK_DL) {
			gamepad->state.dpad |= key.pressed ? GAMEPAD_MASK_LEFT : 0;
		} else if (buttonMask == GAMEPAD_MASK_DR) {
			gamepad->state.dpad |= key.pressed ? GAMEPAD_MASK_RIGHT : 0;
		} else {
			gamepad->state.buttons |= key.pressed ? buttonMask : 0;
		}
	}
}

void AnalogKeyAddon::selectMux(uint8_t channel) {
  if (channel > MUX_CHANNELS) return;

  for (uint8_t i = 0; i < MUX_SELECTOR_BITS; i++) {
		gpio_put(muxSelectorPins[i], channel & (1 << i));
  }
}

long AnalogKeyAddon::map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void AnalogKeyAddon::scanKey(AnalogKey &key) {
  const AnalogKeyOptions& analogKeyOptions = Storage::getInstance().getAddonOptions().analogKeyOptions;
	const uint16_t rawValue = adc_read();

	key.rawValue = rawValue;

	// Read the value from the port of the specified key and run it through the SMA filter.
	key.smaValue = key.filter(rawValue);

	// Invert the value if the definition is set since in rare fields of application the sensor
	// is mounted the other way around, resulting in a different polarity and inverted sensor readings.
	// Since this firmware expects the value to go down when the button is pressed down, this is needed.
  if (analogKeyOptions.bottomMagneticPole == BottomMagneticPole::S_POLE) {
    key.smaValue = (1 << ANALOG_RESOLUTION) - 1 - key.smaValue;
	}

	// If the SMA filter is fully initalized (at least one full circular buffering has been performed), calibration can be performed.
	// This keeps track of the lowest and highest value reached on each key, giving us boundaries to map to an actual milimeter distance.
	if (key.filter.initialized) {
		updateKeyRange(key);
	}

	// Make sure that the key is calibrated, which means that the down position (default 4095) was updated to be  smaller than the rest position.
	// If that's not the case, we go with the total switch travel distance representing a key that is fully up, effectively disabling any value processing.
	// This if-branch is inheritly triggered if the SMA filter is not initialized yet, as the default down position of 4095 was not updated yet.
	if (!key.calibrated) {
		key.distance = analogKeyOptions.travelDistance;

		return;
	}

	// If gauss correction is enabled, use the GaussLUT instance to get the distance based on the adc value and the rest position
	// of the key, which is used to determine the offset from the "ideal" rest position set by the lookup table calculations.
	uint16_t distance = gaussLUT.adcToDistance(key.smaValue, key.restPosition);

	// Stretch the value to the full travel distance using our down position since the LUT is rest-position based. Then invert and constrain it.
	distance = distance * analogKeyOptions.travelDistance / gaussLUT.adcToDistance(key.downPosition, key.restPosition);
	key.distance = constrain(analogKeyOptions.travelDistance - distance, 0, analogKeyOptions.travelDistance);

  // key.distance = constrain(map(key.smaValue, key.downPosition, key.restPosition, 0, TRAVEL_DISTANCE_IN_0_01MM), 0, TRAVEL_DISTANCE_IN_0_01MM);
}

void AnalogKeyAddon::checkKey(AnalogKey &key) {
  const AnalogKeyOptions& analogKeyOptions = Storage::getInstance().getAddonOptions().analogKeyOptions;
	const ActuationOptions& actuationOptions = analogKeyOptions.analogKeys[key.index].enabledPerKeySettings ? analogKeyOptions.analogKeys[key.index].actuationOptions : analogKeyOptions.actuationOptions;

	if (actuationOptions.actuationMode == ActuationMode::STATIC_ACTUATION) {
		if (key.distance <= MAX(analogKeyOptions.travelDistance - actuationOptions.actuationPoint - pressHysteresis, 0)) {
			key.pressed = true;
		} else if (key.distance >= MIN(analogKeyOptions.travelDistance - actuationOptions.actuationPoint + releaseHysteresis, analogKeyOptions.travelDistance)) {
			key.pressed = false;
		}

		return;
	}

	// RT STEP 1: Reset the rapid trigger state if the value left the rapid trigger zone (normal) or was fully released (CRT).
	// If the value is above the upper hysteresis the value is not (anymore) inside the rapid trigger zone
	// meaning the rapid trigger state for the key has to be set to false in order to be processed by further checks.
	// This only applies if continuous rapid trigger is not enabled as it only resets the state when the key is fully released.
	if (key.distance >= MIN(analogKeyOptions.travelDistance - actuationOptions.actuationPoint + releaseHysteresis, analogKeyOptions.travelDistance) && actuationOptions.actuationMode != ActuationMode::CONTINUOUS_RAPID_TRIGGER) {
		key.inRapidTriggerZone = false;
	// If continuous rapid trigger is enabled, the state is only reset to false when the key is fully released (<0.1mm).
	} else if (key.distance >= analogKeyOptions.travelDistance - CONTINUOUS_RAPID_TRIGGER_THRESHOLD && actuationOptions.actuationMode == ActuationMode::CONTINUOUS_RAPID_TRIGGER) {
		key.inRapidTriggerZone = false;
	}

	// RT STEP 2: If the value entered the rapid trigger zone, perform a press and set the rapid trigger state to true.
	// If the value is below the lower hysteresis and the rapid trigger state is false on the key, press the key because the action of entering
	// the rapid trigger zone is already counted as a trigger. From there on, the actuation point moves dynamically in that zone.
	// Also the rapid trigger state for the key has to be set to true in order to be processed by furture loops.
	if (key.distance <= analogKeyOptions.travelDistance - actuationOptions.actuationPoint && !key.inRapidTriggerZone) {
		key.inRapidTriggerZone = true;
		key.pressed = true;

	// RT STEP 3: If the key *already is* in the rapid trigger zone (hence the 'else if'), check whether the key has travelled the sufficient amount.
	// Check whether the key should be pressed. This is the case if the key is currently not pressed,
	// the rapid trigger state is true and the value drops more than (down sensitivity) below the highest recorded value.
	} else if (!key.pressed && key.inRapidTriggerZone && key.distance <= key.extremum - actuationOptions.pressSensitivity) {
		key.pressed = true;

	// Check whether the key should be released. This is the case if the key is currently pressed down and either the
	// rapid trigger state is no longer true or the value rises more than (up sensitivity) above the lowest recorded value.
	} else if (key.pressed && (!key.inRapidTriggerZone || key.distance >= key.extremum + actuationOptions.releaseSensitivity)) {
		key.pressed = false;
	}

	// RT STEP 4: Always remember the peaks of the values, depending on the current pressed state.
	// If the key is pressed and at an all-time low or not pressed and at an all-time high, save the value.
	if ((key.pressed && key.distance < key.extremum) || (!key.pressed && key.distance > key.extremum)) {
		key.extremum = key.distance;
	}
}

void AnalogKeyAddon::updateKeyRange(AnalogKey &key) {
  const AnalogKeyOptions& analogKeyOptions = Storage::getInstance().getAddonOptions().analogKeyOptions;

  // Calculate the value with the deadzone in the positive and negative direction applied.
  uint16_t upperValue = key.smaValue - SENSOR_BOUNDARY_DEADZONE;
  uint16_t lowerValue = key.smaValue + SENSOR_BOUNDARY_DEADZONE;

  // If the read value with deadzone applied is bigger than the current rest position, update it.
  if (key.restPosition < upperValue) {
    key.restPosition = upperValue;

  // If the read value with deadzone applied is lower than the current down position, update it. Make sure that the distance to the rest position
  // is at least SENSOR_BOUNDARY_MIN_DISTANCE (scaled with travel distance @ 4.00mm) to prevent poor calibration/analog range resulting in "crazy behaviour".
  } else if (key.downPosition > lowerValue && key.restPosition - lowerValue >= (analogKeyOptions.travelDistance / 2) * analogKeyOptions.travelDistance / analogKeyOptions.travelDistance) {
    // From here on, the down position has been set < rest position, therefore the key can be considered calibrated, allowing distance calculation.
    key.calibrated = true;
    key.downPosition = lowerValue;
  }
}
