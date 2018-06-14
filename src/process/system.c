#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int return_value;
	return_value = system ("ls -l /");
	return return_value;	
}