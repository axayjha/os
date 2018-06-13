/*
	stdout is buffered. Data written to stdout is not sent to the console
	(or other device, if it’s redirected) until the buffer fills, 
	the program exits normally, orstdout is closed.
	You can explicitly flush the buffer by calling the following:
	fflush (stdout);
	In contrast, stderr is not buffered; data written to
	stderr goes directly to the console.

*/


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