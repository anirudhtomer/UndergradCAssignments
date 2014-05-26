#include<stdio.h>
#include<unistd.h>

int main(){
	
	pid_t pid;

	pid = fork();

	switch(pid){
		case -1:	printf("Error in creating child");	
					break;

		case 0:		printf("\n\nI am child with pid = %d\n",getpid());
				sleep(2);
				printf("\nchild orphaned... parent terminated without waiting for child to terminate\n\n");	
				printf("now child has init as its new parent with pid = %d\n\n",getppid());
				system("ps axjf | grep 'a.out'");							
				printf("\n\nPress enter key to continue..\n\n");
				break;

		default:	printf("\n\nI am the original parent with pid = %d\n",getpid());
				system("ps axjf | grep 'a.out'");							

	}

	return 0;
}
