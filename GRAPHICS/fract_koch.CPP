#include<dos.h>
#include<stdlib.h>
#include<math.h>
#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<time.h>

float factor = -1.0;

class fractal
{
	float x1,y1,x2,y2;

	float arrx[4],arry[4];

	float weight;

	float sinq,cosq;  //q is actually theta (weight) for me

	int STOP,minsidetri;

	public:
	fractal()
	{
		x1 = 100;
		y1 = 100;

		x2 = 400;
		y2 = 100;
	};

	void calcangle_line(float xa,float ya,float xb,float yb,float &sinex,float &cosinex,float &len)
	{
		len = sqrt( pow((yb-ya),2) + pow((xb-xa),2) );

		sinex = (yb-ya)/len;
		cosinex = (xb-xa)/len;
	}

	void enter_disp_line();
	void enter_disp_triangle();
	void enter_disp_koch();

	void perform_surface(float *,float*);
	void perform_line(float,float,float,float,float*,float*);
	void perform_koch(float,float,float,float,int cnt);


	void perform_line()
	{
		perform_line(x1,y1,x2,y2,&::factor,&::factor);
	}

	void perform_surface()
	{
		perform_surface(arrx,arry);
	}

	void perform_koch()
	{
		perform_koch(x1,y1,x2,y2,pow(4,STOP));
	}
};

int main()
{
	int gd = DETECT,gm,chmnu;

	fractal f1;

	randomize();

	initgraph(&gd,&gm,"c:\\tc\\bgi");

	while(1)
	{
		clrscr();
		cleardevice();

		cout<<"\n\n****************** F R A C T A L \tM A G I C *****************";
		cout<<"\n\n\n1.FRACTAL LINES\n\n2.FRACTAL SURFACES\n\n3.KOCH CURVE";
		cout<<"\n\n4.EXIT";
		cout<<"\n\nENTER YOUR CHOICE:-\t";
		cin>>chmnu;

		clrscr();
		cleardevice();

		switch(chmnu)
		{
			case 1: f1.enter_disp_line();

					setcolor(MAGENTA);
					delay(1000);
					cleardevice();

					f1.perform_line();

					setcolor(WHITE);

					break;

			case 2: f1.enter_disp_triangle();

					setcolor(MAGENTA);
					delay(1000);
					cleardevice();

					f1.perform_surface();

					setcolor(WHITE);

					break;

			case 3: f1.enter_disp_koch();

					setcolor(MAGENTA);
					delay(1000);
					cleardevice();

					f1.perform_koch();

					setcolor(WHITE);
					break;

			case 4: return 0;

			default : cout<<"\n\nENTER PROPER CHOICE";
		}
		getch();
	}
}

/***************** FRACTAL LINES STARTS HERE *******************/


//FUNCTION TO ENTER THE LINE
void fractal::enter_disp_line()
{
	cout<<"\n\nENTER THE COORDINATES OF THE LINE:-\t";
	cin>>x1>>y1>>x2>>y2;

	cout<<"\n\nENTER THE WEIGHTING FACTOR (theta upto 0.78) :-\t";
	cin>>weight;

	cout<<"\n\nENTER THE STOPPING PIXEL VALUE (smaller value lead to closer cuts):-\t";
	cin>>STOP;

	sinq = sin(weight);
	cosq = cos(weight);

	cleardevice();
	line(x1,y1,x2,y2);
}

//FUNCTION TO DO CONVERSION OF A LINE TO A FRATAL LINE
void fractal::perform_line(float xa,float ya,float xb,float yb,float *sox,float *soy)
{
	int ub;
	float ox,oy;
	float sinx,cosx;
	float sin_q_x,cos_q_x;

	float hyplen,lenline;

	ub = random(10000);

	calcangle_line(xa,ya,xb,yb,sinx,cosx,lenline);

	hyplen = lenline/(cosq*2.0);

	sin_q_x = sinq*cosx + sinx*cosq;
	cos_q_x = cosq*cosx - sinx*sinq;

	if(ub%2==0)
	{
		ox = xa + hyplen*cos_q_x;
		oy = ya + hyplen*sin_q_x;
	}

	else
	{
		ox = xb - hyplen*cos_q_x;
		oy = yb - hyplen*sin_q_x;
	}

	if(lenline/2 <STOP && (*sox==-1 && *soy ==-1) )
	{
		line(xa,ya,ox,oy);
		line(xb,yb,ox,oy);

		return;
	}

	if(*sox==-1.0 && *soy==-1.0)
	{
		perform_line(xa,ya,ox,oy,&::factor,&::factor);
		perform_line(ox,oy,xb,yb,&::factor,&::factor);
	}
	else
	{
		setcolor(BLACK);
		line(xa,ya,xb,yb);

		setcolor(MAGENTA);
		line(xa,ya,ox,oy);
		line(xb,yb,ox,oy);

		*sox = ox;
		*soy = oy;
	}

}


/***************** FRACTAL SURFACES STARTS HERE *******************/


