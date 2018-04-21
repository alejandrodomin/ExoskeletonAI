#include <gyroscope.h>

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