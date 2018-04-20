#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "LSM9DS1_Types.h"
#include "LSM9DS1.h"
#include <mpi.h>
#include <wiringPi.h>

#define IRSensor 4

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

static bool master = false;

LSM9DS1 imuInit(int imuNum){

	if (imuNum == 0){
		LSM9DS1 imu(IMU_MODE_I2C, 0x6a, 0x1c);
		imu.begin();
		imu.calibrate();
		if (!imu.begin()){
			fprintf(stderr, "Failed to communicate with LSM9DS1.\n");
			exit(EXIT_SUCCESS);
		}
		else return imu;
	}
	else if (imuNum == 1){
		LSM9DS1 imu(IMU_MODE_I2C, 0x6b, 0x1e);
		imu.begin();
		imu.calibrate();
		if (!imu.begin()){
			// fprintf(stderr, "Failed to communicate with LSM9DS1.\n");
			master = true;
		}
		else return imu;
	}
	else{
		fprintf(stderr, "Incorrect imu choice, chose 0 or 1.\n");
		//exit(EXIT_SUCCESS);
	}
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

void IRHandler (void){
	if (digitalRead(IRSensor) == 1)
		printf("Object sensed on the left, stop motion!");
	else
		printf("all clear cap'n");
}
/*
int main (int argc, char **argv){
	int world_size, world_rank, name_len;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Get_processor_name(processor_name, &name_len);

	wiringPiSetup();
	pinMode(IRSensor, INPUT);
	//pullUpDnControl(IRSensor, PUD_UP);
	//wiringPiISR(IRSensor, INT_EDGE_BOTH, IRHandler);
	
	LSM9DS1 imu1, imu2;
	int ir_sensor = 0, test = 0;
	float g[3] = {0}, a[3] = {0}, m[3] = {0};

	if(strcmp(processor_name, "master") != 0){
		imu1 = imuInit(0);
		if(!master)
			imu2 = imuInit(1);
	while(1){
		imuRead(g,a,m,imu1);
		printf("\033[1;32mProcess %s, rank %d, out of %d processes.\033[0m\n", processor_name, world_rank+1, world_size);
		printf("%f, %f, %f [deg/s]\n", g[0], g[1], g[2]);
		printf("%f, %f, %f [Gs]\n", a[0], a[1], a[2]);
		printf("%f, %f, %f [gauss]\n", m[0], m[1], m[2]);

		if(!master){
		imuRead(g,a,m,imu2);
		printf("\033[1:32mProcess %s, rank %d, out of %d processes.\033[0m\n", processor_name, world_rank+1, world_size);
		printf("%f, %f, %f [deg/s]\n", g[0], g[1], g[2]);
		printf("%f, %f, %f [Gs]\n", a[0], a[1], a[2]);
		printf("%f, %f, %f [gauss]\n", m[0], m[1], m[2]);
		}

		ir_sensor = digitalRead(IRSensor);
		//printf("\033[1;33mStatus of IRSensor = %d, GPIO.4 = %d\033[0m\n", ir_sensor, test);
		}
	else{
		printf("Process %s, rank %d, out of %d processes does not have any gyros connected.", processor_name, world_rank, world_size);
	

	//}
	MPI_Finalize();
	exit(EXIT_SUCCESS);
}
*/

