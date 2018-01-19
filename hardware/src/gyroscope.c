#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define FILENAME_SIZE 20

void readGYR(int *g);

int main(int argc, char **argv, char **env)
{
   int file;
   int *g;
   char filename[FILENAME_SIZE];

   sprintf(filename, "/dev/i2c-%d", 1);
   file = open(filename, O_RDWR);
   if (file<0) {
        printf("Unable to open I2C bus!\n");
        exit(1);
   }
   else printf("I2C device open.\n");

   if (ioctl(file, I2C_SLAVE, 0b1101010) < 0) {
        printf("Error: Could not select gyroscope\n");
   }
   else printf("Gyroscope succesfully selected.\n");

   writeGyrReg(CTRL1, 0b00001111); // Normal power mode, all axes enabled
   writeGyrReg(CTRL4, 0b00110000); // Continuos update, 2000 dps full scale

   readGYR(g);

   rate_gyr_x = (float) gyrRaw[0] * G_GAIN;
   rate_gyr_y = (float) gyrRaw[1]  * G_GAIN;
   rate_gyr_z = (float) gyrRaw[2]  * G_GAIN;

   gyroXangle+=rate_gyr_x*DT;
   gyroYangle+=rate_gyr_y*DT;
   gyroZangle+=rate_gyr_z*DT;

   return 0;
}

void readGYR(int *g)
{
    uint8_t block[6];
 
        selectDevice(file,GYR_ADDRESS);
 
    readBlock(0x80 | OUT_X_L_G, sizeof(block), block);
 
        *g = (int16_t)(block[0] | block[1] << 8);
        *(g+1) = (int16_t)(block[2] | block[3] << 8);
        *(g+2) = (int16_t)(block[4] | block[5] << 8);
}