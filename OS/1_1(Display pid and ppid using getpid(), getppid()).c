#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>

int main(){
  pid_t pid,ppid;

  pid = getpid();
  ppid = getppid();

  printf("Process ID (pid) -> %d\n",pid);
  printf("Parent Process ID (ppid) -> %d\n",ppid);

  return 0;
}


//Output:

//Process ID (pid) -> 9349
//Parent Process ID (ppid) -> 6659
