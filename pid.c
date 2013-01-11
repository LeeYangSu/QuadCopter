#include "arm.h"

// ====== 튜닝 =================
extern float kp;	// 비레  		
extern float ki;	// 적분		
extern float kd;	// 미분 계수
// ==========================

/* PID 제어 주기 */
static float dt = 0.02;

/* 현재 편차 */
static float roll_current_err = 0;

/* 이전 편차 */
static float roll_previosly_err = 0;

/* 누적 편차 */
static float roll_deviation_sum = 0;

/* P, I ,D 각각의 결과 값 */
static float roll_p_ctrl_val = 0;			// P 제어
static float roll_i_ctrl_val = 0;			// I 제어 출력 값
static float roll_d_ctrl_val = 0;

/* PID 적용된 모터 속도 */
static float roll_motor_speed = 0;

/* 모터 초기화 값 */
extern float ui_duty2;
extern float ui_duty3;

/* 모터 최소 속도 */
extern float motor_pwm3_speed;
extern float motor_pwm2_speed;

/* 목표 각도 */
extern float TARGET_ANGLE;

/* 출력용 임시 변수 */
extern unsigned int P_cnt;
extern unsigned int I_cnt;
extern unsigned int D_cnt;

void motor_pid_ctrl(float current_angle)	// 현재 각도를 인자로 받아옴
{
	unsigned char buff[]="[000,000,000,00.00,0.0000,00.000]\n\r";
	unsigned int cnt;	
	volatile unsigned int icnt;
	
	roll_current_err = TARGET_ANGLE - (current_angle - 90);				     /* 목표 각도(0) - 현재각도 (-90 ~ + 90) */
	roll_p_ctrl_val = kp * roll_current_err;								 /* P 제어 출력 값 */

	roll_deviation_sum = roll_deviation_sum + (roll_current_err * dt); 		 /* 누적오차 = 현재편차 + 전편차 * dt */
	
	roll_i_ctrl_val = ki * roll_deviation_sum;								 /* I 제어 출력 값 */	

	roll_d_ctrl_val = kd * ((roll_current_err - roll_previosly_err) / dt);	 /* D 제어 출력 값 */

	roll_motor_speed = roll_p_ctrl_val + roll_i_ctrl_val + roll_d_ctrl_val;	 /* PID 제어 값 */

	roll_previosly_err = roll_current_err;									 /* 현재 에러를 이전 에러로 저장 */

	 if((current_angle - 90) < TARGET_ANGLE)				 				 /* 현재 각도가 0보다 작을때 */
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
