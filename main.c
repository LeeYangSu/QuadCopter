#include "arm.h"

void Init();

/* PID ��� */
float kp = 0;
float ki = 0;
float kd = 0;

/* ���� �ּ� �ӵ� */
float motor_pwm2_speed = 330;
float motor_pwm3_speed = 330;

/* ��ǥ ���� */
float TARGET_ANGLE = 0;

/* ���� �ʱ�ȭ �� */
float ui_duty2 = 200;
float ui_duty3 = 200;

/* Į�� ���� �۵� ī���� */
int cnt_ = 0;

/* ��¿� �ӽ� ����*/
unsigned int P_cnt = 0;
unsigned int I_cnt = 0;
unsigned int D_cnt = 0;
float kp_temp = 0.01;

int main()
{
	struct Gyro1DKalman filter_roll;
	init_Gyro1DKalman(&filter_roll, 0.1,0.3, 1);

	Init();

	PIO_SODR = (1 << switch_pin);
	/* 3�� ��� */
	delay_ms(3000);               
	PIO_CODR = (1 << switch_pin);
	
	INIT_UART0();
	
	while(1)
	{
		if(cnt_ == 100)
		{
			Kalman(&filter_roll);
		}
	}		
	
	return 0;
}

void Init()
{
	Init_switch();
	Init_PWM();
	Init_DBGU();
	Init_timer0();
//	Init_timer1();
	Init_ADC();
	Motor_Init();
	return ;
}
