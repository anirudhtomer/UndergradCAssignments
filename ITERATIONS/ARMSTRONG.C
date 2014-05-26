//program for armstrong number

#include<stdio.h>
#include<conio.h>
#include<math.h>

int main()
{
	int a,b,c,d,e,cb,cd,ce,n,o;
	clrscr();

	printf("enter range upto  which series of armstrong numbers is to be produced :-\t");
	scanf("%3d",&a);

	for(n=100;n<=a;n++)
	{
		b=n/100;
		c=n%100;
		d=c/10;
		e=c%10;	

		cb=pow(b,3);
		cd=pow(d,3);
		ce=pow(e,3);

		if ((cb+cd+ce)==n)
			printf("\t%d",n);
	}
	getch();
	return 0;
}

