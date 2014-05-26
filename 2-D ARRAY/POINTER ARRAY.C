//passing 2-D array to a function using pointers & returning from it

#include<stdio.h>
#include<conio.h>

void enter(int (*arr)[10],int *,int *);
void main()
{
	int a[10][10],r,c,i,*p;
	clrscr();
	printf("Enter size of array  (rows * columns) :-\t");
	scanf("%d%d",&r,&c);
	printf("\n");

	enter(a,&r,&c);
	getch();
}
void enter(int (*arr)[10],int *row,int * col)
{
	int i,j;
	int *ptr;

	for(i=0;i<*row;i++)
	{
		ptr = arr + i;

		printf("\n\nEnter elements of row %d:\n",i+1);
		for(j=0;j<*col;j++)
		{
			printf("\nEnter element %d:\t",j+1);
			scanf("%d",*(ptr+j));
		}
	}

	printf("\n\n\nELEMENTS ARE:-\t");

	flushall();
	for(i=0;i<*row;i++)
	{
		printf("\n");
		for(j=0;j<*col;j++)
		{
			printf("%d\t",*(*(arr+i)+j));
		}
	}

	//return arr;
}