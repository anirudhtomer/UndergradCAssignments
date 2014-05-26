#include<dos.h>
#include<stdlib.h>
#include<math.h>
#include<iostream.h>
#include<conio.h>
#include<graphics.h>

class ddaalgo
{
	float x1,y1,x2,y2;

	public:

	ddaalgo(){};

	void bresen();
	void dda();
	void animate();

	void enter()
	{
		cout<<"\n\nENTER COORDINATES OF LINE SEGMENT:-\t";
		cin>>x1>>y1>>x2>>y2;
	}

	int sign(int x)
	{
		if(x<0)
			return -1;
		if(x>0)
			return 1;
		return 0;
	}

};



int main()
{
	int gd = DETECT,gm,chmnu;
	ddaalgo c;

	initgraph(&gd,&gm,"c:\\tc\\bgi");

	c.animate();

	while(1)
	{
		clrscr();
		cleardevice();

		cout<<"\n\n************ LINE ALGORITHM *****************";
		cout<<"\n\n1.DDA\n\n2.BRESENHEM\n\n3.EXIT";
		cout<<"\n\nENTER YOUR CHOICE:-\t";
		cin>>chmnu;

		if(chmnu>=1 && chmnu <3)
			c.enter();

		clrscr();
		cleardevice();

		switch(chmnu)
		{
			case 1: c.dda();
					break;

			case 2: c.bresen();
					break;

			case 3: return 0;

			default: cout<<"WRONG CHOICE !!!";
		}
		getch();
	}

}

void ddaalgo::animate()
{
	int i;

	randomize();

	setlinestyle(0,0,3);

	for(i=0;i<50;i++)
	{
		delay(10);
		setcolor(random(16));
		line(random(639),random(479),random(639),random(479));
	}


	cleardevice();

	setcolor(RED);

	settextstyle(DEFAULT_FONT,0,3);
	outtextxy(10,200,"LINE::DRAWING::ALGORITHM");
	getch();

}

void ddaalgo::dda()
{
	float dx,dy;

	float m,temp,ty,tx;

	int i,factor,final,initial;

	dx = x2-x1;
	dy = y2-y1;

	//compare values of dx,dy
	if(abs(dx)>=abs(dy)) //gentle slope
	{
		if(dx<0)
		{
			temp = x1;
			x1 = x2;
			x2 = temp;

			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		factor = 0;  //x axis

		initial = x1;
		final = x2;
	}

	else
	{
		if(dy<0)
		{
			temp = x1;
			x1 = x2;
			x2 = temp;

			temp = y1;
			y1 = y2;
			y2 = temp;
		}

		factor = 1;

		initial = y1;
		final = y2;
	}

	dy = y2-y1;
	dx = x2-x1;

	if(dx)
		m = dy/dx;

	//draw dda line

	for(i=initial;i<=final;i++)
	{
		if(!dx)
		{
			putpixel(x1,i,MAGENTA);
			continue;
		}

		if(!factor) //gentle slope
		{
			ty = y1 + (i-initial)*m;
			putpixel(i,ty,MAGENTA);
		}
		else
		{
			tx = x1 + (i -initial)/m;

			putpixel(tx,i,MAGENTA);
		}

	}

	getch();
	setlinestyle(0,0,1);
	setcolor(WHITE);
	line(x1,y1,x2,y2);


}

void ddaalgo::bresen()
{
	int abs_dx,abs_dy;
	int s1,s2,i,factor,e;
	int x,y;

	abs_dx = abs(x2-x1);
	abs_dy = abs(y2-y1);

	if(x2>x1)
		s1 = 1;
	else if(x2<x1)
		s1 = -1;
		else s1 = 0;


	if(y2>y1)
		s2 = 1;
	else if(y2<y1)
		s2 = -1;
		else
			s2 = 0;


	if(abs_dx<abs_dy)
	{
		abs_dy ^= abs_dx;
		abs_dx ^= abs_dy;
		abs_dy ^= abs_dx;

		factor = 1;
	}
	else
		factor = 0;

	e = 2*abs_dy-abs_dx;

	i=1;
	x =x1;
	y = y1;

	while(i<=abs_dx)
	{
		putpixel(x,y,YELLOW);

		while(e>=0)
		{
			if(factor)
				x += s1;
			else
				y += s2;

			e = e - 2*abs_dx;
		}

		if(factor)
			y += s2;
		else
			x += s1;

		e += 2*abs_dy;
		i++;
	}

	setcolor(WHITE);
	getch();
	line(x1,y1,x2,y2);

}



