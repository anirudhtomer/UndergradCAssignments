//program for prime number

#include<stdio.h>
#include<conio.h>
void main()
{
	int a,b,c;
	clrscr();
	printf("ENTER ANY NUMBER:-\t");
	flushall();
	scanf("%d",&a);
	for(b=2;b<a;b++)
	{
		if(a%b==0)
		{
		printf("\n\n\nIt is not a prime number");
		break;
		}

	}

	if(b==a)
	printf("\n\n\nit is a prime number");

	getch();
}