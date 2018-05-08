#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

int main(int argc, char **argv)
{
	int p, i=5;
	printf("pos 1: %d\n", p);
	p=fork();
	printf("pos 2: %d\n", p);
	if(p == 0)
		printf("Child process: %d\n", ++i);
	if(p>=0){
		printf("Parent process: %d\n", i);
		printf("pos 3: %d\n", p);
	}
	else
		printf("Error\n");
//	if(p < 0)
//		printf("Hello\n");
	return 0;
}

