//program to find leap year

#include<stdio.h>
#include<conio.h>
void main()
{
	int a,b,c;
	clrscr();

	printf("enter the year:-\t");
	scanf("%4d",&a);


	printf("\nTHE FOLLOWING OUTPUT IS OBTAINED USING 'if_else & logical operators'");

	if((a%4==0)&&(a%100!=0||a%400==0)||(a==1800))
		printf("\n\nIt's a LEAP YEAR");
	else
		printf("\n\nIt's not a leap year");


	printf("\n\nTHE FOLLOWING OUTPUT IS OBTAINED USING 'conditional or ternary operators'");
		((a%4==0)&&(a%100!=0||a%400==0)||(a==1800))?printf("\n\nIt's a LEAP YEAR"):printf("\n\nIt's not a leap year");

	getch();
}