#include <unistd.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define DT 0.02         // [s/loop] loop period. 20ms
#define AA 0.97         // complementary filter constant

#define A_GAIN 0.0573    // [deg/LSB]
#define G_GAIN 0.070     // [deg/s/LSB]
#define RAD_TO_DEG 57.29578
#define M_PI 3.14159265358979323846

/*
    This program  reads the angles from the accelerometer and gyroscope
    on a BerryIMU connected to a Raspberry Pi.
    Both the BerryIMUv1 and BerryIMUv2 are supported
    Feel free to do whatever you like with this code
    Distributed as-is; no warranty is given.
    http://ozzmaker.com/
*/


#include <stdint.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "LSM9DS0.h"
#include "LSM9DS1.h"

int file;
int LSM9DS0 = 0;
int LSM9DS1 = 0;
float q[4];

void  readBlock(uint8_t command, uint8_t size, uint8_t *data)
{
    int result = i2c_smbus_read_i2c_block_data(file, command, size, data);
    if (result != size){
		printf("Failed to read block from I2C.");
		return;
	}
}

void selectDevice(int file, int addr)
{
	if (ioctl(file, I2C_SLAVE, addr) < 0) {
		 printf("Failed to select I2C device.");
	}
}


void readACC(int  *a)
{
	uint8_t block[6];
	if (LSM9DS0){
		selectDevice(file,LSM9DS0_ACC_ADDRESS);
		readBlock(0x80 |  LSM9DS0_OUT_X_L_A, sizeof(block), block);
	}
	else if (LSM9DS1){
		selectDevice(file,LSM9DS1_ACC_ADDRESS);
		readBlock(0x80 |  LSM9DS1_OUT_X_L_XL, sizeof(block), block);
	}

	// Combine readings for each axis.
	*a = (int16_t)(block[0] | block[1] << 8);
	*(a+1) = (int16_t)(block[2] | block[3] << 8);
	*(a+2) = (int16_t)(block[4] | block[5] << 8);

}


void readMAG(int  *m)
{
	uint8_t block[6];
	if (LSM9DS0){
		selectDevice(file,LSM9DS0_MAG_ADDRESS);
		readBlock(0x80 |  LSM9DS0_OUT_X_L_M, sizeof(block), block);
	}
	else if (LSM9DS1){
		selectDevice(file,LSM9DS1_MAG_ADDRESS);
		readBlock(0x80 |  LSM9DS1_OUT_X_L_M, sizeof(block), block);
	}

	// Combine readings for each axis.
	*m = (int16_t)(block[0] | block[1] << 8);
	*(m+1) = (int16_t)(block[2] | block[3] << 8);
	*(m+2) = (int16_t)(block[4] | block[5] << 8);

}


void readGYR(int *g)
{
	uint8_t block[6];
	if (LSM9DS0){
		selectDevice(file,LSM9DS0_GYR_ADDRESS);
		readBlock(0x80 |  LSM9DS0_OUT_X_L_G, sizeof(block), block);
	}
	else if (LSM9DS1){
		selectDevice(file,LSM9DS1_GYR_ADDRESS);
		readBlock(0x80 |  LSM9DS1_OUT_X_L_G, sizeof(block), block);
	}

	// Combine readings for each axis.
	*g = (int16_t)(block[0] | block[1] << 8);
	*(g+1) = (int16_t)(block[2] | block[3] << 8);
	*(g+2) = (int16_t)(block[4] | block[5] << 8);
}


void writeAccReg(uint8_t reg, uint8_t value)
{
	if (LSM9DS0)
		selectDevice(file,LSM9DS0_ACC_ADDRESS);
	else if (LSM9DS1)
		selectDevice(file,LSM9DS1_ACC_ADDRESS);
	int result = i2c_smbus_write_byte_data(file, reg, value);
	if (result == -1){
		printf ("Failed to write byte to I2C Acc.");
        	return;
    }
}

void writeMagReg(uint8_t reg, uint8_t value)
{
	if (LSM9DS0)
		selectDevice(file,LSM9DS0_MAG_ADDRESS);
	else if (LSM9DS1)
		selectDevice(file,LSM9DS1_MAG_ADDRESS);
	int result = i2c_smbus_write_byte_data(file, reg, value);
	if (result == -1){
		printf("Failed to write byte to I2C Mag.");
		return;
	}
}


void writeGyrReg(uint8_t reg, uint8_t value)
{
	if (LSM9DS0)
		selectDevice(file,LSM9DS0_GYR_ADDRESS);
	else if (LSM9DS1)
		selectDevice(file,LSM9DS1_GYR_ADDRESS);
	int result = i2c_smbus_write_byte_data(file, reg, value);
	if (result == -1){
		printf("Failed to write byte to I2C Gyr.");
		return;
	}
}



