/* proram to show use of Semaphores in process synchronisation
   we are using "System V Semaphore"...its not system 5... and we have binary semaphores here
   if resource is free then Semaphore value=1  else = -1
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/sem.h>

#define SEMCOUNT 1

/*
	A BIT OF THEORY(waise its much more than a bit)...

	create semaphore::
	actually the first argument is semaphore key...which is common across all processes in the OS.

	an example is: in my ubuntu I have these semaphores currently owned by the OS...
	the leftmost field is the key

	anirudh@anirudh-laptop:~/Desktop/OS_Ninja/SEMAPHORE$ ipcs -s

	------ Semaphore Arrays --------
	key        semid      owner      perms      nsems     
	0xffffffff 0          anirudh    600        8         
	0xcbc384f8 32769      anirudh    600        1         

	so when u create a semaphore u have two options...either u urself give a KEY or ask the system to allocate for u..
	if u give the key urself u have 2 options again...if that key already exists then join that semaphore set
	if not then give failure

	otherwise simplest is to use IPC_PRIVATE to let the system allocate the key for u...but this semaphore can't be shared with other processes
	since we first create semaphore & then call fork() our child gets the semaphore access too...
	for SYSTEM V SEMAPHORES...IPC_PRIVATE can be used
	
	IPC_CREAT tells the kernel to create a new semaphore set..however if already there is set of semaphores with the same key then
	it returns identifier for that set, so u get added to that set...if u give IPC_EXCL...it means I need a new semaphore set and 
	if there exists a set with the same key in the kernel then it gives failure...

	*/


int main(){
	
	pid_t pid;
	FILE *fp;
	int semid;
	int cnt = 5; //5 times for child and 5 times for parent, we print data into the file
	int termstat;

	char filename[11] = "sharedfile";

	struct sembuf WAIT[SEMCOUNT],SIGNAL[SEMCOUNT];  
	/* I have specifically created array of size 1 (semcount=1 #defined above)...just to make it clear that WAIT array can be of size more than 1 if 
		the semaphore set has more than 1 semaphore...below u can see I have passed SEMCOUNT as argument coz I want 1 semphore */

    //step 1: create semaphore
	semid = semget(IPC_PRIVATE,SEMCOUNT,IPC_CREAT|IPC_EXCL); //semcount = 1...#defined above

	//step 2: initialize semaphore
	semctl(semid,0,SETVAL,1); 
	
	//2nd param = 0 is the semaphore number 0...we have 1 semaphore...so in an array its number is 0
    //3 rd param has 2 values SETVAL OR SETALL...i.e to setval for this sem...or setall for all semaphores in array
	/*4th param is actually not an integer..it should be a union 
	   union semun {
           int val; ---- used for SETVAL only 
	       struct semid_ds *buf; ----for IPC_STAT and IPC_SET, not discussed here 
           ushort *array; ---- used for GETALL and SETALL 
	 }; 

	 since we use setavl...I am directly putting the integer value "val"...& since the initial value must be 1...which is gonna be changed to -1 on wait.
	 I have initialized 4th param to 1
	*/


	//step 3: define semaphore operations
	WAIT[0].sem_num = 0;  //single semaphore...array size = semcount = 1..so index 0..
	WAIT[0].sem_op = -1; //we use -1 to lock semaphore and +1 to unlock semaphore
	WAIT[0].sem_flg = SEM_UNDO ; 

	SIGNAL[0].sem_num = 0;
	SIGNAL[0].sem_op = 1;
	SIGNAL[0].sem_flg = SEM_UNDO ;
	
	/*SEM_UNDO :  if the process terminates without releasing the semaphore, allows the OS to automatically 
				  release the semaphore if it was held by this process.

	 IPC_NOWAIT: If IPC_NOWAIT is NOT specified, then the calling process sleeps until the 
	 requested amount of resources are available in the semaphore */
	
	if(semid < 0){
		printf("Error creating semaphore");
		return 1;
	}

	pid = fork();

	if(pid == -1){
		printf("error while creating child process");
		return 2; //that's just random
	}

	if(pid == 0){

		while(cnt!=0){

			//step 4: using semaphore operations

			printf("\nChild calling Wait()--cnt=%d",cnt);
			semop(semid,WAIT,SEMCOUNT);

			printf("\nChild Inside CS--cnt=%d",cnt);
			fp = fopen(filename,"a"); //open for writing...append to the end of the file
			fputs("Inside child process\n",fp);
			fclose(fp);

			cnt--;

			sleep(3); //this sleep() is just to show that even if it waits for 3 secs the other wont be able to enter CS
			
			printf("\nChild calling Signal()--cnt=%d",cnt);
			semop(semid,SIGNAL,SEMCOUNT);
			
			printf("\nChild Released CS Semaphore--cnt=%d",cnt);
			
		}

		//step 5: release semaphores
		semctl(semid,0,IPC_RMID);

	}

	if(pid > 0){

		while(cnt!=0){

			printf("\nParent calling Wait()--cnt=%d",cnt);
			semop(semid,WAIT,SEMCOUNT);
			
			printf("\nParent Inside CS--cnt=%d",cnt);
			fp = fopen(filename,"a");
			fputs("Inside parent process\n",fp);
			fclose(fp);
			cnt--;

			sleep(1);
		//this sleep() is lesser than last sleep() coz its to show that even if they take different times inside CS..concurrency is maintained

			printf("\nParent calling Signal()--cnt=%d",cnt);
			semop(semid,SIGNAL,SEMCOUNT);
			
			printf("\nParent Released CS Semaphore--cnt=%d",cnt);
		}

		//step 5: release semaphores
		semop(semid,0,IPC_RMID);
		wait(&termstat);
		printf("\n\nChild process is terminated...Parent terminates now\n\n");

	}

	return 0;
}
