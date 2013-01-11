#ifndef __ADC_H__
#define __ADC_H__

void Init_ADC(void);
unsigned int ADC_Run(void);
unsigned int ADC_xgyro(void);
unsigned int ADC_zgyro(void);
unsigned int ADC_XACEL(void);
unsigned int ADC_YACEL(void);
unsigned int ADC_ZACEL(void);

#endif	//__ADC_H__

