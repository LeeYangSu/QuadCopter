#include "arm.h"

void  Init_switch()
{
	PMC_PCER = (1 << PIOA);
	PIO_OWER = (1<<switch_pin);
	PIO_PER  = (1<<switch_pin);
	PIO_OER  = (1<<switch_pin);
	PIO_CODR = (1<<switch_pin);
	
	return ;
}

void Switch_OnOff()
{
	unsigned char ch;

	ch = DBGU_GetChar();

	if(ch == 'q')	    // Switch is On 
	{
		PIO_CODR = (1<<switch_pin);
	}
	if(ch == 'w')       // Switch is Off
	{
		PIO_SODR = (1<<switch_pin);
	}

	return ;
}
