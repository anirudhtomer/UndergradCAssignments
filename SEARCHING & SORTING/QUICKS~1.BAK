//PROGRAM FOR QUICK SORT

#include<stdio.h>
#include<malloc.h>

struct stack
{
	int start;
	int end;	
	struct stack *down;
}*top;

/* stack empty op */
int empty()
{
	if (top==NULL)
		return 1;
	else 
		return 0;	
}

/* stack push op */
void push(int start,int end)
{
	struct stack *temp;
	
	temp = (struct stack*) malloc(sizeof(struct stack*));
	temp->start = start;
	temp->end = end;
	
	temp->down = top;
	top = temp;
}

/* stack pop op */
struct stack* pop()
{
	struct stack *ret;

	ret = top;
	top = top->down;

	return ret;
}

/* takes array,start index,end index +1 (total number of elements) */
void quicksort_rec(int *,int,int);
void quicksort_nonrec(int *,int);

/* returns mid...takes pivot,array,start,end */
int partition(int,int*,int,int);

int main()
{
	int arr[20];
	int i,N;
	
	printf("Enter the number of the elements :-\t");
	scanf("%d",&N);

	for(i=0;i<N;i++)
	{
		printf("\nEnter the element %d:-\t",i+1);
		scanf("%d",arr+i);
	}
	
	quicksort_nonrec(arr,N);

	printf("\n\nTHE SORTED ARRAY IS:-\n");
	for(i=0;i<N;i++)
	{
		printf("%d\t",arr[i]);
	}
	return 0;
}

/* QUICK SORT NON RECURSIVE */
void quicksort_nonrec(int *arr,int N)
{
	int mid;
	struct stack *s1=NULL;
	
	top=NULL;
	push(0,N);	

	while(!empty())
	{
		s1 = pop();
			
		if(s1->start == s1->end)
			continue;

		mid = partition(s1->start,arr,s1->start,s1->end);
		printf("mid = %d\t",mid);
			
		push(s1->start,mid);
		push(mid+1,s1->end);
	}
}

/* QUICK SORT RECURSIVE*/
void quicksort_rec(int *arr,int start,int end)
{
	int mid,pivot;

	if(start==end)
		return;
	
	pivot = start;
	mid = partition(pivot,arr,start,end);

	/* quick sort each of the two halves of the array */
	quicksort_rec(arr,start,mid);
	quicksort_rec(arr,mid+1,end);
}

/* PARTITION */
int partition(int pivot,int *arr,int start,int end)
{
	int down,up;
	int temp;

	down = start;
	up = end-1;

	while(down<=up)
	{
		while(arr[down]<=arr[pivot] && down<=up)
		{	
			down++;
		}

		while(arr[up]>arr[pivot] && down<=up)
		{
			up--;	
		}	

		if(down<=up)
		{
			temp = arr[down];
			arr[down] = arr[up];
			arr[up] = temp;
		}
	}

	temp = arr[up];
	arr[up] = arr[pivot];
	arr[pivot] = temp;

	return up;
}