void detectIMU()
{

	__u16 block[I2C_SMBUS_BLOCK_MAX];

	int res, bus,  size;


	char filename[20];
	sprintf(filename, "/dev/i2c-%d", 1);
	file = open(filename, O_RDWR);
	if (file<0) {
		printf("Unable to open I2C bus!");
			return;
	}

	//Detect if BerryIMUv1 (Which uses a LSM9DS0) is connected
	selectDevice(file,LSM9DS0_ACC_ADDRESS);
	int LSM9DS0_WHO_XM_response = i2c_smbus_read_byte_data(file, LSM9DS0_WHO_AM_I_XM);*/

	selectDevice(file,LSM9DS0_GYR_ADDRESS);
	int LSM9DS0_WHO_G_response = i2c_smbus_read_byte_data(file, LSM9DS0_WHO_AM_I_G);

	if (LSM9DS0_WHO_G_response == 0xd4 /*&& LSM9DS0_WHO_XM_response == 0x49*/){
		printf ("\n\n\n#####   BerryIMUv1/LSM9DS0  DETECTED    #####\n\n");
		LSM9DS0 = 1;
	}




	//Detect if BerryIMUv2 (Which uses a LSM9DS1) is connected
	selectDevice(file,LSM9DS1_MAG_ADDRESS);
	int LSM9DS1_WHO_M_response = i2c_smbus_read_byte_data(file, LSM9DS1_WHO_AM_I_M);

	selectDevice(file,LSM9DS1_GYR_ADDRESS);
	int LSM9DS1_WHO_XG_response = i2c_smbus_read_byte_data(file, LSM9DS1_WHO_AM_I_XG);

    if (LSM9DS1_WHO_XG_response == 0x68 && LSM9DS1_WHO_M_response == 0x3d){
		printf ("\n\n\n#####   BerryIMUv2/LSM9DS1  DETECTED    #####\n\n");
		LSM9DS1 = 1;
	}


	if (!LSM9DS0 && !LSM9DS1){
		printf ("NO IMU DETECTED\n");
		return;
	}
}




void enableIMU()
{

	if (LSM9DS0){//For BerryIMUv1
		// Enable accelerometer.
		writeAccReg(LSM9DS0_CTRL_REG1_XM, 0b01100111); //  z,y,x axis enabled, continuous update,  100Hz data rate
		writeAccReg(LSM9DS0_CTRL_REG2_XM, 0b00100000); // +/- 16G full scale

		//Enable the magnetometer
		writeMagReg(LSM9DS0_CTRL_REG5_XM, 0b11110000); // Temp enable, M data rate = 50Hz
		writeMagReg(LSM9DS0_CTRL_REG6_XM, 0b01100000); // +/-12gauss
		writeMagReg(LSM9DS0_CTRL_REG7_XM, 0b00000000); // Continuous-conversion mode

		// Enable Gyro
		writeGyrReg(LSM9DS0_CTRL_REG1_G, 0b00001111); // Normal power mode, all axes enabled
		writeGyrReg(LSM9DS0_CTRL_REG4_G, 0b00110000); // Continuos update, 2000 dps full scale
	}

	if (LSM9DS1){//For BerryIMUv2
		// Enable the gyroscope
		writeGyrReg(LSM9DS1_CTRL_REG4,0b00111000);      // z, y, x axis enabled for gyro
		writeGyrReg(LSM9DS1_CTRL_REG1_G,0b10111000);    // Gyro ODR = 476Hz, 2000 dps
		writeGyrReg(LSM9DS1_ORIENT_CFG_G,0b10111000);   // Swap orientation

		// Enable the accelerometer
		writeAccReg(LSM9DS1_CTRL_REG5_XL,0b00111000);   // z, y, x axis enabled for accelerometer
		writeAccReg(LSM9DS1_CTRL_REG6_XL,0b00101000);   // +/- 16g

		//Enable the magnetometer
		writeMagReg(LSM9DS1_CTRL_REG1_M, 0b10011100);   // Temp compensation enabled,Low power mode mode,80Hz ODR
		writeMagReg(LSM9DS1_CTRL_REG2_M, 0b01000000);   // +/-12gauss
		writeMagReg(LSM9DS1_CTRL_REG3_M, 0b00000000);   // continuos update
		writeMagReg(LSM9DS1_CTRL_REG4_M, 0b00000000);   // lower power mode for Z axis
	}
}


void  INThandler(int sig)// Used to do a nice clean exit when Ctrl-C is pressed
{
	signal(sig, SIG_IGN);
	exit(0);
}

int mymillis()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec) * 1000 + (tv.tv_usec)/1000;
}

int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;
    return (diff<0);
}

