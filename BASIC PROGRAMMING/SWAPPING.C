//swapping of two numbers

#include<stdio.h>
#include<conio.h>
#define alpha() scanf("%d%d",&a,&b);
int main()
{
	int a,b,c;
	clrscr();

	printf("enter two numbers 'a' & 'b':-\t");
	alpha();

	c=a;
	a=b;
	b=c;

	printf("\nswapped 'a'=%d\tand  swapped 'b'=%d",a,b);
	getch();
	return 0;
}