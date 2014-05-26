#include<unistd.h>
#include<stdio.h>

int main(){
	
	pid_t pid;
	int termstatus;

	pid = fork();

	/* once the child terminates the SIGCHLD signal is raised by the kernel for the parent process..so we have to collect it...coz by default
	   it is ignored 
	*/

	if(pid==-1)
		printf("error in creating a new process");
	
	if(pid==0){
		printf("\nI am the child process with pid = %d\n\n",getpid());
	}
	
	if(pid > 0){
		
		printf("\n\nI am parent process with pid = %d\n",getpid());
		wait(&termstatus);
				
		system("ps axjf | grep 'a.out'");
		printf("\n\nAs u can see there is no zombie process coz we collected child's termination status\n\n");
	}


}
