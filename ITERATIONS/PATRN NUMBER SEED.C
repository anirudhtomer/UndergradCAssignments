/*program for a pattern like      11
				 2112
				321123  & so on      */

#include<stdio.h>
#include<conio.h>
void main()
{
	int n,i,b,c,sp;
	clrscr();
	printf("Enter Upto which Number You want the pattern (max. upto 9):-\t");
	scanf("%d",&n);
	printf("\n\n");
	for(i=1;i<=n;i++)
	{
		for(b=i;b>=1;b--)
		{
			for(sp=n-i;sp>=0;sp--)
			{
				if(b<i)
				break;
				else
				printf(" ");
			}
			printf("%d",b);
		}
		for(c=1;c<=i;c++)
		{
			printf("%d",c);
		}
		printf("\n");
	}
	getch();
}