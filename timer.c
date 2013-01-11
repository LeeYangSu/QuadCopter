#include "arm.h"

#define	FOSC	1000
#define	PLL	    1
#define	FCY	    FOSC*PLL

static volatile unsigned int tick_Cnt;
static const float per_second =(float)FCY;
static volatile float TMR1=0;

void Init_timer0()
{
	PMC_PCER = (1 << TC0);
	TC0_CCR = (1<<TC_CLKDIS);
	TC0_IDR = (1<<TC_COVFS) |(1<<TC_LOVRS) | (1<<TC_CPAS) | (1<<TC_CPBS) | (1<<TC_CPCS) | (1<<TC_LDRAS) | (1<<TC_LDRBS) | (1<<TC_ETRGS);
	TC0_SR;                                                      //읽어서 의도적으로 지우기 위해서 읽었음
	TC0_CMR = (TIMER_CLOCK4 << TC_TCCLKS) | (1 << TC_CPCTRG);
	TC0_RC = 375;                      // 1ms 마다 인터럽트가 발생 -> 즉 1ms 마다 함수 호출가능
	AIC_IDCR = (1<<TC0);
	AIC_SVR[TC0] = (unsigned int)timer_aic_handler;
	AIC_SMR[TC0] = (5<<AIC_PRIOR) | (AIC_SRCTYPE_INT_HIGH_LEVEL<<AIC_SRCTYPE);
	AIC_ICCR = (1<<TC0);
	TC0_IER = (1<<TC_CPCS);               //TC0_RC의 값을 쓰기 위해서
	AIC_IECR = (1<<TC0);
	TC0_CCR =  (1<<TC_CLKEN);
	TC0_CCR =  (1<<TC_SWTRG);
	
	return ;
}

void Init_timer1()
{
	PMC_PCER = (1<<TC1);
	TC1_CCR = (1<<TC_CLKDIS);
	TC1_IDR = (1<<TC_COVFS) |(1<<TC_LOVRS) | (1<<TC_CPAS) | (1<<TC_CPBS) | (1<<TC_CPCS) | (1<<TC_LDRAS) | (1<<TC_LDRBS) | (1<<TC_ETRGS);
	TC1_SR; 
	TC1_CMR = (TIMER_CLOCK4 << TC_TCCLKS) | (1 << TC_CPCTRG);
	TC1_RC = 375; 
	AIC_IDCR = (1<<TC1);
	AIC_SVR[TC1] = (unsigned int)timer_dt;
	AIC_SMR[TC1] = (4<<AIC_PRIOR) | (AIC_SRCTYPE_INT_HIGH_LEVEL<<AIC_SRCTYPE);
	AIC_ICCR = (1<<TC1);
	TC1_IER = (1<<TC_CPCS);               //TC0_RC의 값을 쓰기 위해서
	AIC_IECR = (1<<TC1);
	TC1_CCR = (1<<TC_CLKEN);
	TC1_CCR = (1<<TC_SWTRG);

	return ;
}
void timer_aic_handler()
{
	TC0_SR;
	++tick_Cnt;
	TC0_SR;

	return ;
}

void delay_ms(unsigned int ui_ms)
{
	tick_Cnt = 0;

	while(tick_Cnt < ui_ms);
	
	return ;
}

float timer_dt(void)
{
	float ticks;
	float time;

	ticks	= TMR1;

	timer_reset();
	time	= (float)ticks/per_second;

	return time; 
}

void timer_handler(void)
{
	TC1_SR;
	TMR1++;
	TC1_SR;

	return;
}

void timer_reset(void)
{
	TMR1 =0;

	return;
}
