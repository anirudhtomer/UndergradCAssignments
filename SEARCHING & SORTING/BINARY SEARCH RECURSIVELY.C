#include<stdio.h>
#include<conio.h>
#define MAX 10

void sort(int *);
int binsrch(int *,int,int,int);

void main()
{
	int i,arr[MAX],tar,loc,low=0,high=9;

	clrscr();
	printf("Enter elements (10):\t");

	for(i=0;i<MAX;i++)
		scanf("%d",(arr+i));

	printf("\n\nEnter element to be searched:-\t");
	scanf("%d",&tar);

	sort(arr);

	printf("\n\nThe sorted list is:-\n\n");
	for(i=0;i<MAX;i++)
		printf("%d\t",*(arr+i));

	loc=binsrch(arr,tar,low,high);

	if(loc==-1)
		printf("\n\nUNSUCCESSFUL...");
	else
		printf("\n\nSUCCESS FOR  %d   at location  %d",tar,loc+1);
	getch();
}

int binsrch(int *a,int t,int low,int high)
{
	int mid;

	if(low<=high)
	{
		mid=(low+high)/2;

		if(t==a[low])
			return low;
		if(t==a[high])
			return high;
		if(t==a[mid])
			return mid;

		if(t<a[mid])
			binsrch(a,t,low,mid-1);

		binsrch(a,t,mid+1,high);
	}
	else
		return -1;

}

void sort(int *a)
{
	int i,j,temp;

	for(i=0;i<9;i++)
	{
		for(j=i+1;j>0;j--)
		{
			if( (*(a+j)) < (*(a+j-1)) )
			{
				temp=*(a+j);
				*(a+j)=*(a+j-1);
				*(a+j-1)=temp;
			}
			else
				break;
		}
	}
}