#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define FILENAME_SIZE 20

int main(int argc, char **argv, char **env)
{
   int file;
   char filename[FILENAME_SIZE];

   sprintf(filename, "/dev/i2c-%d", 1);
   file = open(filename, O_RDWR);
   if (file<0) {
        printf("Unable to open I2C bus!\n");
        exit(1);
   }
   else printf("I2C device open\n.");

   if (ioctl(file, I2C_SLAVE, 0b1101010) < 0) {
        printf("Error: Could not select gyroscope\n");
   }
   else printf("Gyroscope succesfully selected.\n");

   return 0;
}