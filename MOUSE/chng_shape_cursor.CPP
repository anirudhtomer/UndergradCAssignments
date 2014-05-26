//PROGRAM TO SHOW THE INITIALISATION OF A MOUSE

#include<iostream.h>
#include<graphics.h>
#include<dos.h>
#include<conio.h>

union REGS i,o;
struct SREGS s;

int cursor[32] = {
				  //screen mask bitmap
				  0xf00f,0xe007,0xc7e3,0x8ff1,
				  0x1ff8,0x3ffc,0x3ffc,0x3e7c,
				  0x3e7c,0x3ffc,0x3ffc,0x1ff8,
				  0x8ff1,0xc7e3,0xe007,0xf00f,

				  //mouse pointer bitmap
				  0x0ff0,0x1ff8,0x381c,0x700e,
				  0xe007,0xc003,0xc003,0xc183,
				  0xc183,0xc003,0xc003,0xe007,
				  0x700e,0x381c,0x1ff8,0x0ff0,

				  };

int main()
{
	int gd = DETECT,gm,x,y,btno;
	clrscr();

	initgraph(&gd,&gm,"c:\\tc\\bgi");


	setcolor(RED);

	setlinestyle(1,0,3);
	circle(300,300,40);


	i.x.ax=0;   //put AX=0 & CALL int 33h ...it initializes mouse
	int86(0x33,&i,&o);

	i.x.ax=1; //AX=1....show the position of the mouse
	int86(0x33,&i,&o);


	//TO CHANGE SHAPE OF CURSOR
	i.x.ax = 9;  //interrupt service number
	i.x.bx = 0;
	i.x.cx = 0;
	i.x.dx = (unsigned)cursor;

	segread(&s);   //reads the segment registers & put their value in "s"
	s.es = s.ds;  // or   mov es,ds
	int86x(0x33,&i,&o,&s); //this int86x takes values from es instead of ds
	getch();

	i.x.ax=2; //to remove the mouse pointer
	int86(0x33,&i,&o);

	closegraph();
	restorecrtmode();
	return 0;
}


/*int cursor[32] = {
				  //screen mask bitmap
				  0xf00f,0xe007,0xc7e3,0x8ff1,
				  0x1ff8,0x3ffc,0x3ffc,0x3e7c,
				  0x3e7c,0x3ffc,0x3ffc,0x1ff8,
				  0x8ff1,0xc7e3,0xe007,0xf00f,

				  //mouse pointer bitmap

				  0x0ff0,0x1ff8,0x381c,0x700e,
				  0xe007,0xc003,0xc003,0xc183,
				  0xc183,0xc003,0xc003,0xe007,
				  0x700e,0x381c,0x1ff8,0x0ff0,

				  };*/
