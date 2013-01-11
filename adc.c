#include "arm.h"

void Init_ADC(void)
{
	PMC_PCER = (1<<ADC);              
	ADC_CR   = (1<<ADC_SWRST);                 
	ADC_CHER = (1<<ADC_CH7)|(1<<ADC_CH6)|(1<<ADC_CH5)|(1<<ADC_CH4)|(1<<ADC_CH3);                
	ADC_MR   = (47<<ADC_PRESCAL) | (0<<ADC_LOWRES);
	
	return ;
}

unsigned int ADC_Run(void)
{
	ADC_CR = (1<<ADC_START);
	while(0 == (ADC_SR & (1<<ADC_DRDY)));
	
	return ADC_LCDR&0x000003FF;
}

unsigned int ADC_xgyro(void)
{
	ADC_CR = (1<<ADC_START);
	while(0 == (ADC_SR & (1<<ADC_EOC7)));
	
	return ADC_CDR7&0x000003FF;
}

unsigned int ADC_zgyro(void)
{
	ADC_CR = (1<<ADC_START);
	while(0 == (ADC_SR & (1<<ADC_EOC6)));
	
	return ADC_CDR6&0x000003FF;
}

unsigned int ADC_XACEL()
{
	ADC_CR = (1<<ADC_START);
	while(0 == (ADC_SR & (1<<ADC_EOC5)));
	
	return ADC_CDR5&0x000003FF;
}
unsigned int ADC_YACEL()
{
	ADC_CR = (1<<ADC_START);
	while(0 == (ADC_SR & (1<<ADC_EOC4)));
	
	return ADC_CDR4&0x000003FF;
}
unsigned int ADC_ZACEL()
{
	ADC_CR = (1<<ADC_START);
	while(0 == (ADC_SR & (1<<ADC_EOC3)));
	
	return ADC_CDR3&0x000003FF;
}

