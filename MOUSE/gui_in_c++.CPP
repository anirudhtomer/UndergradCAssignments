//SIGNAL GENERATION

#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>

#define SINE 0
#define COSINE 1
#define SET 1
#define RESET 0

int cursor[32] = { //wavy cursor
				  //screen mask bitmap
				  0xffff,0xffff,0xffff,0xffff,
				  0xe7e7,0xdbeb,0xb9ed,0xbddd,
				  0xbddd,0x7ede,0x7ebe,0x7e3e,
				  0xffff,0xffff,0xffff,0xffff,

				  //mouse pointer bitmap

				  0x0000,0x0000,0x0000,0x0000,
				  0x1818,0x2414,0x4612,0x4222,
				  0x4222,0x8121,0x8141,0x81c1,
				  0x0000,0x0000,0x0000,0x0000,

				  };

class mouse
{
	protected:

	union REGS i,o;
	struct SREGS s;

	public:
	void initmouse();
	void hidemouse();
	void changecursor();
};

class signal:public mouse  //inherits class mouse
{
	const int numvert;

	float sinx;
	float wavelength,amplitude;
	float xinc;

	int initx;
	int init_angle,end_angle;

	int *arrsin,*arrcos,*arrexit;

	public:
	signal():numvert(4) //initialize constant PI..member initializer method
	{
		amplitude = 100;  //increments sin value by 100....thus "sin 90 = 1 * 100 = 100" ..thus it increments the amplitude of the sin wave
		wavelength = 216;
		xinc = wavelength/360;  //theta on x axis is incremented by 0.4 each time...to

		initx = 0; //to shift the origin of sin wave on x axis

		init_angle = 360 * 7; //"theta = 360 * X" initially...should have been 0 initially but tc draws 180 phase out in 4th quadrant
		end_angle = 0;

/*total vertices are 4 so i need
4*2=8 locations to store coordinates + 2 locations

for the first coordinate(repeated) to complete polygon */

		arrsin = new int[numvert*2 + 2];
		arrcos = new int[numvert*2 + 2];
		arrexit = new int[numvert*2 + 2];
	}

	void draw_sin_cos(int);

	int gui_choose();

	void drawmenu();

	float conv_to_rad(int deg_angle)
	{
		return(deg_angle * (M_PI/180));
	}
};

int main()
{
	int gd = DETECT,gm;
	signal s1;

	initgraph(&gd,&gm,"c:\\tc\\bgi");

	while(s1.gui_choose()!=-1)
	{
		cleardevice();
	}

	closegraph();
	return 0;
}

//GUI FOR CHOOSING THE TYPE OF THE GRAPH
int signal::gui_choose()
{
	int mx,my;
	int flagsin = 0,flagcos = 0 ,flagexit = 0;

	initmouse();
	drawmenu();

	setlinestyle(0,0,3);
	setcolor(MAGENTA);

	while(1)
	{
		i.x.ax=3;   //don't write it ouside the loop
		int86(0x33,&i,&o);

		mx = o.x.cx;
		my = o.x.dx;

		if(mx>arrsin[0] && mx<arrsin[2] && my>arrsin[1] && my<arrsin[5])
		{
			flagsin = 1;
			drawpoly(5,arrsin);

			if(o.x.bx==1)
			{
				hidemouse();
				break;
			}
		}
		else if(flagsin)
		{
			flagsin=0;
			setcolor(BLACK);
			drawpoly(5,arrsin);
			drawpoly(5,arrcos);
			drawpoly(5,arrexit);
			setcolor(MAGENTA);
		}

		if(mx>arrcos[0] && mx<arrcos[2] && my>arrcos[1] && my<arrcos[5])
		{
			flagcos=1;
			drawpoly(5,arrcos);

			if(o.x.bx==1)
			{
				hidemouse();
				break;
			}
		}
		else if(flagcos)
		{
			flagcos=0;
			setcolor(BLACK);
			drawpoly(5,arrsin);
			drawpoly(5,arrcos);
			drawpoly(5,arrexit);
			setcolor(MAGENTA);
		}

		if(mx>arrexit[0] && mx<arrexit[2] && my>arrexit[1] && my<arrexit[5])
		{
			flagexit=1;
			drawpoly(5,arrexit);

			if(o.x.bx==1)
			{
				hidemouse();
				break;
			}
		}
		else if(flagexit)
		{
			flagexit=0;
			setcolor(BLACK);
			drawpoly(5,arrsin);
			drawpoly(5,arrcos);
			drawpoly(5,arrexit);
			setcolor(MAGENTA);
		}

	}

	cleardevice();

	setlinestyle(0,0,1);

	if(flagsin==1)
		draw_sin_cos(SINE);

	if(flagcos==1)
		draw_sin_cos(COSINE);

	if(flagexit==1)
		return -1;
	return 0;
}

