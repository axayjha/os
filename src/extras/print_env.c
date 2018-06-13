#include <stdio.h>
#include <stdlib.h>
/*  The ENVIRON variable contains the environment.*/
extern char** environ;
int main ()
{
	char** var;
	for (var = environ; *var != NULL; ++var)
		printf ("%s\n", *var);
	printf ("%s\n", getenv("SHELL"));
	printf ("%s\n", getenv("_"));
	return 0;
}