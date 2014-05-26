//progarm for all possible combinations of 1,2,3

#include<stdio.h>
#include<conio.h>
void main()
{
	int num,a,b,c,d,e,f,g;
	clrscr();
	printf("COMBINATIONS OF 1,2&3 ARE\n");
	for(num=100;num<=500;num++)
	{
		a=num/100;
		b=(num%100)/10;
		c=num%10;
		
		if((a+b+c==6)&&(a*b*c==6))
			printf("\n %d\n",num);
	}
	getch();
}


