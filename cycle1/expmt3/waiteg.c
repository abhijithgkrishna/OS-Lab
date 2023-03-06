#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
	int pid=fork(); //creating child
	if(pid<0)
	{
			printf("fork failed!\n");
	}
	else if(pid==0)
	{
		printf("\nchild process %d executing\n",getpid());
		printf("calling program prg.c from child using exec\n");
		char* argv[]={"prg",NULL};
		execv("./prg",argv);
	}
	else
	{
		printf("parent process %d executing\n",getpid());
		int status = 1;
		printf("parent waiting for child to terminate\n");
		int pid=wait(&status);
		printf("child process %d exited-parent wait over\n",pid);
		printf("parent process %d exits\n",getpid());
	}
}

