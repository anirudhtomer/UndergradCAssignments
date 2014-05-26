#include<stdio.h>
#include<conio.h>

void main()
{
	int i=23456,*j;
	char *ch;
	int l,m;


	clrscr();

	j=&i;
	ch =(char*) j;
	l = *ch;

	m = *(ch+1);
	m = m<<8;
	m = m & 0xff00;
	l = l & 0x00ff;
	m = m + l;

	printf("%d\n",m);

	printf("%d\t%d",*j,*ch);


	getch();

}