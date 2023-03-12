#include <stdlib.h>
#include <fcntl.h>
#include<unistd.h>
#include <stdio.h>
 
int main()
{
    size_t filedesc = open("testfile.txt", O_WRONLY | O_CREAT);
    if(filedesc < 0)
    {	
    	printf("Outside Close\n");
    	return 1;
    }
 
    if(close(filedesc) < 0)	
    {
    	printf("Inside close\n");
		return 1;
	}
	else
	{
		printf("File is there.\n");
	}
 
    return 0;
}