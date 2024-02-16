#include "enums.pb.h"

#ifndef ANALOG_RESOLUTION
#define ANALOG_RESOLUTION 12
#endif

#ifndef TRAVEL_DISTANCE_IN_0_01MM
#define TRAVEL_DISTANCE_IN_0_01MM 400
#endif

// Variables for the equation to calculate the ADC reading into a physical distance. These numbers are chosen by trial-and-error, making the curve fit.
// These values are only effective on magnets like the ones used in the Gateron-KS 20 or the Wooting Lekkers, which are based on them.
// This gauss correction is also dependent on the hardware specifications. The switch should be as close to the Hall Effect sensor as possible.
// The Hall Effect sensor used is the 49E sensor, therefore these values are highly tailored towards the hardware of the minipad.
// If this firmware is used on a device with different magnets/hardware, these values have to be adjusted or gauss correction has to be disabled.
// The equation for the gauss correction is based off the following Desmos sheet and can be used for adjustments: https://www.desmos.com/calculator/ps4wd127tu
#define GAUSS_CORRECTION_PARAM_A 6647.8446648
#define GAUSS_CORRECTION_PARAM_B -0.00609446727442
#define GAUSS_CORRECTION_PARAM_C -721.743991123
#define GAUSS_CORRECTION_PARAM_D 4525.58542876

class GaussLUT {
public:
	// Variables for the equation to calculate the ADC reading into a physical distance.
	// a = y-stretch, b = x-stretch, c = x-offset, d = y-offset, for more info: https://www.desmos.com/calculator/ps4wd127tu
	// GaussLUT(double a, double b, double c, double d, uint16_t travelDistance);
	// GaussLUT(double a, double b, double c, double d, uint16_t travelDistance);

	void init(double a, double b, double c, double d, uint16_t travelDistance);
	uint16_t adcToDistance(const uint16_t adc, uint16_t const restPosition);

private:
	// The calculated lookup table used by this GaussLUT instance.
	uint16_t lut[1 << ANALOG_RESOLUTION];

	// The rest position of the keys according to the lookup table.
	uint16_t lutRestPosition;
};
