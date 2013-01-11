#include "arm.h"

void init_Gyro1DKalman(struct Gyro1DKalman *filterdata, float Q_angle, float Q_gyro, float R_angle)
{
	filterdata->Q_angle = Q_angle;
	filterdata->Q_gyro  = Q_gyro;
	filterdata->R_angle = R_angle;
	filterdata->x_angle	= 90;
	filterdata->x_bias	= 0;
	filterdata->P_00	= 0;
	filterdata->P_01	= 0;
	filterdata->P_10	= 0;
	filterdata->P_11	= 0;
}

void ars_predict(struct Gyro1DKalman *filterdata, const float dotAngle, const float dt)
{
	/* 이전 각속도와 지금 각속도를 비교하여 계산한 각도 값 */
	filterdata->x_angle += dt * (dotAngle - filterdata->x_bias);

	filterdata->P_00 += - dt * (filterdata->P_10 + filterdata->P_01) + filterdata->Q_angle * dt;
	filterdata->P_01 += - dt * filterdata->P_11;
	filterdata->P_10 += - dt * filterdata->P_11;
	filterdata->P_11 += + filterdata->Q_gyro * dt;
}

float ars_update(struct Gyro1DKalman *filterdata, const float angle_m)
{
	/* 측정된 각도와 계산된 각도의 오차 */
	const float y = angle_m - filterdata->x_angle;

	const float S = filterdata->P_00 + filterdata->R_angle;

	/* 칼만 이득 계산 */
	const float K_0 = filterdata->P_00 / S;
	const float K_1 = filterdata->P_10 / S;
	
	filterdata->x_angle +=  K_0 * y;
	filterdata->x_bias  +=  K_1 * y;
	
	filterdata->P_00 -= K_0 * filterdata->P_00;
	filterdata->P_01 -= K_0 * filterdata->P_01;
	filterdata->P_10 -= K_1 * filterdata->P_00;
	filterdata->P_11 -= K_1 * filterdata->P_01;
	
	return filterdata->x_angle;
}