//FUNCTION TO ENTER THE TRIANGULAR SURFACE
void fractal::enter_disp_triangle()
{
	int i;

	for(i=0;i<3;i++)
	{
		cout<<"\n\nENTER COORDINATES FOR VERTEX "<<i+1<<" :-\t";
		cin>>arrx[i]>>arry[i];
	}
	arrx[3] = arrx[0];
	arry[3] = arry[0];

	weight = 0.1;

	cout<<"ENTER THE MIN PERIMETER OF THE TRIANGLE:-\t";
	cin>>minsidetri;

	sinq = sin(weight);
	cosq = cos(weight);

	cleardevice();

	for(i=0;i<3;i++)
		line(arrx[i],arry[i],arrx[i+1],arry[i+1]);
}

//FUNCTION TO PERFORM FRACTALISATION ON A TRIANGULAR SURFACE
void fractal::perform_surface(float *ax,float *ay)
{
	int i;

	float len1,len2,len3;

	float *ox = new float [3],*oy = new float [3];
	float *tarx = new float [4],*tary = new float[4];

	len1 = sqrt( pow((ax[0]-ax[1]),2) + pow((ay[0]-ay[1]),2) );
	len2 = sqrt( pow((ax[1]-ax[2]),2) + pow((ay[1]-ay[2]),2) );
	len3 = sqrt( pow((ax[2]-ax[3]),2) + pow((ay[2]-ay[3]),2) );


	if( (len1+len2+len3) < minsidetri)
		goto end;

	for(i=0;i<3;i++)
	{
		perform_line(ax[i],ay[i],ax[i+1],ay[i+1],(ox+i),(oy+i));
	}

	//1st internal triangle

	tarx[0] = ax[0];
	tary[0] = ay[0];

	tarx[1] = ox[0];
	tary[1] = oy[0];

	tarx[2] = ox[2];
	tary[2] = oy[2];

	tarx[3] = ax[0];
	tary[3] = ay[0];

	perform_surface(tarx,tary);

	//2nd internal triangle

	tarx[0] = ox[0];
	tary[0] = oy[0];

	tarx[1] = ax[1];
	tary[1] = ay[1];

	tarx[2] = ox[1];
	tary[2] = oy[1];

	tarx[3] = ox[0];
	tary[3] = oy[0];

	perform_surface(tarx,tary);

	//3rd internal triangle

	tarx[0] = ox[0];
	tary[0] = oy[0];

	tarx[1] = ox[1];
	tary[1] = oy[1];

	tarx[2] = ox[2];
	tary[2] = oy[2];

	tarx[3] = ox[0];
	tary[3] = oy[0];

	perform_surface(tarx,tary);

	//4th internal triangle

	tarx[0] = ox[2];
	tary[0] = oy[2];

	tarx[1] = ox[1];
	tary[1] = oy[1];

	tarx[2] = ax[2];
	tary[2] = ay[2];

	tarx[3] = ox[2];
	tary[3] = oy[2];

	perform_surface(tarx,tary);

	end:
	delete []ox;
	delete []oy;
	delete []tarx;
	delete []tary;

}


/***************** KOCH CURVE STARTS HERE ***************/

//ENTER THE LINE FOR A KOCH CURVE

void fractal::enter_disp_koch()
{
	int i;

	cout<<"\n\nENTER THE COORDINATES OF THE LINE:-\t";
	cin>>x1>>y1>>x2>>y2;

	cout<<"\n\nENTER THE NUMBER OF ITERATIONS (>=0 && <=7):-\t";
	cin>>STOP;

	weight = 1.04;

	sinq = sin(weight);
	cosq = cos(weight);

	cleardevice();
	line(x1,y1,x2,y2);
}

//draw koch curve
void fractal::perform_koch(float xa,float ya,float xb,float yb,int cnt)
{
	float ox,oy;
	float sinx,cosx;
	float sin_q_x,cos_q_x;

	float hyplen,lenline;
	float mx1,my1,mx2,my2;

	mx1 = (2*xa+xb)/3.0;
	my1 = (2*ya+yb)/3.0;

	mx2 = (mx1 + xb)/2.0;
	my2 = (my1 + yb)/2.0;

	calcangle_line(mx1,my1,mx2,my2,sinx,cosx,lenline);

	hyplen = lenline/(cosq*2.0);

	sin_q_x = sinq*cosx + sinx*cosq;
	cos_q_x = cosq*cosx - sinx*sinq;

	ox = mx2 - hyplen*cos_q_x;
	oy = my2 - hyplen*sin_q_x;

	//due to floating pt values the pixels aren't exactly placed
	//so i have to draw lines in fractions & leaving the middle part

	setcolor(BLACK);
	line(xa,ya,xb,yb);

	setcolor(MAGENTA);

	line(xa,ya,mx1,my1);
	line(mx2,my2,xb,yb);

	line(mx1,my1,ox,oy);
	line(mx2,my2,ox,oy);

	cnt=cnt/4;

	if(!cnt)
		return;

	//recursive calls

	perform_koch(xa,ya,mx1,my1,cnt);
	perform_koch(mx1,my1,ox,oy,cnt);
	perform_koch(ox,oy,mx2,my2,cnt);
	perform_koch(mx2,my2,xb,yb,cnt);

}