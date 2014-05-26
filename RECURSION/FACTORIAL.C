#include<stdio.h>
#include<conio.h>
long facto(long );
void main()
{
	long i,j;
	clrscr();
	printf("\nEnter any number you like:-\t");
	scanf("%ld",&i);
	j=facto(i);
	printf("\nthe answer of the problem is %ld",j);
	getch();
}
long facto(long x)
{
	long f=x,a,b,c;

	if(x==0)
		return 1;

	f=f*facto(x-1);
	return f;
}