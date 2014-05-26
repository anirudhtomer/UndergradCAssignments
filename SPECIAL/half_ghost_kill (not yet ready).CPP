//PROGRAM TO SHOW THE INITIALISATION OF A MOUSE

#include<iostream.h>
#include<graphics.h>
#include<dos.h>
#include<conio.h>

union REGS i,o;
struct SREGS s;

int cursor[32] =
				{
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


class mouse
{
	public:
	mouse()
	{
	}


	void initmouse();
};

class ghost:public mouse
{
	const int r,lb,la,wa,ll,wl;

	/*
		r  -> radius of the head      (7)

		lb -> length of the body      (40)

		la -> lateral length of the arms (13)

		wa -> width of the arms      (5)

		ll -> lateral length of the legs (18)

		wl -> width of the legs     (8)
	*/

	public:
	ghost():r(5),lb(25),la(10),wa(3),ll(13),wl(7)
	{

	}

	//FOLLOWING ARE THE FUNCTIONS TO DRAW & REMOVE GHOST
	void drawghost(int,int);
	void removeghost(int,int);

	void linearmov_left_right();  //to move ghost from left to right
	void linearmov_right_left();  //to move ghost form right to left

};


int main()
{
	int gd = DETECT,gm;
	ghost g1;

	initgraph(&gd,&gm,"c:\\tc\\bgi");
	g1.initmouse();

	g1.linearmov_left_right();


	getch();

	closegraph();
	return 0;

}

void ghost::drawghost(int x,int y)
{
	int i;

	setcolor(DARKGRAY);
	setfillstyle(SOLID_FILL,DARKGRAY);

	//head

	circle(x,y,r);
	fillellipse(x,y,r,r);  // to fill the head of ghost

	//body frame
	for(i=x-r/2;i<=x+r/2;i++)  // "i" is the vertical line being chosen (x coordinate)
	{
		line(i,y+r,i,y+r+lb);
	}

	//right arm       ....16 pixels down from the head
	for(i=0;i<wa;i++)     // "i" is the lateral line being chosen (y coordinate)
	{
		line(x+r/2,y+i+16,x+r/2+la,y+i+24);
	}

	//left arm      .... 16 pixels down from the head
	for(i=0;i<wa;i++)     // "i" is the lateral line being chosen (y coordinate)
	{
		line(x-r/2,y+i+16,x-r/2-la,y+i+24);
	}

	//right leg     ....4 pixels above the bottom of the body
	for(i=0;i<wl;i++)
	{
		line(x,y+r+lb+i-8,x+ll,y+r+lb+i+10);
	}

	//left leg     ....4 pixels above the bottom of the body
	for(i=0;i<wl;i++)
	{
		line(x,y+r+lb+i-8,x-ll,y+r+lb+i+10);
	}

	//eyes
	putpixel(x-r/2,y-r/2,LIGHTGRAY);
	putpixel(x+r/2,y-r/2,LIGHTGRAY);
	putpixel(x-r/2-1,y-r/2,LIGHTGRAY);
	putpixel(x+r/2+1,y-r/2,LIGHTGRAY);
	putpixel(x-r/2,y-r/2+1,LIGHTGRAY);
	putpixel(x+r/2,y-r/2+1,LIGHTGRAY);

	//to draw the nose
	setcolor(LIGHTGRAY);
	line(x,y-2,x,y+2);

}
/*
//remove the ghost image
void ghost::removeghost(int x,int y)
{
	int i;

	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);

	//head

	circle(x,y,r);
	fillellipse(x,y,r,r);

	//body frame
	for(i=x-r/2;i<=x+r/2;i++)
	{
		line(i,y+r,i,y+r+lb);
	}

	//right arm
	for(i=0;i<wa;i++)
	{
		line(x+r/2,y+i+16,x+r/2+la,y+i+24);
	}

	//left arm
	for(i=0;i<wa;i++)
	{
		line(x-r/2,y+i+16,x-r/2-la,y+i+24);
	}

	//right leg
	for(i=0;i<wl;i++)
	{
		line(x,y+r+lb+i-8,x+ll,y+r+lb+i+10);
	}

	//left leg
	for(i=0;i<wl;i++)
	{
		line(x,y+r+lb+i-8,x-ll,y+r+lb+i+10);
	}


}*/

//remove the ghost image
void ghost::removeghost(int x,int y)
{
	int i,j,msx,msy;

	setcolor(BLACK);

	/*don't think of filling the area with lines...use pixels to have
	control on the activation & the deactivation...i don't wanna put mouse
	cursor pixels black*/

	for(i=x-20;i<x+20;i++)
	{
		for(j=390;j<=470;j++)
		{
			if(WHITE!=getpixel(i,j))
				putpixel(i,j,BLACK);
		}
	}

}


//to move ghost from left to right
void ghost::linearmov_left_right()
{
	int start_x,start_y,i;

	start_x = 40;
	start_y = 400;

	for(i=start_x;i<639;i++)
	{
		drawghost(i,start_y);
		removeghost(i,start_y);
	}

}

//to move ghost from right to left
void ghost::linearmov_right_left()
{
	int start_x,start_y,i;

	start_x = 40;
	start_y = 400;

	for(i=start_x;i<63;i++)
	{
		drawghost(i,start_y);
		delay(14);
		removeghost(i,start_y);
	}


}

//INITIALIZING (U.S. ....INITIALISING)
void mouse::initmouse()
{

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
	//int86(0x33,&i,&o);  //takes values from ds


}