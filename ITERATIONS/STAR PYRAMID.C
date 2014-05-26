//program to print stars in form of a pyramid

#include<stdio.h>
#include<conio.h>
void main()
{
	int a,b,st,sp,e;
	clrscr();
	printf("Enter The maximum Number Of Stars You Want upto 40 only:-\t");
	scanf("%d",&a);
	printf("\n");
	for(b=1;b<=a;b++)
	{
		for(st=1;st<=b;st++)
		{
			for(sp=a-b;sp>=1;sp--)
			{
				if(st>1)
				break;
				else
				{
					printf(" ");
				}
			}
			printf("%c ",42);
		}
		printf("\n");
	}

	getch();
}