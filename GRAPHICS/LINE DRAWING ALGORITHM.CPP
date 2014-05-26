//ANIRUDH TOMER....SE COMP-I.....ROLL NO:42028
//program to a line using dda & bresenham's algorithm

#include<math.h>
#include<iostream.h>
#include<conio.h>
#include<graphics.h>

void ddaline(float,float,float,float,int);
void breshline(int,int,int,int,int);

void main()
{

	float xa,xb,ya,yb;
	int gd=DETECT,gm,chmnu,modch;

	initgraph(&gd,&gm,"c:\\tc\\bgi");

	do
	{
		clrscr();
		cleardevice();
		cout<<"\n\n\t\t****************M E N U****************\n\n";
		cout<<"--------------------------------------------------";
		cout<<"\n\tD D A\t\tA L G O R I T H M\n\n";
		cout<<"1.THICK LINE\t2.DOTTED LINE\t3.NORMAL LINE";
		cout<<"\n\n--------------------------------------------------";

		cout<<"\n\n\tB R E S E N H A M' s\t\tA L G O R I T H M\n\n";
		cout<<"4.THICK LINE\t5.DOTTED LINE\t6.NORMAL LINE\n\n";
		cout<<"--------------------------------------------------\n7.EXIT";


		cout<<"\n\nENTER CHOICE:-\t";
		cin>>chmnu;

		if(chmnu==7)
			break;

		if(chmnu>=1 && chmnu<=3)
			modch=1;
		else
			modch=2;

		cout<<"\n\nENTER THE END POINTS OF THE LINE (xa,ya)&(xb,yb) :-\t";
		cin>>xa>>ya>>xb>>yb;

		switch(modch)
		{
			case 1: clrscr();
				  cleardevice();
				  ddaline(xa,ya,xb,yb,chmnu);
				  break;

			case 2: clrscr();
				  cleardevice();
				  breshline((int)(ceil(xa)),(int)(ceil(ya)),(int)(ceil(xb)),(int)(ceil(yb)),chmnu );
				  break;

			default: cout<<"ENTER PROPER VALUES";
		}
		getch();
	}while(1);

	closegraph();

}

void ddaline(float xa,float ya,float xb,float yb,int type_dda)
{

	float dx,dy,tx,ty,wxy;
	int steps,i,j;
	int x,y,thickn=2,flag;


	xa=ceil(xa);
	xb=ceil(xb);
	ya=ceil(ya);
	yb=ceil(yb);

	tx=xa;
	ty=ya;

	dx=xb-xa;
	dy=yb-ya;

	if(abs(dx)<abs(dy))
	{
		steps=dy;
		flag=2;
	}
	else
	{
		steps=dx;
		flag=1;
	}

	dx=dx/abs(steps);
	dy=dy/abs(steps);

	x=(int)(xa);
	y=(int)(ya);

	if(type_dda==1)
	{
		cout<<"\n\nENTER THICKNESS OF THE LINE:-\t";
		cin>>thickn;
	}

	//LOOP TO PRINT LINE
	for(i=0;i<abs(steps);i++)
	{
		if(type_dda==3 || type_dda==1)   //TO PLOT NORMAL LINE
			putpixel(x,y,CYAN);

		if(type_dda==2 && i%2!=0)   //TO PLOT DOTTED LINE
			putpixel(x,y,CYAN);

		tx+=dx;
		x=(int)(floor(tx+0.5));

		ty+=dy;
		y=(int)(floor(ty+0.5));

	}

	if(type_dda!=1)
		return;

	//THIS SEGMENT OF CODE ONLY FOR THICK LINE
	if(flag==1)
	{
	     wxy=( (thickn-1) * sqrt((double) ( pow( (xb-xa),2 ) + pow( (yb-ya),2 ) ) ) );
	     wxy/=(2.0* (xb-xa));
	}
	else
	{
	     wxy=( (thickn-1) * sqrt((double) ( pow( (xb-xa),2 ) + pow( (yb-ya),2 ) ) ) );
	     wxy/=(2.0* (yb-ya));
	}

	for(i=1;i<=fabs(wxy);i++)
	{

		if(flag==1)
		{
			ddaline(xa,ya+i,xb,yb+i,3);
			ddaline(xa,ya-i,xb,yb-i,3);
		}

		else
		{
			ddaline(xa+i,ya,xb+i,yb,3);
			ddaline(xa-i,ya,xb-i,yb,3);
		}
	}

}

void breshline(int xa,int ya,int xb,int yb,int type_br)
{
	int i,dx,dy,swp,x2=xb,x1=xa,y2=yb,y1=ya,thickn,e,flag;
	int upto,start,var,j;
	float wxy;

	dx=x2-x1;
	dy=y2-y1;


	if(abs(dx)>=abs(dy))   //CONDITION FOR GENTLE SLOPE
	{
		if(x2<x1)
		{
			swp=x2;
			x2=x1;
			x1=swp;

			swp=y2;
			y2=y1;
			y1=swp;
		}

		dy=y2-y1;
		dx=x2-x1;

		e=2*dy-dx;
		flag=0;	//FLAG IS RESET FOR GENTLE SLOPE
		upto=x2;
		start=x1;

		if(y2<y1)
			var=y2;
		else
			var=y1;

	}

	else        //FOR SHARP SLOPE
	{
		if(y2<y1)
		{
			swp=x2;
			x2=x1;
			x1=swp;

			swp=y2;
			y2=y1;
			y1=swp;
		}
		dy=y2-y1;
		dx=x2-x1;


		e=2*dx-dy;
		flag=1;	//FLAG IS SET FOR SHARP SLOPE
		upto=y2;
		start=y1;

		if(x2<x1)
			var=x2;
		else
			var=x1;
	}


	if(type_br==4)
	{
		cout<<"\n\nENTER THICKNESS OF THE LINE:-\t";
		cin>>thickn;
	}

	//HERE WE GO.....STARTING FROM A SCRATCH

	for(i=start;i<=upto;i++)
	{
		if(type_br==4 || type_br==6)
		{
			if(!flag)
				putpixel(i,var,CYAN);

			else
				putpixel(var,i,CYAN);
		}

		else
		{
			if(i%2==0)
			{
				if(!flag)
					putpixel(i,var,CYAN);

				else
					putpixel(var,i,CYAN);
			}
		}

		if(e<0)
		{
			if(flag)
				e+=2*dx;
			else
				e+=2*dy;
		}

		else
		{
			if(flag)
				e+=2*(dx-dy);

			else
				e+=2*(dy-dx);
			var++;

		}

	}

	if(type_br!=4)
		return;

	//THIS SEGMENT OF CODE ONLY FOR THICK LINE
	if(!flag)
	{
	     wxy=( (thickn-1) * sqrt((double) ( pow( (xb-xa),2 ) + pow( (yb-ya),2 ) ) ) );
	     wxy/=(2.0* (xb-xa));
	}
	else
	{
	     wxy=( (thickn-1) * sqrt((double) ( pow( (xb-xa),2 ) + pow( (yb-ya),2 ) ) ) );
	     wxy/=(2.0* (yb-ya));
	}

	for(j=1;j<=fabs(wxy);j++)
	{
		if(!flag)
		{
			breshline(xa,ya-j,xb,yb-j,6);
			breshline(xa,ya+j,xb,yb+j,6);
		}
		else
		{
			breshline(xa-j,ya,xb-j,yb,6);
			breshline(xa+j,ya,xb+j,yb,6);
		}

	}
}

