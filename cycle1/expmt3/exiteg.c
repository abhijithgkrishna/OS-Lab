#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main() 
{
	printf("Start \n");
	printf("Exiting\n ");
	if (fork() == 0)
	{
		printf("fork created\n");
		exit(getpid());
		printf("fork deleted\n");
	}
	
	printf("Exited\n");
}