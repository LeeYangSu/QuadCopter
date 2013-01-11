#include "arm.h"

float gyro_roll_degrees()
{
	float roll=ADC_xgyro();

	return ((roll-380)/1024*3.3)/0.00083; 
}


float gyro_pitch_degrees()
{
	float pitch=ADC_zgyro();

	return ((pitch-380)/1024*3.3)/0.00083;

	//return (float) ((int)adc_read(PITCH_ADC)-ADC_PITCH_NEUTRAL) * (gyro_pitch_degrees_per_second / 32750.0);
}

