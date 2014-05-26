/*SUM OF THE DIGITS OF A NUMBER*/

#include<stdio.h>
#include<conio.h>
#include<string.h>
int main()
	{
	int a,b,c,d,e,f,num,sum,g;

	clrscr();
	printf("Enter a four digit number:-\t");
	scanf("%4d",&num);

	a=num/1000;
	b=num%1000;
	c=b/100;
	d=b%100;
	e=d/10;
	f=d%10;
	sum=a+c+e+f;

	printf("\nsum of the digits=\t%d+%d+%d+%d\a=\t%d",a*1000,c*100,e*10,f,sum);

	getch();
	return 0;
}