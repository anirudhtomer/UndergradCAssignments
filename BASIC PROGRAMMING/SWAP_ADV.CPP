//PROGRAM FOR SWAPPING IN ADVANCED WAY

#include<iostream.h>
#include<conio.h>

int main()
{
	int x=6,y=9;

	clrscr();

	cout<<"\n\nUNSWAPPED \n\nX = "<<x;
	cout<<"\n\nY = "<<y;


	y^=x;     // ^ is ex-or operator

	x^=y;

	y^=x;

	cout<<"\n\nSWAPPED \n\nX = "<<x;
	cout<<"\n\nY = "<<y;

	getch();

	return 0;

}

