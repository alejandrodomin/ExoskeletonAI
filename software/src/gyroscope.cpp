LSM9DS1 imuInit(float* gyro, float* accel, float* mag, int index){

	LSM9DS1 imu(IMU_MODE_I2C, 0x6a, 0x1c);
	imu.begin();
	if (!imu.begin()){
		fprintf(stderr, "Failed to communicate with LSM9DS1.\n");
		exit(EXIT_FAILURE);
	}
	imu.calibrate();
	return imu;
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
