/* program to send signal to child */

#include<stdio.h>
#include<signal.h>

void sighandler_child(int sig_num){
	printf("\n\nSignal %d caught by the process with pid =  %d\n",sig_num,getpid());	
}

int main(){

	pid_t pid;
	int termstatus;
	/*
		HISTORY: (I have copied it from NET)
		though this program is about SIGNALS...lemme talk something about SEMAPHORE

		Semaphores were first proposed by Edsger W. Dijkstra in 1968. 
		
		Dijkstra, a Dutchman, used 
			P for Wait() because P is the first letter of the Dutch word "passeren," which means "to pass," 
			V for Signal() because V is the first letter of the Dutch word "vrijgeven," which means "to release." 
	
		that's why we have SYSTEM V signals...where V is not roman 5 but is "V"--> "vrijgeven" used by dijkstra for Signal()

		all signals begin with SIG

	*/


	/*biggest misconception introduced by teachers:
	
	u have to establish the signal handler twice....
	nah! u have to establish it only for the process which catches the signal...
	why would I increase the code segment of the parent proces when I knw that its not gonna catch the signal at all...
	so establish handler in child only

	*/

	pid = fork();	

	if(pid==-1)
		printf("Error whlie creating child process");

	//parent sends the signal
	if(pid > 0){
		
		sleep(1); //to let the child establish the handler first
		printf("\n\nI am parent with pid = %d and I am sending the SIGUSR1 to the child with pid = %d\n",getpid(),pid);
		kill(pid,SIGUSR2);
		printf("\nParent: I have sent the signal to the child..gonna wait for the child to terminate\n");
		wait(&termstatus);
		printf("\n\nParent: Child terminated...now I am gonna terminate\n\n");
	}

	if(pid==0){

		/*   to establish the signal handler..
			the type of the second argument is "sighandler_t" which is actually a pointer to a function...
			 void (*sighandler_t)(int)

		*/
	
		if(signal(SIGUSR2,sighandler_child) == SIG_ERR){
			printf("\n\nError while establishing signal handler\n\n");
			return 2; //I donno what the exact return status should be..so I returned 2 randomly..I can't return 0 after an error 
		} 
	
		sleep(3); //to let the child wait for the parent to send signal

		printf("\nChild: I am exiting\n\n"); 

	}
		
		

	return 0;
}
