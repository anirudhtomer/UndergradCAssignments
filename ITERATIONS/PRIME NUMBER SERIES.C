// conventional program to print series of prime numbers upto n

#include<stdio.h>
#include<conio.h>
void main()
{
	long a,b,c,co=0;
	clrscr();
	printf("Enter The Number Upto Which You Want The Series of Prime No's:-\t");
	scanf("%ld",&a);

	for(b=2;b<=a;b++)
	{
	   for(c=2;c<b;c++)
	   {
		if(b%c==0)
		break;
	   }
	   if(c==b)
	   {
		printf("\t%ld",c);
		co+=1;
	   }
	 }
	 printf("\n\n\n Number Of prime numbers between 0 & %ld are:- %ld",a,co);
	getch();
}


