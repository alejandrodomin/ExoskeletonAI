#include <stdlib.h>
#include <stdio.h>

#define DEBUG 1  

int main(){
	#undef DEBUG	// compiler directives seem to have no scope
	#define DEBUG 0
	#if DEBUG
		printf("Hello.");
	#else
		printf("Bye");
	#endif
	return 0;
}
