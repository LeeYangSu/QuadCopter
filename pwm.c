#include "arm.h"

void Init_PWM(void)
{
	PMC_PCER = (1<<PWMC); // 전원 공급
	
	PIO_PUDR = (1<<PWM2)|(1<<PWM3); // 풀업저항 off

	PIO_BSR  = (1<<PWM2)|(1<<PWM3); // Peripheral B 선택

	return ;
}

void Motor_Init(void)
{
	PIO_PDR  = (1 << PWM2 )|( 1 << PWM3 ); // I/O PIN off

	PWM_MR   = ( 0 << PWM_PREA ) | ( 24 << PWM_DIVA ) | ( 0 << PWM_PREB ) | ( 24 << PWM_DIVB ); 
	PWM_CMR2 = ( 0 << PWM_CPD ) | ( 1 << PWM_CPOL ) | ( 0 << PWM_CALG ) | ( 11 << PWM_CPRE );
	PWM_CMR3 = ( 0 << PWM_CPD ) | ( 1 << PWM_CPOL ) | ( 0 << PWM_CALG ) | ( 11 << PWM_CPRE );

	PWM_CDTY2 = 3000;
	PWM_CPRD2 = 40000;

	PWM_CDTY3 = 3000;
	PWM_CPRD3 = 40000;
	
	PWM_ENA = (1<<CHID2)|(1<<CHID3); // PWM 3번 채널 동작

	return ;
}

void PWM3_dutyset(float duty)
{

	PWM_CUPD3 = duty;

	return ;
}

void PWM2_dutyset(float duty)
{
	PWM_CUPD2 = duty;

	return ;
}
