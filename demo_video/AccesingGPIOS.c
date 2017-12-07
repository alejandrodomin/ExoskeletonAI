#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
  	FILE * fp = NULL;

	if(argc < 1)
	{
		puts("Not enough arguments.");
		puts("\t Format AccesingGPIOS [filepath] [arguments]");
		puts("\t [-r] opens existing file for reading");
		puts("\t [-w] opens text file for writing");
		puts("\t [-a] opens file for appending writing");
		puts("\t [-r+] opens a file for reading and writing");
		puts("\t [-w+] opens a file for reading and writing but truncates it");
		puts("\t [-a+] opens a file for reading and writing, it creates it if it doesn't exist, and it appends");
		return 0;
	}
	else
	{
		fclose(fp);
	}

	return 0;
}
