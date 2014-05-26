/*
This program shows
1. how to make a zombie process ?
2. how to remove that zombie process from the list by calling wait from the parent process

*/


#include<unistd.h>
#include<stdio.h>

int main(){

	pid_t pid;
	int termstatus;

	pid = fork();

	/*      
		the child has association with the parent until the parent terminates or calls wait() to collect the termination status 
		of the child.
		on the termination of the child process the SIGCHLD signal is raised which the parent is supposed to collect

		if the parent terminates now then the child becomes ORPHAN + ZOMBIE...so now init process becomes its parent
		and since init will surely gonna collect the termination status the process is removed from the process list

		The following lines from WIKIPEDIA::

		When a child process terminates before the parent has called wait, the kernel retains some information about the process to enable its parent to call wait later. Because the child is still consuming system resources but not executing it is known as a zombie process.
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
		printf("\nnow lets collect the termination status by calling wait\n\n");

		sleep(2); //I have added this sleep() here so that output can be read easily...I mean u get the time to read the output.
		wait(&termstatus);
		system("ps axjf | grep 'a.out'");
		printf("\n\nAs u can see the <defunct> or zombie process is removed coz we collected its termination status\n\n");
	}

	return 0;
}
