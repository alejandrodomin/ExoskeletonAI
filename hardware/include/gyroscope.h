#ifndef GYROSCOPE_HPP
#define GYROSCOPE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "LSM9DS1_Types.h"
#include "LSM9DS1.h"

LSM9DS1 imuInit(float* gyro, float* accel, float* mag, int index);
void imuRead(float* gyro, float* accel, float* mag, LSM9DS1 imu);

#endif