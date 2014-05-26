/*REVERSE OF THE DIGITS OF A NUMBER*/

#include<stdio.h>
#include<conio.h>
#include<string.h>
int main()
{
	int a,b,c,d,e,f,num,rev,g;

	clrscr();
	printf("Enter a four digit number:-\t");
	scanf("%4d",&num);
	
	a=num/1000;
	b=num%1000;
	c=b/100;
	d=b%100;
	e=d/10;
	f=d%10;
	rev=f*1000+e*100+c*10+a;

	printf("\nreverse of the digits=\t%d",rev);

	getch();
	return 0;
}