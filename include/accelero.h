#ifndef __ACCELERO_H__
#define __ACCELERO_H__

unsigned int accelero_x_raw();
unsigned int accelero_y_raw();
unsigned int accelero_z_raw();

// return 1 = force of 1g along axis
float accelero_x();
float accelero_y();
float accelero_z();

float accelero_roll_radians();

#endif	//__ACCELERO_H__
