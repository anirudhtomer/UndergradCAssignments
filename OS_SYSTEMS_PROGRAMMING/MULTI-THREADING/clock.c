#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
//#include<pthread.h>

/* 
I commented "pthread.h" coz even after including that I had to give the path of the library lpthread
	gcc addition.c -lpthread
so there was no point in including this....

ideally this clock program should have been made using "semaphores for thread synchronization"...but 
there is not much time left to first understand it & them implement it (semaphore)

*/

#define TRUE 1
#define FALSE 0

struct Time{
	int hour;
	int min;
	int sec;

	int hourflag;
	int minflag;
	//second's thread always keeps running so I don't need a flag to control its working 
};

void getCurrentTime(struct Time *time1){

	struct tm *curtime;
	time_t t1;

	time(&t1); //takes the time in seconds from EPOCH...1st jan 1970...type "man 2 time"

	/*curtime is a structure which has values for min,hour,year etc...it takes the number of seconds since EPOCH & fills the structture elements
	type "man ctime" to check it out
	*/

	curtime = localtime(&t1);
	
	time1->hour = curtime->tm_hour;
	time1->min = curtime->tm_min;
	time1->sec = curtime->tm_sec;

	time1->hourflag = FALSE;
	time1->minflag = FALSE;
}

void displayTime(struct Time *time){
	system("clear");
	printf("%d : %d : %d\n\nPress Ctrl + C to exit\n\n",time->hour,time->min,time->sec);
}

void * handleHour(struct Time * time){
	while(1){
		while(time->hourflag == FALSE);

		time->hourflag = FALSE;

		time->hour = (time->hour + 1) % 60;

	}
}

void * handleMin(struct Time * time){
	
	while(1){
		while(time->minflag == FALSE);
			
		time->minflag = FALSE;
		
		time->min = (time->min + 1) % 60;

		if(time->min == 0)
			time->hourflag = TRUE;
	}
}

void * handleSec(struct Time * time){
	while(1){
		
		if(time->sec==59){
			time->minflag = TRUE;	
		}	

		sleep(1);
		time->sec = (time->sec + 1) % 60;
		displayTime(time);
	}
}


int main(){
	
	struct Time *curtime = (struct Time*) malloc(sizeof(struct Time));
	
	pthread_t thread_hour,thread_min,thread_sec;

	//get current time from system clock
	getCurrentTime(curtime);

	displayTime(curtime);

	pthread_create(&thread_sec,NULL,handleSec,(void *) curtime);
	pthread_create(&thread_min,NULL,handleMin,(void *) curtime);
	pthread_create(&thread_hour,NULL,handleHour,(void *) curtime);

	pthread_join(thread_hour,NULL);
	pthread_join(thread_min,NULL);
	pthread_join(thread_sec,NULL);

	return 0;
}

