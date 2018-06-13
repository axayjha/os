#include <stdio.h>
#include <stdlib.h>
int main ()
{
	char* server_name = getenv ("SERVER_NAME");
	if (server_name == NULL)
		/*  The SERVER_NAME environment variable was not set.
			Use the default. */
		server_name = "server.my-company.com";
	
	printf ("accessing server %s\n", server_name);
	/* Access the server here... */
	return 0;
}