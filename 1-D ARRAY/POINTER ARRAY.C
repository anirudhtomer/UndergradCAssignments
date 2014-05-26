//passing 1-D array to a function using pointers & returning from it

#include<stdio.h>
#include<conio.h>
int * enter(int *,int *);
void main()
{
	int a[20],n,i,*p;
	clrscr();
	printf("Enter size of array:-\t");
	scanf("%d",&n);
	printf("\n");

	p=enter(&a[0],&n);

	printf("\n\n\nELEMENTS ARE:-\t");
	for(i=0;i<n;i++)
	{
		printf("%d ",*(p+i));
	}

	getch();
}
int * enter(int *arr,int *siz)
{
	int i;
	for(i=0;i<*siz;i++)
	{
		printf("\nEnter element %d:\t",i+1);
		scanf("%d",(arr+i));
	}
	return arr;
}