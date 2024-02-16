#ifndef _AnalogKey_H
#define _AnalogKey_H

#include "gpaddon.h"

#include "BoardConfig.h"

#include "addons/analog_key/sma_filter.h"
#include "addons/analog_key/gauss_lut.h"

#ifndef ANALOG_KEY_ENABLED
#define ANALOG_KEY_ENABLED 0
#endif

// The travel distance of the switches, where 1 unit equals 0.01mm. This is used to map the values properly to
// guarantee that the unit for the numbers used across the firmware actually matches the milimeter metric.
#ifndef TRAVEL_DISTANCE_IN_0_01MM
#define TRAVEL_DISTANCE_IN_0_01MM 400
#endif

#ifndef BOTTOM_MAGNETIC_POLE
#define BOTTOM_MAGNETIC_POLE 0
#endif

#ifndef ANALOG_KEY_ACTUATION_MODE
#define ANALOG_KEY_ACTUATION_MODE 0
#endif

#ifndef ANALOG_KEY_ACTUATION_POINT
#define ANALOG_KEY_ACTUATION_POINT 150
#endif

#ifndef ANALOG_KEY_PRESS_SENSITIVITY
#define ANALOG_KEY_PRESS_SENSITIVITY 20
#endif

#ifndef ANALOG_KEY_RELEASE_SENSITIVITY
#define ANALOG_KEY_RELEASE_SENSITIVITY 55
#endif

#ifndef MUX_PIN
#define MUX_PIN 29
#endif

#ifndef MUX_SELECTOR_PINS
#define MUX_SELECTOR_PINS { 4, 5, 3, 2 }
#endif

#ifndef MUX_PIN_00
#define MUX_PIN_00 MuxAction::MUX_PIN_NONE
#endif

#ifndef MUX_PIN_01
#define MUX_PIN_01 MuxAction::MUX_PIN_NONE
#endif

#ifndef MUX_PIN_02
#define MUX_PIN_02 MuxAction::MUX_PIN_NONE
#endif

#ifndef MUX_PIN_03
#define MUX_PIN_03 MuxAction::MUX_PIN_NONE
#endif

#ifndef MUX_PIN_04
#define MUX_PIN_04 MuxAction::MUX_PIN_NONE
#endif

#ifndef MUX_PIN_05
#define MUX_PIN_05 MuxAction::MUX_PIN_NONE
#endif

#ifndef MUX_PIN_06
#define MUX_PIN_06 MuxAction::MUX_PIN_NONE
#endif

#ifndef MUX_PIN_07
#define MUX_PIN_07 MuxAction::MUX_PIN_NONE
#endif

#ifndef MUX_PIN_08
#define MUX_PIN_08 MuxAction::MUX_PIN_NONE
#endif

#ifndef MUX_PIN_09
#define MUX_PIN_09 MuxAction::MUX_PIN_NONE
#endif

#ifndef MUX_PIN_10
#define MUX_PIN_10 MuxAction::MUX_PIN_NONE
#endif

#ifndef MUX_PIN_11
#define MUX_PIN_11 MuxAction::MUX_PIN_NONE
#endif

#ifndef MUX_PIN_12
#define MUX_PIN_12 MuxAction::MUX_PIN_NONE
#endif

#ifndef MUX_PIN_13
#define MUX_PIN_13 MuxAction::MUX_PIN_NONE
#endif

#ifndef MUX_PIN_14
#define MUX_PIN_14 MuxAction::MUX_PIN_NONE
#endif

#ifndef MUX_PIN_15
#define MUX_PIN_15 MuxAction::MUX_PIN_NONE
#endif

/*
---------------------------
  Analog Key
---------------------------
*/

struct AnalogKey {
  uint16_t rawValue = 0;
  uint16_t smaValue = 0;
  uint16_t restPosition = 0;
  uint16_t downPosition = (1 << ANALOG_RESOLUTION) - 1;
  uint16_t distance = 0;
  uint16_t extremum = UINT16_MAX;
	bool calibrated = false;
	bool pressed = false;
	bool inRapidTriggerZone = false;
	SMAFilter filter = SMAFilter(SMA_FILTER_SAMPLE_EXPONENT);
};

