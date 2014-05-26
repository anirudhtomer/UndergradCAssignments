#include<stdio.h>
#include<conio.h>
#include<dos.h>
long facto(long );
void main()
{
	long i,j,k;
	clrscr();
	printf("Hi Divya Behna I have made this program specially for you");
	delay(5000);
	clrscr();
	printf("\nEnter any number you like:-\t");
	scanf("%ld",&i);
	j=facto(i);
	printf("\nThe SUM OF THE DIGITS is");
	for(k=0;k<4;k++)
	{
		printf(".");
		delay(200);
	}
	printf("%ld",j);
	getch();
}
long facto(long x)
{
	long f,a,b,c;

	if(x==0)
		return 0;

	f=x%10+facto(x/10);
	return f;
}