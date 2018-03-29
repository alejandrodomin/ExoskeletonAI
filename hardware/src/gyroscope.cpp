#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "LSM9DS1_Types.h"
#include "LSM9DS1.h"

/*
int main(int argc, char *argv[]) {
    LSM9DS1 imu(IMU_MODE_I2C, 0x6a, 0x1c);
    imu.begin();
    if (!imu.begin()) {
        fprintf(stderr, "Failed to communicate with LSM9DS1.\n");
        exit(EXIT_FAILURE);
    }
    imu.calibrate();

    for (;;) {
        while (!imu.gyroAvailable()) ;
        imu.readGyro();
        while(!imu.accelAvailable()) ;
        imu.readAccel();
        while(!imu.magAvailable()) ;
        imu.readMag();

        printf("Gyro: %f, %f, %f [deg/s]\n", imu.calcGyro(imu.gx), imu.calcGyro(imu.gy), imu.calcGyro(imu.gz));
        printf("Accel: %f, %f, %f [Gs]\n", imu.calcAccel(imu.ax), imu.calcAccel(imu.ay), imu.calcAccel(imu.az));
        printf("Mag: %f, %f, %f [gauss]\n", imu.calcMag(imu.mx), imu.calcMag(imu.my), imu.calcMag(imu.mz));
        sleep(1.0);
    }

    exit(EXIT_SUCCESS);
}
*/

LSM9DS1 imuInit(int imuNum){

	if (imuNum == 0){
		LSM9DS1 imu(IMU_MODE_I2C, 0x6a, 0x1c);
		imu.begin();
		imu.calibrate();
		if (!imu.begin()){
			fprintf(stderr, "Failed to communicate with LSM9DS1.\n");
			exit(EXIT_FAILURE);
		}
		return imu;
	}
	else if (imuNum == 1){
		LSM9DS1 imu(IMU_MODE_I2C, 0x6b, 0x1e);
		imu.begin();
		imu.calibrate();
		if (!imu.begin()){
			fprintf(stderr, "Failed to communicate with LSM9DS1.\n");
			exit(EXIT_FAILURE);
		}
		return imu;
	}
	
	fprintf(stderr, "Incorrect imu choice, chose 0,1,2.\n");
	exit(EXIT_SUCCESS);
}

void imuRead(float* gyro, float* accel, float* mag, LSM9DS1 imu){
	float* loc = NULL;
	//for(;;){
		while (!imu.gyroAvailable());
		imu.readGyro();
		while (!imu.accelAvailable());
		imu.readAccel();
		while (!imu.magAvailable());
		imu.readMag();

		*gyro = imu.calcGyro(imu.gx);
		loc = gyro + 1;
		*loc = imu.calcGyro(imu.gy);
		loc = gyro + 2;
		*loc = imu.calcGyro(imu.gz);

		*accel = imu.calcAccel(imu.ax);
		loc = accel + 1;
		*loc = imu.calcAccel(imu.ay);
		loc = accel + 2;
		*loc = imu.calcAccel(imu.az);

		*mag = imu.calcMag(imu.mx);
		loc = mag + 1;
		*loc = imu.calcMag(imu.my);
		loc = mag + 2;
		*loc = imu.calcMag(imu.mz);
		sleep(1.0);
	//}
}

// int main (int argc, char **argv){
// 	float g[3] = {0}, a[3] = {0}, m[3] = {0};
// 	LSM9DS1 imu1 = imuInit(0);
// 	LSM9DS1 imu2 = imuInit(1);
// 	imuRead(g,a,m,imu1);
// 	printf("%f, %f, %f [deg/s]\n", g[0], g[1], g[2]);
// 	printf("%f, %f, %f [Gs]\n", a[0], a[1], a[2]);
// 	printf("%f, %f, %f [gauss]\n", m[0], m[1], m[2]);
	
// 	imuRead(g,a,m,imu2);
// 	printf("%f, %f, %f [deg/s]\n", g[0], g[1], g[2]);
// 	printf("%f, %f, %f [Gs]\n", a[0], a[1], a[2]);
// 	printf("%f, %f, %f [gauss]\n", m[0], m[1], m[2]);

// 	imuRead(g,a,m,imu1);
// 	printf("%f, %f, %f [deg/s]\n", g[0], g[1], g[2]);
// 	printf("%f, %f, %f [Gs]\n", a[0], a[1], a[2]);
// 	printf("%f, %f, %f [gauss]\n", m[0], m[1], m[2]);



// exit(EXIT_SUCCESS);
// }


