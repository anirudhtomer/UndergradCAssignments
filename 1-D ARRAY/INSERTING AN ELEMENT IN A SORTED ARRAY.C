//program to insert an element in an array at a given position

#include<stdio.h>
#include<conio.h>

int arr[20],*j,i,k,min;

void sel_sort(int *,int );
void display(int *,int );

void main()
{
	int n,num,p,temp;
	clrscr();

	printf("Enter The Size of the array:-\t");
	scanf("%d",&n);

	printf("\nEnter The Elements of the array:-\n\n");

	j=arr;

	for(i=0;i<n;i++)
	{
		scanf("%d",j);
		j++;
	}


	sel_sort(arr,n);
	display(arr,n);

	printf("\n\nEnter the element to be inserted & at what positon:-\t");
	scanf("%d%d",&num,&p);

	for(i=n;i>p-1;i--)
	{
		arr[i]=arr[i-1];
	}
	arr[p-1]=num;

	display(arr,n+1);

	getch();

}
void sel_sort(int *a,int n)
{
	int temp;
	min=a[0];
	for(i=0;i<n-1;i++)
	{
		for(k=i+1;k<n;k++)
		{
			if(min>a[k])
			{
				temp=min;
				min=a[k];
				a[k]=temp;
			}
		}
		a[i]=min;
		min=a[i+1];
	}


}

void display(int *a,int n)
{
	static int cnt=1;
	if(cnt==1)
		printf("\n Sorted array is\n\n");
	if(cnt==2)
		printf("\n Array with inserted element is\n\n");
	for(i=0;i<n;i++)
	{
		printf("%d  ",a[i]);
	}
	cnt++;
}

