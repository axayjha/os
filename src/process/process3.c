#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

int main(int argc, char **argv)
{	
	fork();
	fork();
	printf("ABCD\n");
		
	return 0;
}

