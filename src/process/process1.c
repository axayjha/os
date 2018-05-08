#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

int main(int argc, char **argv)
{
	int p=fork();
	if(p == 0)
	{
		printf("%d\n", getpid());
		printf("%d\n", getppid());
	}
	return 0;
}

