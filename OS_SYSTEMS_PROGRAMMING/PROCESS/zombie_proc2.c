/*
This program shows
1. how to make a zombie process ?
2. how to let the init process remove the zombie process from the list ?
*/


#include<unistd.h>
#include<stdio.h>

int main(){

	pid_t pid;
	int termstatus;

	pid = fork();

	/* the child has association with the parent until the parent terminates or calls wait() to collect the termination status 
		of the child.
		on the termination of the child process the SIGCHLD signal is raised which the parent is supposed to collect

		if the parent terminates now then the child becomes ORPHAN + ZOMBIE...so now init process becomes its parent
		and since init will surely gonna collect the termination status the process is removed from the process list
	*/


	if(pid==-1){
		printf("Error creating process");	
	}		

	if(pid==0){
		printf("\nI am the child process with pid = %d\n\n",getpid());
	}
	
	if(pid > 0){
		printf("\n\nI am parent process with pid = %d\n",getpid());
	
		sleep(1);
		system("ps axjf | grep 'a.out'");
		printf("\n\nSince parent didn't collect the termination status of child is shown as defunctional or zombie\n");
		printf("\nnow lets terminate the parent process without collecting termination status so that the child becomes ZOMBIE + ORPHAN...so init() becomes the next parent and init() will automatically collect the termination status of the child and remove it from the zombie list\n\n");

		sleep(6); //just to make the output more readable...not of any use as such 
		printf("\n\nParent is terminated..now run this command \"ps axjf | grep '<defunct>'\"..u won't see any zombies as earlier..only the grep process is shown\n\n");
	}

	return 0;
}
