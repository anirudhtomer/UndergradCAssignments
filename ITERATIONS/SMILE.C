//program to print smiling faces

#include<stdio.h>
#include<conio.h>
void main()
{
	long a,b;
	clrscr();
	printf("LET ME MAKE YOU SMILE\n\nENTER HOW MANY TIMES YOU WANNA SMILE:-\t");
	flushall();
	scanf("%ld",&a);
	printf("\n\n");
	for(b=1;b<=a;b++)
	{
		printf(" %c",2);
	}
	printf("\n\n\nCOUNT THEM THEY ARE EXACTLY %ld",a);
	getch();

}

