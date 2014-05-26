//program to find pythagorean triplets

#include<stdio.h>
#include<conio.h>
void main()
{
	int a,b,n,c,d,e,f,g=0,h;
	clrscr();
	printf("ENTER UPTO WHICH NUMBER PYTHAGORIAN TRIPLETS ARE TO BE FOUND :-\t");
	scanf("%d",&n);
	for(a=1;a<=n;a++)
	{
		b=a*a;
		for(c=1;c<=n;c++)
		{
			d=c*c;
			for(e=1;e<=n;e++)
			{
				f=e*e;
				if(b+d==f)
				{
				      g++;
				      printf("\n\n %d%c + %d%c  =  %d%c",a,253,c,253,e,253);
				}
			}
		}
	}
	printf("\n\nTOTAL NUMBER OF PYTHAGORIAN TRIPLETS ARE:-\t%d",g);
	getch();
}
