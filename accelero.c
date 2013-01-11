#include "arm.h"

static const int ADC_X_NEUTRAL = 512;
static const int ADC_Y_NEUTRAL = 512;
static const int ADC_Z_NEUTRAL = 770;

float accelero_x()
{
	float accx=ADC_XACEL();
	if(accx==525)
	{
		accx=526;
	}
	return (accx-525);
}

float accelero_y()
{
	float accy=ADC_YACEL();
	if(accy==525)
	{
		accy=526;
	}
	return (accy-525); 
}

float accelero_z()
{
	float accz=ADC_ZACEL();
	if(accz==775)
	{
		accz=776;
	}
	return (accz-775); 
}
