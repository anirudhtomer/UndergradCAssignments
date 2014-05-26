//progarm for palindrome number

#include<stdio.h>
#include<conio.h>
int main()
{
	int a,b,c,d,e;
	clrscr();

	printf("enter a three digit number:-\t");
	scanf("%3d",&a);

	b=a/100;
	c=a%100;
	d=c/10;
	e=c%10;

	if(b==e)
	printf("\nThe given number is palandrome number");
	else
	printf("it's not a palandrome number");

	getch();
	return 0;
}