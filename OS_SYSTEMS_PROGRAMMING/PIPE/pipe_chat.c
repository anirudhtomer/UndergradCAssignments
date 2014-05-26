/* program for chat between parent and child using pipe */

/* while running this program u may encounter a warning saying gets() is dangerous and must not be used...
okay fine unless I don't put a string greater than the size of the buffer gets works fine */

#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(){

	pid_t pid;
	int fd[2];
	int termstat;
	char buff_parent[50]="";
	char buff_child[50]="";
		
	pipe(fd);
	
	pid = fork();
	
	if(pid==-1){
		printf("Error while creating child");
	}	

	
	// u wanna make it as good as a chat on gmail...use multithreading...and multibuffers...a single buffer won't do.

	if(pid > 0){
		
		printf("\n\nParent: Ready for chat...\n\n");
				
		sleep(1); //to let the child get initialized
	
		printf("\n\nChat Rule: type \"bye\" for exiting...and parent is always the initiator of the chat\n\n");
		printf("PLEASE DO NOT PRESS ENTER FASTER THEN THE OCCURANCE OF A SECOND (1 sec) or the working would be undefined\n\n");
		printf("Message length should not exceed 50 characters...(why do we always think of crashing programs ?)");
		while(strcasecmp(buff_parent,"bye")){
			printf("\nType message to be sent to child:\t");
			gets(buff_parent);
			write(fd[1],buff_parent,50); 
			// even if I send strlen(buff_parent) as the length of the data instead of 50, the receiver won't be able to know that in advance...

			if(!strcasecmp(buff_parent,"bye")){
				break;
			}
			
			//this sleep coz it lets child to read the msg...otherwise parent would read its own msg
			sleep(1);
					
			read(fd[0],buff_parent,50); // since I donno how much is the data being received...I read all the 50 bytes
			printf("\nMessage from child to parent: %s",buff_parent);
		}

		close(fd[0]);
		close(fd[1]);

		wait(&termstat);
		printf("\nParent: Child terminated..now I am about to terminate\n\n");
	}

	if(pid == 0){
		
	/*arey this msg is not for just time pass han...if I do not put such a msg then people would start typing before the 
	 code in the parent process asks them to */		  	
		
		printf("\n\nChild: getting initialized for chat...plz wait\n\n");
		
		while(strcasecmp(buff_child,"bye")){
			read(fd[0],buff_child,50);
			printf("\nMessage from parent to child: %s",buff_child);
		
			if(!strcasecmp(buff_child,"bye")){
				write(fd[1],buff_child,50);				
				break;
			}
			
			printf("\nType message to be sent to parent:\t");
			gets(buff_child);
			write(fd[1],buff_child,50); 
		
			//this sleep coz it lets parent to read ur msg...otherwise u will read ur own msg
			sleep(1);
		}
		close(fd[0]);
		close(fd[1]);						
	}
	

	return 0;
}
