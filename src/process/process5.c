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
		
		
	}	
	else if(p>0)
	{	
		sleep(5);
		printf("parent process\n");
		printf("Zombie process\n");
		while(1){};
	}
	else
		printf("error\n");
	return 0;
}

