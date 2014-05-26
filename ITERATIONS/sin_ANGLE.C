//program to calculate "sine"  of any angle using functions

#include<stdio.h>
#include<conio.h>
int i;
float fact(float );
float powr(float ,float );
void main()
{

	float c,fac,pow,deg,rad,sum1=0.0,sum2=0.0;

	clrscr();

	printf("Enter the angle:-\t");
	scanf("%f",&deg);

	rad=deg*3.14/180;

	for(i=1;i<4;i++)
	{
		c=(4*i-3);
		fac=fact(c);
		pow=powr(rad,c);
		sum1=(float)(sum1+pow/fac);
	}
	for(i=2;i<4;i++)
	{
		c=(4*i-5);
		fac=fact(c);
		pow=powr(rad,c);
		sum2=(float)(sum2+pow/fac);
	}

	printf("\n\nsin %f=\t%f",deg,sum1-sum2);

	getch();

}
float fact(float f)
{
     float f_tr=1.0;
     for(i=1;i<=f;i++)
     {
	 f_tr=f_tr*i;
     }
     return f_tr;
}
float powr(float bas,float rad)
{
	float p_wr=1;
	for(i=1;i<=rad;i++)
	{
		p_wr=p_wr*bas;
	}
	return p_wr;
}