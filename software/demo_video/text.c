#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main ( void ) {
  	int gpios[] = {3,5,7,8,10,11,12,13,15,16,18,19,21,22,23,24,26,29,31,32,33,35,36,37,38,40};
  	printf("Raspberry Pi wiringPi blink test\n");

  	if (wiringPiSetup() == -1) {
    		printf( "Setup didn't work... Aborting.\n" );
    		exit (1);
  	}
	else printf("Setup worked\n");

  	int a;
  	for(a = 0; a < (sizeof(gpios) / sizeof(int)); a++)
  	{
    		pinMode(gpios[a], OUTPUT);
  	}


  	int i;
	for ( i=0; i<10; i++ ) {
		for(a = 0; a < (sizeof(gpios) / sizeof(int)); a++)
		{
			printf("Pin %d\n", gpios[a]);
   			digitalWrite(gpios[a], 1);
    			delay(250);

    			digitalWrite(gpios[a], 0);
    			delay(250);
  		}
	}

	return 0;
}
