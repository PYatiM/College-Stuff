#include<stdio.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include <fcntl.h> 

void main()  { 
    char buff; 
	int fd,fd1; 
	fd=open("one.txt",O_RDONLY); 
	fd1=open("two.txt",O_WRONLY|O_CREAT); 
	while(read(fd,&buff,1)) 
	write(fd1,&buff,1); 
	printf("The copy of a file is successed"); 
	close(fd); 
	close(fd1); 
}

// OUTPUT

// CONTENT OF FILE 1:
// HELLO I AM THE CONTENT OF THIS FILE

// The copy of a file is successful

// CONTENT OF FILE 2:
// HELLO I AM THE CONTENT OF THIS FILE
