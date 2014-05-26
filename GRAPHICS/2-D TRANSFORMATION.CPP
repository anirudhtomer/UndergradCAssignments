//PROGRAM TO DO 2D TRANSFORMATIONS

#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>

class tood
{
	float *polx,*poly;

	float *tpolx,*tpoly;

	float dimen;

	float tmat[3][3];
	float vmat[1][3];

	public:

	tood()
	{
		polx = poly = NULL;
		tpolx = tpoly = NULL;
		dimen = 0;
	}

	void resetvset();
	void resettmat();

	void enter();
	void display();
	void tdisplay();

	void scaling(float,float);
	void translation(float,float);
	void roty();
	void rotx();
	void rot_y_x();
	void rot_x_y();
	void shearx();
	void sheary();
	void rotpt();

	void multiply();


};

int main()
{
	int gd = DETECT,gm;
	int chmnu;
	float tx,ty;

	tood t1;

	initgraph(&gd,&gm,"c:\\tc\\bgi");

	clrscr();
	cleardevice();

	t1.enter();
	t1.resetvset();

	while(1)
	{
		clrscr();
		cleardevice();
		cout<<"\n\n\t\t2-D\t\t T R A N S F O R M A T I O N S\n";
		cout<<"\n\n1.SCALING\n\n2.TRANSLATION\n\n3.ROTATION ABOUT Y AXIS\n\n";
		cout<<"4.ROTATION ABOUT X AXIS\n\n5.ROTATION ABOUT Y=X\n\n6.ROTATION ABOUT X=Y";
		cout<<"\n\n7.SHEAR ALONG X\n\n8.SHEAR ALONG Y\n\n9.ROTATION ABOUT A POINT\n\n10.EXIT";

		cout<<"\n\nEnter Your Choice:-\t";
		cin>>chmnu;

		clrscr();
		cleardevice();

		t1.resettmat();
		t1.resetvset();

		switch(chmnu)
		{
			case 1: cout<<"\n\nENTER THE SCALING FACTOR FOR X & Y:-\t";
					cin>>tx>>ty;

					t1.scaling(tx,ty);
					break;

			case 2: cout<<"ENTER THE TRANSLATION FACTOR FOR X & Y:-\t";
					cin>>tx>>ty;

					t1.translation(tx,ty);
					break;

			case 3: t1.roty();
					break;

			case 4: t1.rotx();
					break;

			case 5: t1.rot_y_x();
					break;

			case 6: t1.rot_x_y();
					break;

			case 7: t1.shearx();
					break;

			case 8: t1.sheary();
					break;

			case 9: t1.rotpt();
					break;

			case 10:closegraph();
					return 0;

			default: cout<<"PROPER CHOICE ENTER KAR";
		}
		getch();
	}
}

void tood::enter()
{
	int i;

	cout<<"\n\nENTER THE NUMBER OF THE VERTICES:-\t";
	cin>>dimen;

	polx = new float[dimen+1];
	poly = new float[dimen+1];

	tpolx = new float[dimen+1];
	tpoly = new float[dimen+1];

	cout<<"\n\nENTER THE POLYGON:::\n\n\n";

	for(i=0;i<dimen;i++)
	{
		cout<<"\n\nENTER VERTEX(-320<x<320 && -240<y<240) "<<i+1<<" :-\t";
		cin>>polx[i]>>poly[i];
	}

	polx[dimen] = polx[0];
	poly[dimen] = poly[0];

}

void tood::display()
{
	int i;

	cleardevice();
	setcolor(DARKGRAY);

	line(0,240,639,240);
	line(320,0,320,479);


	setcolor(LIGHTBLUE);

	for(i=0;i<dimen;i++)
		line(polx[i]+320,240-poly[i],polx[i+1]+320,240-poly[i+1]);

}

void tood::tdisplay()
{
	int i;

	cleardevice();
	setcolor(DARKGRAY);

	line(0,240,639,240);
	line(320,0,320,479);

	setcolor(MAGENTA);

	for(i=0;i<dimen;i++)
		line(tpolx[i]+320,240-tpoly[i],tpolx[i+1]+320,240-tpoly[i+1]);

}

void tood::resetvset()
{
	int i;

	for(i=0;i<=dimen;i++)
	{
		tpolx[i] = polx[i];
		tpoly[i] = poly[i];
	}

}