//DRAW THE "sine" or "cosine" SIGNAL
void signal::draw_sin_cos(int sinorcos)
{
	int theta,i;
	float rad_angle;

	float temporix = initx;  //don't use "int" here as adding 0.4 to int produces the original value

	setcolor(DARKGRAY);
	line(0,getmaxy()/2,639,getmaxy()/2);

	theta = sinorcos==SINE?init_angle:init_angle-180;  //ternary operator instead of if-else

	for(;theta>=end_angle;theta--)
	{
		rad_angle = conv_to_rad(theta);

		if(sinorcos==SINE)
			putpixel(temporix+=xinc,sin(rad_angle)*amplitude + getmaxy()/2,LIGHTRED);
		else
			putpixel(temporix+=xinc,cos(rad_angle)*amplitude + getmaxy()/2,LIGHTBLUE);
	}

	setcolor(LIGHTGRAY);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,0);


	theta = 0;
	for(i=initx;i<=639;i++)
	{
		if(i%((int)wavelength/4)==0)
		{
			outtextxy(i,getmaxy()/2+3,"i");
			theta+=90;
		}
	}

	getch();
}
//FUNCTION TO DRAW THE MENU ON THE SCREEN

void signal::drawmenu()
{
	setcolor(LIGHTBLUE);

	settextstyle(DEFAULT_FONT,HORIZ_DIR,4);

	outtextxy(40,20,"SIGNAL");
	outtextxy(270,20,"GENERATION");

	setcolor(RED);
	setfillstyle(1,LIGHTGREEN);

	//SINE BLOCK
	{
		arrsin[0] = 45;
		arrsin[1] = 95;

		arrsin[2] = 230;
		arrsin[3] = 95;

		arrsin[4] = 230;
		arrsin[5] = 121;

		arrsin[6] = 45;
		arrsin[7] = 121;

		arrsin[8] = 45;
		arrsin[9] = 95;

		fillpoly(numvert+1,arrsin);

		setcolor(RED);
		settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
		outtextxy(50,100,"SINE_SIGNAL");
	}

	//COSINE BLOCK
	{
		arrcos[0] = 45;
		arrcos[1] = 140;

		arrcos[2] = 265;
		arrcos[3] = 140;

		arrcos[4] = 265;
		arrcos[5] = 170;

		arrcos[6] = 45;
		arrcos[7] = 170;

		arrcos[8] = 45;
		arrcos[9] = 140;

		fillpoly(numvert+1,arrcos);

		setcolor(RED);
		settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
		outtextxy(50,150,"COSINE_SIGNAL");
	}

	//EXIT BLOCK
	{
		arrexit[0] = 45;
		arrexit[1] = 395;

		arrexit[2] = 115;
		arrexit[3] = 395;

		arrexit[4] = 115;
		arrexit[5] = 420;

		arrexit[6] = 45;
		arrexit[7] = 420;

		arrexit[8] = 45;
		arrexit[9] = 395;

		fillpoly(numvert+1,arrexit);

		setcolor(RED);
		settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
		outtextxy(50,400,"EXIT");
	}

	setcolor(WHITE);
}

//FUNCTION OF CLASS MOUSE TO INITIALIZE THE MOUSE
void mouse::initmouse()
{
	i.x.ax = 0;
	int86(0x33,&i,&o); //0x33 means 33h or dec 51

	//set mouse ptr location to 0,0
	i.x.ax=4;
	i.x.cx=0;
	i.x.dx=0;
	int86(0x33,&i,&o);

	i.x.ax = 1;
	int86(0x33,&i,&o);
	changecursor();
}
//function to hide the mouse

void mouse::hidemouse()
{
	i.x.ax = 2;
	int86(0x33,&i,&o);
}
//function to change the cursor of mouse

void mouse::changecursor()
{
	i.x.ax = 9;  //interrupt service number
	i.x.bx = 0;
	i.x.cx = 0;
	i.x.dx = (unsigned)cursor;

	segread(&s);   //reads the segment registers & put their value in "s"
	s.es = s.ds;  // or   mov es,ds
	int86x(0x33,&i,&o,&s); //this int86x takes values from es instead of ds
}
