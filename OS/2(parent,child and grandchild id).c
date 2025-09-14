#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>

int main(){
    pid_t pid, ppid, cpid, gpid;

    cpid = fork(); 

    if (cpid < 0) {
        printf("\nError at fork (child)\n");
        return 0;
    }   
    else if (cpid == 0) {
        pid = getpid();
        ppid = getppid();
        printf("\nI am the child PID -> %d\n", pid);
        printf("I am the parent PPID -> %d\n",ppid);

        gpid = fork(); 

        if (gpid < 0) {
            printf("\nError at fork (grandchild)\n");
            return 0;
        } 
        else if (gpid == 0) {
            pid = getpid();
            ppid = getppid();
            printf("\nI am the grandchild process id (PID) -> %d\n", pid);
            printf("My parent's ID (PPID) -> %d\n",ppid);
        }

    } 
    else {
        pid = getpid();
        ppid = getppid();
        printf("\nI am the process id (PID): %d\n", pid);

    }

    return 0;
}

// Output:

// I am the process id (PID): 7801

// I am the child PID -> 7802
// I am the parent PPID -> 7801
// dsu@dsu-Precision-3460:~$ 
//I am the grandchild process id (PID) -> 7803
//My parent's ID (PPID) -> 7802
