#ifndef _AnalogKey_H
#define _AnalogKey_H

#include "gpaddon.h"

#include "BoardConfig.h"

#include "addons/analog_key/sma_filter.h"
#include "addons/analog_key/gauss_lut.h"

#ifndef ANALOG_KEY_ENABLED
#define ANALOG_KEY_ENABLED 0
#endif

#ifndef MUX_PIN
#define MUX_PIN 29
#endif

#ifndef MUX_SELECTOR_PINS
#define MUX_SELECTOR_PINS \
    {                     \
        4, 5, 3, 2        \
    }
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

#ifndef ANALOG_KEY_01
#define ANALOG_KEY_01 0
#endif

#ifndef ANALOG_KEY_02
#define ANALOG_KEY_02 0
#endif

#ifndef ANALOG_KEY_03
#define ANALOG_KEY_03 0
#endif

#ifndef ANALOG_KEY_04
#define ANALOG_KEY_04 0
#endif

#ifndef ANALOG_KEY_05
#define ANALOG_KEY_05 0
#endif

#ifndef ANALOG_KEY_06
#define ANALOG_KEY_06 0
#endif

#ifndef ANALOG_KEY_07
#define ANALOG_KEY_07 0
#endif

#ifndef ANALOG_KEY_08
#define ANALOG_KEY_08 0
#endif

#ifndef ANALOG_KEY_09
#define ANALOG_KEY_09 0
#endif

#ifndef ANALOG_KEY_10
#define ANALOG_KEY_10 0
#endif

#ifndef ANALOG_KEY_11
#define ANALOG_KEY_11 0
#endif

#ifndef ANALOG_KEY_12
#define ANALOG_KEY_12 0
#endif

#ifndef ANALOG_KEY_13
#define ANALOG_KEY_13 0
#endif

#ifndef ANALOG_KEY_14
#define ANALOG_KEY_14 0
#endif

#ifndef ANALOG_KEY_15
#define ANALOG_KEY_15 0
#endif

#ifndef ANALOG_KEY_16
#define ANALOG_KEY_16 0
#endif

/*
---------------------------
  Analog Key State
---------------------------
*/

struct AnalogKey {
  uint16_t index;
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
#define MUX_CHANNELS (1 << MUX_SELECTOR_BITS)

#define ANALOG_RESOLUTION 12

// This number will be added to the down position and substracted from the rest position on bounary update
// to introduce a deadzone at the boundaries. This might be desired since values might fluctuate.
// e.g. if the value fluctuates around 1970 in rest position but peaks at 1975, this would counteract it.
// 10 may seem like much at first but when "smashing" the button a lot it'll be just right.
#define SENSOR_BOUNDARY_DEADZONE 20

// The threshold when a key is considered fully released. 10 would mean if the key is <0.1mm pressed.
// This value is important to reset the rapid trigger state properly with continuous rapid trigger.
#define CONTINUOUS_RAPID_TRIGGER_THRESHOLD 0

#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

// Analog Module Name
#define AnalogKeyName "AnalogKey"

class AnalogKeyAddon : public GPAddon {
public:
  AnalogKeyAddon() {
    for (uint8_t i = 0; i < MUX_CHANNELS; i++) {
      keys[i] = AnalogKey();
      keys[i].index = i;
    }
  }
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
  GaussLUT gaussLUT;
  void selectMux(uint8_t channel);
  void updateKeyRange(AnalogKey &key);
  void scanKey(AnalogKey &key);
  void checkKey(AnalogKey &key);
  long map(long x, long in_min, long in_max, long out_min, long out_max);
};

#endif // _AnalogKey_H_
