#include<unistd.h>
#include<stdio.h>

int main(){

	//pid_t is defined as a "signed integer" in GNU library
	pid_t pid;		

	//parent's code segment starts from here
	pid = fork();

	//child's code segment starts from here	
	switch(pid){
		case -1:	printf("\nError in creating process");
					break;
		case 0:     printf("\n\nI am child with pid = %d...parent pid = %d\n",getpid(),getppid());
					break;
		default:	printf("\n\nI am parent with pid = %d\n",getpid());
	}
	return 0;
}
