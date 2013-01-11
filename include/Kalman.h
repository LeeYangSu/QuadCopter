#ifndef __KALMAN_H__
#define __KALMAN_H__

float PredictAccG_roll(float a_z, float a_y);
void Kalman(struct Gyro1DKalman *);

#endif 	//__KALMAN_h__
