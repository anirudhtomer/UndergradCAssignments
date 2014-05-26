//program to show how to use ternary operator

#include<stdio.h>
#include<conio.h>
void main()
{
	int a,b,c;

	clrscr();

	printf("Enter Three Numbers:-\t");
	scanf("%d%d%d",&a,&b,&c);
	//for finding greatest of three using && operator
	( a>b&&a>c?printf("\n\nFirst Number is Greatest"):( b>c?printf("\n\nSecond Number is greatest"):printf("\n\nThird Number is greatest")));

	//for finding smallest of three using || operator
	( a>b||a>c?(b>c?printf("\n\nThird number is smallest"):printf("\n\nSecond Number is smallest")):printf("\n\nFirst Number is smallest"));

	getch();
}
