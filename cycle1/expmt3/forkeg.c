#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t id = getpid();
	printf("%d \n",id );
	int k = fork();
	if (k == 0)
	{
		printf("Child process\n");
		printf("child 2\n");
		pid_t id3 = getpid();
		
		printf("%d \n",id3 );
		exit(0);
	}
	else
	{
		printf("parent process\n");
		pid_t id2 = getpid();
		printf("%d \n",id2 );
		exit(0);
	}
}