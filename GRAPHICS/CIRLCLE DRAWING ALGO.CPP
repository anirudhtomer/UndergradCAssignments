//ANIRUDH TOMER.....SE 42028.....SE COMP-I

//CIRCLE DRAWING ALGORITHM

#include<iostream.h>
#include<conio.h>
#include<math.h>
#include<dos.h>
#include<graphics.h>

void ddacircle(int,int,int);
void midcircle(int,int,int);
void brescircle(int,int,int);

void main()
{
	int rad,x,y,gd=DETECT,gm,chmnu;

	initgraph(&gd,&gm,"c:\\tc\\bgi");

	do
	{
		clrscr();
		cleardevice();

		cout<<"\t\t*************MENU*************\n\n";
		cout<<"1. DDA CIRCLE\t2. BRESENHAM CIRCLE\t3. MIDPOINT CIRCLE\t4.EXIT";

		cout<<"\n\nEnter Your Choice:-\t";
		cin>>chmnu;


		for(x=-1;chmnu!=4 && (x<0 || y<0);)
		{
			cout<<"\n\nENTER CENTRE OF THE CIRCLE (starting pt for breshen-loop):-\t";
			cin>>x>>y;

			cout<<"\n\nENTER THE RADIUS OF THE CIRCLE(rad for midptcircle means rad of petals):-\t";
			cin>>rad;

		}
		clrscr();
		cleardevice();

		switch(chmnu)
		{
			case 1: ddacircle(x,y,rad);
				  break;

			case 2: brescircle(x+rad,y,rad);
				  break;

			case 3: midcircle(x,y,rad);
				  break;

			case 4: return;

			default: cout<<"\n\n\aENTER PROPER VALUE";
		}

		getch();

	}while(1);

}


//********DDA CIRCLE ALGORITHM********
void ddacircle(int cx,int cy,int rad)
{
	int i;
	float ang,xi,yi;


	for(ang=0;ang<=2*3.14;ang+=0.0001)
	{
		xi=cx+rad*cos(ang);
		yi=cy+rad*sin(ang);
		putpixel(xi,yi,CYAN);

	}

}

//********BRESENHAM CIRCLE ALGORITHM*******

void brescircle(int cx,int cy,int rad)
{
	float ef_xy;

	int i,j,x1,y1,l;

	cout<<"ENTER THE LENGTH OF THE LOOP (length=1 means a semicircle):-\t";
	cin>>l;

	cleardevice();

	cx=cx+rad;

	for(i=0;i<l;i++,cx+=2*rad)
	{
		x1=0,y1=rad;
		ef_xy=3.0-2.0*rad;

		while(x1<=y1)
		{
			if(ef_xy<0)
				ef_xy+=4.0*x1+6.0;

			else
			{
				ef_xy+=4.0*(x1-y1)+10.0;
				y1--;
			}
			x1++;
			//CHECK: TO DRAW UPPER OR LOWER LOOP

			if(i%2==0)
			{
				putpixel(cx-x1,cy-y1,CYAN);
				putpixel(cx+x1,cy-y1,CYAN);
				putpixel(cx+y1,cy-x1,CYAN);
				putpixel(cx-y1,cy-x1,CYAN);
			}
			else
			{
				putpixel(cx-x1,cy+y1,CYAN);
				putpixel(cx+x1,cy+y1,CYAN);
				putpixel(cx+y1,cy+x1,CYAN);
				putpixel(cx-y1,cy+x1,CYAN);

			}
		}
	}

}

//********MID POINT CIRLCE ALGORITHM*********
void midcircle(int px,int py,int rad)
{
	float ef_xy,cx=px,cy=py,ang=0.785;

	int i,j,x1,y1;


	putpixel(cx+rad*1.414,cy,CYAN);
	putpixel(cx-rad*1.414,cy,CYAN);
	putpixel(cx,cy+rad*1.414,CYAN);
	putpixel(cx,cy-rad*1.414,CYAN);


	for(i=0,ang=0.785;i<4;i++,ang+=1.57)
	{
		x1=0,y1=rad;
		ef_xy=1.25-2.0*rad;

		cx=px+rad*cos(ang);
		cy=py+rad*sin(ang);

		while(x1<=y1)
		{
			if(ef_xy<0)
				ef_xy+=2.0*x1+3.0;

			else
			{
				ef_xy+=2.0*(x1-y1)+3.0;
				y1--;
			}
			x1++;
			//CHECK: TO DRAW UPPER OR LOWER LOOP

			if(i==0)
			{
				putpixel(cx-x1,cy+y1,CYAN);
				putpixel(cx+x1,cy+y1,CYAN);
				putpixel(cx+y1,cy-x1,CYAN);
				putpixel(cx+y1,cy+x1,CYAN);
				continue;
			}
			if(i==1)
			{
				putpixel(cx-x1,cy+y1,CYAN);
				putpixel(cx+x1,cy+y1,CYAN);
				putpixel(cx-y1,cy-x1,CYAN);
				putpixel(cx-y1,cy+x1,CYAN);
				continue;
			}
			if(i==2)
			{
				putpixel(cx-x1,cy-y1,CYAN);
				putpixel(cx+x1,cy-y1,CYAN);
				putpixel(cx-y1,cy-x1,CYAN);
				putpixel(cx-y1,cy+x1,CYAN);
				continue;
			}
			if(i==3)
			{
				putpixel(cx-x1,cy-y1,CYAN);
				putpixel(cx+x1,cy-y1,CYAN);
				putpixel(cx+y1,cy-x1,CYAN);
				putpixel(cx+y1,cy+x1,CYAN);

			}

		}
	}
	ddacircle(px,py,5);

}







