#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(){
  pid_t pid = fork();

  if(pid<0){
    fprintf(stderr,"Failed");
    return 1;
  }
  else if(pid==0){
    execlp("ls","ls",NULL);
    fprintf(stderr,"Execlp Failed\n");
    exit(1);
  }
  else{
    wait(NULL);
    printf("Child complete \n");
  }
  return 0;
}


//Output:
//  1a.c	 3.c	    anuraj		   dfsexp.c	   ENG24CY0126						 first	     kaveen.c			       nar.jpg	 one.txt   program2a.c	 two.txt
//  1.b.c	 4.c	    a.out		   Downloads	   E-Note_35522_Content_Document_20250429105205AM.docx	 first.c     lab.c			       n.c	 os1.c	   rakesh.c	 varsha
//  1.c	 5.c	    cloudd		   edd.pem	   exp2.c						 hi.c	     mariko_credentials.csv	       newc	 os3.c	   right.c
//  2a	 abcd	   'DAA LAB MANUAL.docx'   eng23cy0099.c   exp3.c						 InRelease   matrix.c			       new.py	 os.com    snap
//  2.c	 amithero   dfs.c		   eng24cy0017	   exp4.c						 k	     mongodb-mongosh_2.5.0_amd64.deb   nn.c	 program   tn.c
// Child complete 
