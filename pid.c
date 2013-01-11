#include "arm.h"

// ====== Ʃ�� =================
extern float kp;	// ��  		
extern float ki;	// ����		
extern float kd;	// �̺� ���
// ==========================

/* PID ���� �ֱ� */
static float dt = 0.02;

/* ���� ���� */
static float roll_current_err = 0;

/* ���� ���� */
static float roll_previosly_err = 0;

/* ���� ���� */
static float roll_deviation_sum = 0;

/* P, I ,D ������ ��� �� */
static float roll_p_ctrl_val = 0;			// P ����
static float roll_i_ctrl_val = 0;			// I ���� ��� ��
static float roll_d_ctrl_val = 0;

/* PID ����� ���� �ӵ� */
static float roll_motor_speed = 0;

/* ���� �ʱ�ȭ �� */
extern float ui_duty2;
extern float ui_duty3;

/* ���� �ּ� �ӵ� */
extern float motor_pwm3_speed;
extern float motor_pwm2_speed;

/* ��ǥ ���� */
extern float TARGET_ANGLE;

/* ��¿� �ӽ� ���� */
extern unsigned int P_cnt;
extern unsigned int I_cnt;
extern unsigned int D_cnt;

void motor_pid_ctrl(float current_angle)	// ���� ������ ���ڷ� �޾ƿ�
{
	unsigned char buff[]="[000,000,000,00.00,0.0000,00.000]\n\r";
	unsigned int cnt;	
	volatile unsigned int icnt;
	
	roll_current_err = TARGET_ANGLE - (current_angle - 90);				     /* ��ǥ ����(0) - ���簢�� (-90 ~ + 90) */
	roll_p_ctrl_val = kp * roll_current_err;								 /* P ���� ��� �� */

	roll_deviation_sum = roll_deviation_sum + (roll_current_err * dt); 		 /* �������� = �������� + ������ * dt */
	
	roll_i_ctrl_val = ki * roll_deviation_sum;								 /* I ���� ��� �� */	

	roll_d_ctrl_val = kd * ((roll_current_err - roll_previosly_err) / dt);	 /* D ���� ��� �� */

	roll_motor_speed = roll_p_ctrl_val + roll_i_ctrl_val + roll_d_ctrl_val;	 /* PID ���� �� */

	roll_previosly_err = roll_current_err;									 /* ���� ������ ���� ������ ���� */

	 if((current_angle - 90) < TARGET_ANGLE)				 				 /* ���� ������ 0���� ������ */
	{
		motor_pwm2_speed = motor_pwm2_speed - roll_motor_speed;
		motor_pwm3_speed = motor_pwm3_speed + roll_motor_speed;
		
		if(motor_pwm2_speed < 330)
		{	
			motor_pwm2_speed = 330 ;
	
		}	
		else if( motor_pwm3_speed < 330)
		{
			motor_pwm3_speed = 330 ;
		}
		
		if(motor_pwm2_speed > 450) 
		{
			motor_pwm2_speed = 450;
		}
		else if( motor_pwm3_speed > 450)
		{
			motor_pwm3_speed = 450;
		}
		PWM2_dutyset(motor_pwm2_speed);
		PWM3_dutyset(motor_pwm3_speed);
	}
	else	
	{
		motor_pwm2_speed = motor_pwm2_speed - roll_motor_speed;
		motor_pwm3_speed = motor_pwm3_speed + roll_motor_speed;
		
		if(motor_pwm2_speed < 330)
		{	
			motor_pwm2_speed = 330 ;
		}	
		else if( motor_pwm3_speed < 330 )
		{
			motor_pwm3_speed = 330 ;
		}
		
		if(motor_pwm2_speed > 450 ) 
		{
			motor_pwm2_speed = 450 ;
		}
		else if(motor_pwm3_speed > 450)
		{
			motor_pwm3_speed = 450;
		}

		PWM2_dutyset(motor_pwm2_speed);
		PWM3_dutyset(motor_pwm3_speed);
	}

	cnt = motor_pwm2_speed;
	buff[1]='0'+((cnt%1000)/100);
	buff[2]='0'+((cnt%100)/10);
	buff[3]='0'+(cnt%10);
	
	cnt = motor_pwm3_speed;
	buff[5]='0'+((cnt%1000)/100);
	buff[6]='0'+((cnt%100)/10);
	buff[7]='0'+(cnt%10);
	
	cnt = current_angle;
	buff[9]='0'+((cnt%1000)/100);
	buff[10]='0'+((cnt%100)/10);
	buff[11]='0'+(cnt%10);

	cnt = P_cnt;
	buff[13]='0'+(cnt/1000);
	buff[14]='0'+((cnt%1000)/100);
	buff[16]='0'+((cnt%100)/10);
	buff[17]='0'+(cnt%10);

	cnt = I_cnt;
	buff[19]='0'+(cnt/10000);
	buff[21]='0'+(cnt/1000);
	buff[22]='0'+((cnt%1000)/100);
	buff[23]='0'+((cnt%100)/10);
	buff[24]='0'+(cnt%10);

	cnt = D_cnt;
	buff[26]='0'+(cnt/10000);
	buff[27]='0'+(cnt/1000);
	buff[29]='0'+((cnt%1000)/100);
	buff[30]='0'+((cnt%100)/10);
	buff[31]='0'+(cnt%10);
	
	DBGU_string(buff);
	for(icnt=0;icnt<20000;icnt++);

	return ;
}
