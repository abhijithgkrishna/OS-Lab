#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	char *args[]={"./execdemo",NULL};
	execvp(args[0],args);
	printf("End\n");
}