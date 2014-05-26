/*factorial of a number*/

#include<stdio.h>
#include<conio.h>
int main()
{
	int a,b,c;
	clrscr();
	
	printf("enter any number:-\t");
	scanf("%d",&a);

	for (b=2,c=1;b<=a;b++)

	{
		c=c*b;
	}

	printf("\nfactorial of the number=\t%d",c);

	getch();
	return 0;

}