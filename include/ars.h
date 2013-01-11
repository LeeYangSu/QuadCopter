#ifndef __ARS_H__
#define __ARS_H__

struct Gyro1DKalman
{
	/* These variables represent our state matrix x */
	float x_angle;
	float x_bias;

	/* Our error covariance matrix */
	float P_00;
	float P_01;
	float P_10;
	float P_11;
	
	float Q_angle;
	float Q_gyro;
	float R_angle;
};

// Initializing the struct
void init_Gyro1DKalman(struct Gyro1DKalman *filterdata, float Q_angle, float Q_gyro, float R_angle);

// Kalman predict
void ars_predict(struct Gyro1DKalman *filterdata, const float gyro, const float dt);

// Kalman update
float ars_update(struct Gyro1DKalman *filterdata,const float angle_m);

#endif //__ARS_H__
