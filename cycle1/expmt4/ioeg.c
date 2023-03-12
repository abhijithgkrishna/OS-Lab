#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

int main (void)
{
	int fd[2];
	char buf1[14] = "hello world \n";
	char buf2[14];
	
	fd[0] = open("test.txt", O_RDWR);		
	fd[1] = open("test.txt", O_RDWR);
	
	write(fd[0], buf1, strlen(buf1));		
	write(1, buf2, read(fd[1], buf2, 14));

	close(fd[0]);
	close(fd[1]);

	return 0;
}