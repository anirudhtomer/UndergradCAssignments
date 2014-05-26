//program for binary search

#include<stdio.h>
#include<conio.h>

void sel_sort(int *,int);
void bin_srch(int *,int);

void main()
{
	int i,n,arr[10];
	clrscr();
	printf("Enter the number of the elements:-\t");
	scanf("%d",&n);

	printf("\n\nEnter the elements of the matrix:-\n");
	for(i=0;i<n;i++)
	{
		printf("\nElement %d:\t",i+1);
		scanf("%d",(arr+i));
	}
	bin_srch(arr,n);
	getch();

}
void sel_sort(int *a,int n)
{
	int i,j,k,max,temp;
	max=a[0];
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(max>a[j])
			{
				temp=max;
				max=a[j];
				a[j]=temp;
			}
		}
		a[i]=max;
		max=a[i+1];
	}
	printf("\nSORTED ARRAY IS:\n");

	for(i=0;i<n;i++)
	{
		printf("\n\n%d",*(a+i));
	}
}

void bin_srch(int *a,int n)
{
	int tar,low,high,mid,flag;

	sel_sort(a,n);
	printf("\n\nEnter the element to be searched:-\t");
	scanf("%d",&tar);
	low=0;
	high=n-1;

	do
	{
		mid=(low+high)/2;

		if(tar==a[mid])
		{
			printf("\ntarget %d found at position... \"%d\"",tar,mid+1);
			flag=1;
			break;
		}

		if(tar==a[low])
		{
			printf("\ntarget %d found at location %d",tar,low+1);
			flag=1;
			break;
		}

		if(tar==a[high])
		{
			printf("\ntarget %d found at location %d",tar,high+1);
			flag=1;
			break;
		}

		if(tar>a[mid])
			low=mid+1;
		
		if(tar<a[mid])
			high=mid-1;

	}while(low<=high);

	if(flag!=1)
		printf("\n\nTARGET %d IS NOT IN THIS LIST",tar);
}









