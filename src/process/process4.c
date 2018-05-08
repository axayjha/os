#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

int main(int argc, char **argv)
{	
	int p;
	p = fork();
	if(p == 0)
	{
		printf("CHild process\n");
		sleep(5);
		printf("Orphan process\n");
		
	}	
	else if(p>0)
		printf("parent process\n");
	else
		printf("error\n");
	return 0;
}

