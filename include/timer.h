#ifndef	__TIMER_H_
#define	__TIMER_H_

void Init_timer0();
void timer_aic_handler();
void delay_ms(unsigned int );
void timer_handler(void);
float timer_dt(void);
void timer_reset(void);
void Init_timer1();

#endif	//__TIMER_H__