/*
---------------------------
  Analog Key Addon
---------------------------
*/

#define MUX_SELECTOR_BITS 4
#define MUX_CHANNELS ( 1 << MUX_SELECTOR_BITS )

#define ANALOG_RESOLUTION 12

// This number will be added to the down position and substracted from the rest position on bounary update
// to introduce a deadzone at the boundaries. This might be desired since values might fluctuate.
// e.g. if the value fluctuates around 1970 in rest position but peaks at 1975, this would counteract it.
// 10 may seem like much at first but when "smashing" the button a lot it'll be just right.
#define SENSOR_BOUNDARY_DEADZONE 20

// The minimum difference between the rest position and the deadzone-applied down position.
// It is important to mantain a minimum analog range to prevent "crazy behavior".
#define SENSOR_BOUNDARY_MIN_DISTANCE 200

// The threshold when a key is considered fully released. 10 would mean if the key is <0.1mm pressed.
// This value is important to reset the rapid trigger state properly with continuous rapid trigger.
#define CONTINUOUS_RAPID_TRIGGER_THRESHOLD 0

enum BottomMagneticPole {
  N_POLE = 0,
  S_POLE,
};

enum ActuationMode {
  STATIC_ACTUATION = 0,
  RAPID_TRIGGER,
  CONTINUOUS_RAPID_TRIGGER,
};

enum MuxAction {
	MUX_PIN_NONE = 255,
	MUX_PIN_UP = 0,
	MUX_PIN_DOWN = 1,
	MUX_PIN_LEFT = 2,
	MUX_PIN_RIGHT = 3,
	MUX_PIN_B1 = 4,
	MUX_PIN_B2 = 5,
	MUX_PIN_B3 = 6,
	MUX_PIN_B4 = 7,
	MUX_PIN_L1 = 8,
	MUX_PIN_R1 = 9,
	MUX_PIN_L2 = 10,
	MUX_PIN_R2 = 11,
	MUX_PIN_S1 = 12,
	MUX_PIN_S2 = 13,
	MUX_PIN_L3 = 14,
	MUX_PIN_R3 = 15,
	MUX_PIN_A1 = 16,
	MUX_PIN_A2 = 17,
	MUX_PIN_Fn = 18,
};

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

// Analog Module Name
#define AnalogKeyName "AnalogKey"

class AnalogKeyAddon : public GPAddon {
public:
	virtual bool available();
	virtual void setup();
	virtual void process();
	virtual void preprocess() {}
	virtual void bootProcess();
  virtual std::string name() { return AnalogKeyName; }
	AnalogKey keys[MUX_CHANNELS];
	AnalogKey bootKeys[MUX_CHANNELS];
private:
	uint16_t pressHysteresis = 0;
	uint16_t releaseHysteresis = 50;
  uint8_t muxSelectorPins[MUX_SELECTOR_BITS] = MUX_SELECTOR_PINS;
	MuxAction muxIndex[MUX_CHANNELS] = {
		MUX_PIN_00, // LEFT
		MUX_PIN_01, // DOWN
		MUX_PIN_02, // R2
		MUX_PIN_03, // B2
		MUX_PIN_04, // L3
		MUX_PIN_05, // B1
		MUX_PIN_06, // UP
		MUX_PIN_07, // RIGHT
		MUX_PIN_08,
		MUX_PIN_09,
		MUX_PIN_10, // L2
		MUX_PIN_11, // B3
		MUX_PIN_12, // L1
		MUX_PIN_13, // R1
		MUX_PIN_14, // B4
		MUX_PIN_15  // R3
	};

	void selectMux(uint8_t channel);
	void updateKeyRange(AnalogKey *key);
	void scanKey(AnalogKey *key);
	void checkKey(AnalogKey *key);
	long map(long x, long in_min, long in_max, long out_min, long out_max);
  GaussLUT gaussLUT = GaussLUT();
};

#endif  // _AnalogKey_H_
