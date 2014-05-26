/* program for sending data from parent to child using pipe */

#include<stdio.h>
#include<unistd.h>

int main(){

	pid_t pid;
	int fd[2];
	int termstat;
	char buff_parent[15] = "BE COMP1 Rocks";
	char buff_child[15];
		
	pipe(fd);

	/* 
		following info is copied from manual page "man 7 pipe"

		pipe has a limited capacity.
		check ur kernel version at home and college using the command "uname-r"
		all kernel with versions above 2.6.11-x are having pipe capacity = 65536 bytes.

		like at home I have ubuntu 10.04 karmic with kernel 2.6.32-25 so I have pipe capacity = 65536

		if college has an older kernel then it may be equal to the PAGE SIZE of the machine...
		I think they are i386 machines so  pipe size = page size = 4096 bytes
	
		the fd[0] is for reading & fd[1] the write end.		
	*/

	pid = fork();
	/* whenever a child is created with fork it gets its own set of file descriptors...
		so fd[0],fd[1] are not shared with child
	*/
	
	if(pid==-1){
		printf("Error while creating child");
	}	

	if(pid > 0){
		/* since parent is gonna only write into pipe there is no need of the read end...even if do not close it the program runs successfully
		   however there is no point in wasting resources unless u have a two way communication using pipe
		*/

		close(fd[0]);
		write(fd[1],buff_parent,15);
		printf("\nParent: sent the message \"%s\" to the child",buff_parent);
		printf("\n\nParent: Waiting for the child to terminate\n");
		wait(&termstat);
		printf("\nParent: Child terminated..now I am about to terminate\n\n");
	}

	if(pid == 0){
		//since the child is only gonna read from the pipe there is no need of the write end

		/* don't u think we should have a sleep() call here so that we let the parent write the data first...& then giving control to child process
		   actually there is no such need coz read blocks until the data is avaible so unless parent writes read won't execute
		*/
			
		close(fd[1]);
		read(fd[0],buff_child,15);
		printf("\nChild: I got the message \"%s\" from the parent\n\nChild: now I am terminating\n\n",buff_child);
		
	}
	

	return 0;
}
