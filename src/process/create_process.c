#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
	pid_t pid, cpid;

	/* fork a child process */
	pid = fork();

	if (pid < 0) {	/* error occurred */
		fprintf(stderr, "Fork failed\n");
		return 1;
	}
	else if (pid == 0) { /* child process */
		execlp("/bin/ls", "ls", NULL);
	}
	else {	/* parent process */
		/* parent will wait for child to complete */
		cpid = wait(NULL);
		printf("Child complete\n");
	}
	printf("Parent pid = %d\n", getpid());
    printf("Child pid = %d\n", cpid);
	return 0;
}