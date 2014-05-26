#include<stdio.h>
#include<stdlib.h>
//#include<pthread.h>

/* 
I commented "pthread.h" coz even after including that I had to give the path of the library lpthread
	gcc addition.c -lpthread
so there was no point in including this....waise bhi this is not a part of standard C library

*/
	


void* add1(void *arg){
	
	int *arr = (int*) arg;

	printf("\n\nInside Thread 1");
	arr[2] = arr[0] + arr[1];

}

void* add2(void *arg){

	int *arr = (int*) arg;
	
	printf("\n\nInside Thread 2");

	arr[2] = arr[0] + arr[1];

}


int main(){

// pthread_t is a long int 

	pthread_t t1,t2;
	int *a1,*a2;

	/* 
	  the function which which is executed for a given thread should
	  1. return void *
	  2. parameters as void*

	  since the type of parameters or type of return can be anything...they have used void* so that POSIX threads do not get confined 
	  to one particular data type

	*/

	a1 = (int *) malloc(sizeof(int)*3);
	a2 = (int *) malloc(sizeof(int)*3);

	a1[0] = 1;
	a1[1] = 2;
	
	a2[0] = 3;
	a2[1] = 4;

	//a1[2] and a2[2] contain the addition result

	if( pthread_create(&t1,NULL,add1,(void*) a1) != 0){
		printf("Error while creating first thread");
	}

	printf("\nFirst thread created");

	if( pthread_create(&t2,NULL,add2,(void*) a2) != 0){
		printf("Error while creating second thread");
	}

	printf("\nSecond thread created");

	/* if we do not join the threads then main thread will execute & probably wont give time to other threads	
	   the worst part is ..since its the main thread..once it gets over the whole process is over & other threads are terminated too.	
	*/

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	printf("\n\nResult of the summation:-\t%d\n\n",a1[2] + a2[2]);

	return 0;
}
