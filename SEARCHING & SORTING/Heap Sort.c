//program for heap operations

#include<stdio.h>
#include<malloc.h>

/* to create a heap */
void createHeap(int *arr,int N)
{
	

}

/* insertion of the nodes */
void insertNode(int *arr,int N,int ele)
{
	

}

int main()
{
	int *heaparr[30];
	int N,i;

	printf("\nEnter the number of elements to be inserted in a heap:-\t");
	scanf("%d",&N);

	for(i=0;i<N;i++)
	{
		printf("Enter element %d:-\t",i+1);
		scanf("%d",heaparr+i);
	}
	
	//createHeap(heaparr,N);
//	insertNode(arr,N,10);

	return 0;
}