int main(int argc, char *argv[])
{


	float rate_gyr_y = 0.0;   // [deg/s]
	float rate_gyr_x = 0.0;   // [deg/s]
	float rate_gyr_z = 0.0;   // [deg/s]

	int  accRaw[3];
	int  magRaw[3];
	int  gyrRaw[3];

	//drift calculators
	float driftx = 0.0;
	float drifty = 0.0;
	float driftz = 0.0;
	float gyroXprev = 0.0;
	float gyroYprev = 0.0;
	float gyroZprev = 0.0;
	int count = 0;

	float gyroXangle = 0.0;
	float gyroYangle = 0.0;
	float gyroZangle = 0.0;
	float est_drift_x = 0.0;
	float est_drift_y = 0.0;
	float est_drift_z = 0.0;

	float AccYangle = 0.0;
	float AccXangle = 0.0;
	float CFangleX = 0.0;
	float CFangleY = 0.0;

	int startInt  = mymillis();
	int startTime = startInt;
	struct  timeval tvBegin, tvEnd,tvDiff;


	signal(SIGINT, INThandler);

	detectIMU();
	enableIMU();

	gettimeofday(&tvBegin, NULL);


	while(mymillis()-startTime <= 60000)
	{
		startInt = mymillis();


		//read ACC and GYR data
		readACC(accRaw);
		readGYR(gyrRaw);

		//Convert Gyro raw to degrees per second
		rate_gyr_x = (float) gyrRaw[0] * G_GAIN;
		rate_gyr_y = (float) gyrRaw[1]  * G_GAIN;
		rate_gyr_z = (float) gyrRaw[2]  * G_GAIN;

		//store prev values of each angle
		gyroXprev = gyroXangle;
		gyroYprev = gyroYangle;
		gyroZprev = gyroZangle;

		//Calculate the angles from the gyro
		gyroXangle+=rate_gyr_x*DT - est_drift_x;
		gyroYangle+=rate_gyr_y*DT - est_drift_y;
		gyroZangle+=rate_gyr_z*DT - est_drift_z;

		//calculate relative drift over time
		driftx += gyroXangle - gyroXprev;
		drifty += gyroYangle - gyroYprev;
		driftz += gyroZangle - gyroZprev;

		//Convert Accelerometer values to degrees
		AccXangle = (float) (atan2(accRaw[1],accRaw[2])+M_PI)*RAD_TO_DEG;
		AccYangle = (float) (atan2(accRaw[2],accRaw[0])+M_PI)*RAD_TO_DEG;

		//Change the rotation value of the accelerometer to -/+ 180 and move the Y axis '0' point to up.
		//Two different pieces of code are used depending on how your IMU is mounted.
		//If IMU is upside down
		/*
			if (AccXangle >180)
					AccXangle -= (float)360.0;
			AccYangle-=90;
			if (AccYangle >180)
					AccYangle -= (float)360.0;
		*/

		//If IMU is up the correct way, use these lines
		AccXangle -= (float)180.0;
		if (AccYangle > 90)
				AccYangle -= (float)270;
		else
			AccYangle += (float)90;


		//Complementary filter used to combine the accelerometer and gyro values.
		CFangleX=AA*(CFangleX+rate_gyr_x*DT) +(1 - AA) * AccXangle;
		CFangleY=AA*(CFangleY+rate_gyr_y*DT) +(1 - AA) * AccYangle;

		//printf ("   GyroX  %7.3f \t AccXangle \e[m %7.3f \t \033[22;31mCFangleX %7.3f\033[0m\t GyroY  %7.3f \t AccYangle %7.3f \t \033[22;36mCFangleY %7.3f\t\033[0m\n",gyroXangle,AccXangle,CFangleX,gyroYangle,AccYangle,CFangleY);
		//printf ("   GyroX  %7.3f \t GyroY  %7.3f \t GyroZ  %7.3f \n",gyroXangle,gyroYangle,gyroZangle);
		printf ("q0 = %7.3f \t q1 = %7.3f \t q2 = %7.3f \t q3 = %7.3f \n", q[0], q[1], q[2], q[3]);

		//Each loop should be at least 20ms.
		while(mymillis() - startInt < (DT*60000)){
				usleep(100);
		}
		count++;
		printf("Loop Time %d\t", mymillis()- startInt);
    }
    //printf("average Xdrift = %f \t Ydrift = %f \t Zdrift = %f \n", driftx/count, drifty/count, driftz/count);
}

