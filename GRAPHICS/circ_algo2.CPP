#include<dos.h>
#include<stdlib.h>
#include<math.h>
#include<iostream.h>
#include<conio.h>
#include<graphics.h>

class vrit
{
	int xc,yc,r;

	public:

	vrit()
	{
		xc = 0;
		yc = 0;


	}

	void midpt();
	void bresen();
	void dda();
	void putter(int,int);
	void animate();

	void enter()
	{
		cout<<"\n\nENTER COORDINATES OF CENTRE:-\t";
		cin>>xc>>yc;

		cout<<"\n\nENTER THE RADIUS:-\t";
		cin>>r;
	}

};



int main()
{
	int gd = DETECT,gm,chmnu;
	vrit c;

	initgraph(&gd,&gm,"c:\\tc\\bgi");

	c.animate();

	while(1)
	{
		clrscr();
		cleardevice();

		cout<<"\n\n************ CIRCLE ALGORITHM *****************";
		cout<<"\n\n1.DDA\n\n2.MID POINT\n\n3.BRESENHEM\n\n4.EXIT";
		cout<<"\n\nENTER YOUR CHOICE:-\t";
		cin>>chmnu;

		if(chmnu>=1 && chmnu <=3)
			c.enter();

		clrscr();
		cleardevice();

		switch(chmnu)
		{
			case 1: c.dda();
					break;
			case 2: c.midpt();
					break;
			case 3: c.bresen();
					break;
			case 4: return 0;

			default: cout<<"WRONG CHOICE !!!";
		}
		getch();
	}

}

void vrit::animate()
{
	int i;

	randomize();

	setlinestyle(0,0,3);

	for(i=0;i<500;i++)
	{
		setcolor(random(16));
		circle(random(639),random(479),random(50));
	}

	delay(500);
	cleardevice();


	setcolor(RED);
	settextstyle(DEFAULT_FONT,0,3);
	outtextxy(10,200,"CIRLCE DRAWING ALGORITHM");
	getch();

}

void vrit::dda()
{
	int i,radian;
	float px,py;

	for(i=0;i<=360;i++)
	{
		px = xc + r*cos( (3.14/180) * i);
		py = yc + r*sin( (3.14/180) * i);
		putpixel(px,py,CYAN);
	}
}

void vrit::midpt()
{
	float factor = 1-r;

	int px = 0 ,py = r;

	while(px<=py)
	{
		putter(px,py);

		if(factor<0)
			factor += 2*px + 3;

		else
		{
			factor += 2*(px-py) +3;
			py--;
		}

		px++;
	}

}

void vrit::bresen()
{
	float factor = 3 - 2*r;

	int px = 0 ,py = r;

	while(px<=py)
	{
		putter(px,py);

		if(factor<0)
			factor += 4*px + 6;
		else
		{
			factor += 4*(px-py) +10;
			py--;
		}
		px++;
	}

}

void vrit::putter(int x,int y)
{
	putpixel(xc+x,yc-y,CYAN);
	putpixel(xc-x,yc-y,CYAN);
	putpixel(xc+x,yc+y,CYAN);
	putpixel(xc-x,yc+y,CYAN);

	putpixel(xc+y,yc-x,CYAN);
	putpixel(xc+y,yc+x,CYAN);
	putpixel(xc-y,yc-x,CYAN);
	putpixel(xc-y,yc+x,CYAN);
}


