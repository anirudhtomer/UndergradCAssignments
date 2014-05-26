//The New faster Prime number series program

#include<stdio.h>
#include<conio.h>
void main()
{
	long a,b,c,co=0;
	long arr[15000];
	clrscr();
	printf("Enter The Number Upto Which You Want The Series of Prime No's:-\t");
	scanf("%ld",&a);
	for(b=2;b<=a;b++)
	{
	   for(c=0;c<co;c++)
	   {
		if(b>40000 && (b-arr[c])<=10000)
			  continue;

		if((b%arr[c])==0)
			goto incre;
	   }
	   if(c==co)
	   {
		printf("\t%ld",b);
		arr[co]=b;
		co++;
	   }
	   incre:
	 }
	 printf("\n\n\n Number Of prime numbers between 0 & %ld are:- %ld",a,co);
	getch();
}


