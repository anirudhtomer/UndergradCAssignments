//PROGRAM TO SHOW THE INITIALISATION OF A MOUSE

#include<iostream.h>
#include<graphics.h>
#include<dos.h>
#include<conio.h>

union REGS i,o;

int main()
{
	int gd = DETECT,gm;
	clrscr();

	initgraph(&gd,&gm,"c:\\tc\\bgi");

	i.x.ax=0;   //put AX=0 & CALL int 33h ...it initializes mouse
	int86(0x33,&i,&o);

	i.x.ax=1; //AX=1....show the position of the mouse
	int86(0x33,&i,&o);

	getch();

	//show mouse position just before mouse is hidden
	i.x.ax=3;
	int86(0x33,&i,&o);
	cout<<o.x.cx<<" "<<o.x.dx;

	i.x.ax=2; //to remove the mouse pointer
	int86(0x33,&i,&o);



	getch();

	return 0;
}