void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz)
        {
            float q1 = q[0], q2 = q[1], q3 = q[2], q4 = q[3];   // short name local variable for readability
            float norm;
            float hx, hy, _2bx, _2bz;
            float s1, s2, s3, s4;
            float qDot1, qDot2, qDot3, qDot4;

            // Auxiliary variables to avoid repeated arithmetic
            float _2q1mx;
            float _2q1my;
            float _2q1mz;
            float _2q2mx;
            float _4bx;
            float _4bz;
            float _2q1 = 2.0f * q1;
            float _2q2 = 2.0f * q2;
            float _2q3 = 2.0f * q3;
            float _2q4 = 2.0f * q4;
            float _2q1q3 = 2.0f * q1 * q3;
            float _2q3q4 = 2.0f * q3 * q4;
            float q1q1 = q1 * q1;
            float q1q2 = q1 * q2;
            float q1q3 = q1 * q3;
            float q1q4 = q1 * q4;
            float q2q2 = q2 * q2;
            float q2q3 = q2 * q3;
            float q2q4 = q2 * q4;
            float q3q3 = q3 * q3;
            float q3q4 = q3 * q4;
            float q4q4 = q4 * q4;

            // Normalise accelerometer measurement
            norm = sqrt(ax * ax + ay * ay + az * az);
            if (norm == 0.0f) return; // handle NaN
            norm = 1.0f/norm;
            ax *= norm;
            ay *= norm;
            az *= norm;

            // Normalise magnetometer measurement
            norm = sqrt(mx * mx + my * my + mz * mz);
            if (norm == 0.0f) return; // handle NaN
            norm = 1.0f/norm;
            mx *= norm;
            my *= norm;
            mz *= norm;

            // Reference direction of Earth's magnetic field
            _2q1mx = 2.0f * q1 * mx;
            _2q1my = 2.0f * q1 * my;
            _2q1mz = 2.0f * q1 * mz;
            _2q2mx = 2.0f * q2 * mx;
            hx = mx * q1q1 - _2q1my * q4 + _2q1mz * q3 + mx * q2q2 + _2q2 * my * q3 + _2q2 * mz * q4 - mx * q3q3 - mx * q4q4;
            hy = _2q1mx * q4 + my * q1q1 - _2q1mz * q2 + _2q2mx * q3 - my * q2q2 + my * q3q3 + _2q3 * mz * q4 - my * q4q4;
            _2bx = sqrt(hx * hx + hy * hy);
            _2bz = -_2q1mx * q3 + _2q1my * q2 + mz * q1q1 + _2q2mx * q4 - mz * q2q2 + _2q3 * my * q4 - mz * q3q3 + mz * q4q4;
            _4bx = 2.0f * _2bx;
            _4bz = 2.0f * _2bz;

            // Gradient decent algorithm corrective step
            s1 = -_2q3 * (2.0f * q2q4 - _2q1q3 - ax) + _2q2 * (2.0f * q1q2 + _2q3q4 - ay) - _2bz * q3 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q4 + _2bz * q2) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q3 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
            s2 = _2q4 * (2.0f * q2q4 - _2q1q3 - ax) + _2q1 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q2 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + _2bz * q4 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q3 + _2bz * q1) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q4 - _4bz * q2) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
            s3 = -_2q1 * (2.0f * q2q4 - _2q1q3 - ax) + _2q4 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q3 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + (-_4bx * q3 - _2bz * q1) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q2 + _2bz * q4) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q1 - _4bz * q3) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
            s4 = _2q2 * (2.0f * q2q4 - _2q1q3 - ax) + _2q3 * (2.0f * q1q2 + _2q3q4 - ay) + (-_4bx * q4 + _2bz * q2) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q1 + _2bz * q3) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q2 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
            norm = sqrt(s1 * s1 + s2 * s2 + s3 * s3 + s4 * s4);    // normalise step magnitude
            norm = 1.0f/norm;
            s1 *= norm;
            s2 *= norm;
            s3 *= norm;
            s4 *= norm;

            // Compute rate of change of quaternion
            qDot1 = 0.5f * (-q2 * gx - q3 * gy - q4 * gz) - beta * s1;
            qDot2 = 0.5f * (q1 * gx + q3 * gz - q4 * gy) - beta * s2;
            qDot3 = 0.5f * (q1 * gy - q2 * gz + q4 * gx) - beta * s3;
            qDot4 = 0.5f * (q1 * gz + q2 * gy - q3 * gx) - beta * s4;

            // Integrate to yield quaternion
            q1 += qDot1 * deltat;
            q2 += qDot2 * deltat;
            q3 += qDot3 * deltat;
            q4 += qDot4 * deltat;
            norm = sqrt(q1 * q1 + q2 * q2 + q3 * q3 + q4 * q4);    // normalise quaternion
            norm = 1.0f/norm;
            q[0] = q1 * norm;
            q[1] = q2 * norm;
            q[2] = q3 * norm;
            q[3] = q4 * norm;

        }