void tood::resettmat()
{
	tmat[0][0] = 1;
	tmat[0][1] = 0;
	tmat[0][2] = 0;

	tmat[1][0] = 0;
	tmat[1][1] = 1;
	tmat[1][2] = 0;

	tmat[2][0] = 0;
	tmat[2][1] = 0;
	tmat[2][2] = 1;

}

void tood::multiply()
{
	int i,j;
	float temp[1][3] = {0,0,0};

	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			temp[0][i] += vmat[0][j] * tmat[j][i];

	vmat[0][0] = temp[0][0];
	vmat[0][1] = temp[0][1];
	vmat[0][2] = temp[0][2];

}

void tood::scaling(float sx,float sy)
{
	int i;


	cleardevice();

	display();

	tmat[0][0] = sx;
	tmat[1][1] = sy;

	for(i=0;i<=dimen;i++)
	{
		vmat[0][0] = polx[i];
		vmat[0][1] = poly[i];
		vmat[0][2] = 1;

		multiply();

		tpolx[i] = vmat[0][0];
		tpoly[i] = vmat[0][1];

	}

	getch();
	cleardevice();

	tdisplay();

}

void tood::translation(float tx,float ty)
{
	int i;

	display();

	tmat[2][0] = tx;
	tmat[2][1] = ty;

	for(i=0;i<=dimen;i++)
	{
		vmat[0][0] = tpolx[i];
		vmat[0][1] = tpoly[i];
		vmat[0][2] = 1;

		multiply();

		tpolx[i] = vmat[0][0];
		tpoly[i] = vmat[0][1];
	}

	getch();
	tdisplay();

}

void tood::roty()
{
	scaling(-1,1);
}

void tood::rotx()
{
	scaling(1,-1);
}

void tood::rot_y_x()
{
	int i;


	tmat[0][0] = 0;
	tmat[0][1] = 1;
	tmat[1][0] = 1;
	tmat[1][1] = 0;

	display();

	for(i=0;i<=dimen;i++)
	{
		vmat[0][0] = polx[i];
		vmat[0][1] = poly[i];
		vmat[0][2] = 1;

		multiply();

		tpolx[i] = vmat[0][0];
		tpoly[i] = vmat[0][1];
	}

	getch();
	tdisplay();

}


void tood::rot_x_y()
{
	int i;


	tmat[0][0] = 0;
	tmat[0][1] = -1;
	tmat[1][0] = -1;
	tmat[1][1] = 0;

	display();

	for(i=0;i<=dimen;i++)
	{
		vmat[0][0] = polx[i];
		vmat[0][1] = poly[i];
		vmat[0][2] = 1;

		multiply();

		tpolx[i] = vmat[0][0];
		tpoly[i] = vmat[0][1];
	}

	getch();
	tdisplay();

}

void tood::shearx()
{
	int a,i;

	cout<<"\n\nENTER THE SHEAR FACTOR:-\t";
	cin>>a;


	tmat[1][0] = a;
	display();

	for(i=0;i<=dimen;i++)
	{
		vmat[0][0] = polx[i];
		vmat[0][1] = poly[i];
		vmat[0][2] = 1;

		multiply();

		tpolx[i] = vmat[0][0];
		tpoly[i] = vmat[0][1];
	}

	getch();
	tdisplay();

}

void tood::sheary()
{
	int a,i;

	cout<<"\n\nENTER THE SHEAR FACTOR:-\t";
	cin>>a;


	tmat[0][1] = a;
	display();

	for(i=0;i<=dimen;i++)
	{
		vmat[0][0] = polx[i];
		vmat[0][1] = poly[i];
		vmat[0][2] = 1;

		multiply();

		tpolx[i] = vmat[0][0];
		tpoly[i] = vmat[0][1];
	}

	getch();
	tdisplay();

}

void tood::rotpt()
{
	int i,rx,ry;
	float ang;

	cout<<"ENTER THE PT OF ROTATION:-\t";
	cin>>rx>>ry;

	cout<<"\n\nENTER THE ANGLE OG ROTATION:-\t";
	cin>>ang;

	ang = ang *3.14/180;

	translation(-rx,-ry);

	resettmat();

	tmat[0][0] = cos(ang);
	tmat[0][1] = sin(ang);
	tmat[1][0] = -sin(ang);
	tmat[1][1] = cos(ang);


	for(i=0;i<=dimen;i++)
	{
		vmat[0][0] = polx[i];
		vmat[0][1] = poly[i];
		vmat[0][2] = 1;

		multiply();

		tpolx[i] = vmat[0][0];
		tpoly[i] = vmat[0][1];
	}

	translation(rx,ry);

}