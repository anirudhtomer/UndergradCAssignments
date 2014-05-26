//GAME: ARRANGE IN ASCENDING ORDER

#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<process.h>

int a[4][4]={
			{1,4,15,7},
			{8,10,2,11},
			{14,3,6,13},
			{12,9,5,0}
	    };

int b[4][4]={
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12},
		{13,14,15,0}
	    };

int getkey();
void press(int [4][4]);
void out();
void check(int [4][4],int);
void cong(int);

void up(int [4][4]);
void down(int [4][4]);
void left(int [4][4]);
void right(int [4][4]);

void display(int [4][4]);
void main()
{
	press(a);
}
void out()
{
	printf("\n\n***************PRESS**************\n\n\"Enter\" to EXIT\n\n%c for UP\n\n%c for DOWN\n\n<- for LEFT\n\n-> for RIGHT",24,25);
}
void press(int a[4][4])
{

	int ret;
	static int cnt;
	clrscr();
	printf("**********ARRANGE THESE IN ASCENDING ORDER IN MINIMUM CHANCES********\n\nCHANCES:-\t%d\n\n",cnt);
	display(a);

	out();

	if(cnt>100)
		check(a,cnt);

	ret=getkey();
	cnt++;
	switch(ret)
	{
		case 72: up(a);
			 break;
		case 80: down(a);
			 break;
		case 75: left(a);
			 break;
		case 77: right(a);
			 break;
		case 28: exit(0);
	}
}
void check(int a[4][4],int cnt)
{
	int i,j,cnt1=0,f=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(a[i][j]==b[i][j])
			{
				cnt1++;
			}
			else
			{
				f=1;
				break;
			}
		}
		if(f)
			break;
	}
	if(cnt1==16)
		cong(cnt);
}
void cong(int cnt)
{
	delay(500);
	clrscr();
	printf("***********CONGRATS***********");
	printf("\n\nYOU WON THE GAME\n\nYou took %d chances",cnt);

}

void up(int a[4][4])
{
	int i,j,f=0;

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(!a[i][j])
			{
				a[i][j]=a[i+1][j];
				a[i+1][j]=0;

				f=1;
				break;
			}
		}
		if(f)
			break;
	}
	press(a);
}
void down(int a[4][4])
{
	int i,j,f=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(!a[i][j])
			{
				a[i][j]=a[i-1][j];
				a[i-1][j]=0;

				f=1;
				break;
			}
		}
		if (f)
			break;
	}
	press(a);
}
void left(int a[4][4])
{
	int i,j,f=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(!a[i][j])
			{
				a[i][j]=a[i][j+1];
				a[i][j+1]=0;

				f=1;
				break;
			}
		}
		if(f)
			break;
	}
	press(a);
}
void right(int a[4][4])
{
	int i,j,f=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(!a[i][j])
			{
				a[i][j]=a[i][j-1];
				a[i][j-1]=0;

				f=1;
				break;
			}
		}
		if(f)
			break;
	}
	press(a);
}

void display(int a[4][4])
{
	int i,j;
	for(i=0;i<4;i++)
	{
		printf("\n\n");
		for(j=0;j<4;j++)
		{
			if(a[i][j]!=0)
				printf("%d\t",a[i][j]);
			else
				printf("%c\t",32);
		}

	}
	printf("\n\n\n");
}

int getkey()
{
	union REGS i,o;
	while(!kbhit())

	i.h.ah=0;
	int86 (22,&i,&o);
	return(o.h.ah);
}