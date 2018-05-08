#include <stdio.h>
#include <unistd.h>

int main()
{
	for(int i=0; i < 4; i++) { /* will be printed at the end when program returns*/
		printf(".");
		sleep(1);
	}

	for(int i=0; i < 2; i++) {
		fprintf (stderr, "Akshay");
		sleep (1);
	}

	for(int i=0; i < 2; i++) {
		fprintf (stdout, "||");
		fflush(stdout); /* will flush stdout buffer data from before first. Even a \n would do */
		sleep (1);
	}
	return 0;
}