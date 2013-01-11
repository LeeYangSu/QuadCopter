#include "arm.h"

extern float ui_duty2;
extern float ui_duty3;

void Kalman(struct Gyro1DKalman * filter_roll)
{
	float temp=0;
	float roll_angle = 0;
	float pich_angle = 0;
	float dt= 0.02;
	
    /* dt =timer_dt();   // time passed in s since last call */

	// execute kalman filter
	temp = PredictAccG_roll(accelero_z(), accelero_y());
	
	ars_predict(filter_roll, gyro_roll_degrees(), dt);  // Kalman predict
   	roll_angle = ars_update(filter_roll, temp);         // Kalman update + result (angle)

	motor_pid_ctrl(roll_angle);			 	            // pid »£√‚ 

   	return ;
}

float PredictAccG_roll(float a_z, float a_y)
{	
	float temp = ((atan2(-a_z, a_y)*360/3.1459));

	return temp;
}
