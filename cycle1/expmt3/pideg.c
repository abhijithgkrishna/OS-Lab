#include <stdio.h>
#include <unistd.h>

void main()
{
	if (fork() == 0)
	{
		printf("Process id of process is : %d \n",getpid());
	}
}