//PROGRAM TO MAKE A BEZIER CURVE

#include<dos.h>
#include<stdlib.h>
#include<math.h>
#include<iostream.h>
#include<conio.h>
#include<graphics.h>

class bezier
{
	int ax[4],ay[4];
	int cnt;

	int *jblx,*jbly;

	public:
	bezier()
	{
		cnt = 0;
		jblx = NULL;
		jbly = NULL;
	}

	void perform(int *,int*);

	void enter();

	void display();

	void perform()
	{
		perform(ax,ay);
	}

	void detectallpt();
	void joinbyline();
};

int main()
{
	int gd=DETECT,gm;
	bezier b1;

	initgraph(&gd,&gm,"c:\\tc\\bgi");

	setcolor(MAGENTA);

	b1.enter();

	cleardevice();

	b1.display();

	b1.perform();

	b1.detectallpt();

	b1.joinbyline();

	getch();
	return 0;
}

void bezier::enter()
{
	int i;

	for(i=0;i<4;i++)
	{
		cout<<"\n\nENTER THE COORDINATES OF VERTEX "<<i+1<<" :-\t";
		cin>>ax[i]>>ay[i];
	}

}

void bezier::display()
{
	int i;

	for(i=0;i<3;i++)
		line(ax[i],ay[i],ax[i+1],ay[i+1]);

}

void bezier::perform(int *arrx,int *arry)
{
	int i;

	int *alphax = new int [6] ,*alphay = new int [6];

	int *tx = new int [4],*ty = new int [4];

	for(i=0;i<3;i++)       // to find first three mid pts
	{
		alphax[i] = ( arrx[i] + arrx[i+1] )/2;
		alphay[i] = ( arry[i] + arry[i+1] )/2;
	}

	for(i=0;i<2;i++) // to find next two mid pts
	{
		alphax[i+3] = ( alphax[i] + alphax[i+1] )/2;
		alphay[i+3] = ( alphay[i] + alphay[i+1] )/2;
	}

	alphax[5] = ( alphax[3] + alphax[4] )/2;
	alphay[5] = ( alphay[3] + alphay[4] )/2;

	if( ((alphax[5] == arrx[0]) && (alphay[5] == arry[0])) || ((alphax[5] == arrx[3]) && (alphay[5] == arry[3])))
		return;

	putpixel(alphax[5],alphay[5],WHITE);
	cnt++;

	//each 4 sided polygon gives two similar polygons

	//1. poly1

	tx[0] = arrx[0];
	ty[0] = arry[0];

	tx[1] = alphax[0];
	ty[1] = alphay[0];

	tx[2] = alphax[3];
	ty[2] = alphay[3];

	tx[3] = alphax[5];
	ty[3] = alphay[5];

	perform(tx,ty);

	tx[0] = alphax[5];
	ty[0] = alphay[5];

	tx[1] = alphax[4];
	ty[1] = alphay[4];

	tx[2] = alphax[2];
	ty[2] = alphay[2];

	tx[3] = arrx[3];
	ty[3] = arry[3];

	perform(tx,ty);

	delete []tx;
	delete []ty;

	delete []alphax;
	delete []alphay;

}

void bezier::detectallpt()
{
	int i,j,xcnt=0;

	int minx,miny,maxx,maxy;

	minx = maxx = ax[0];
	miny = maxy = ay[0];

	jblx = new int [cnt];
	jbly = new int [cnt];


	for(i=1;i<4;i++)
	{
		if(minx>ax[i])
			minx = ax[i];
		if(maxx<ax[i])
			maxx = ax[i];

		if(miny>ay[i])
			miny = ay[i];
		if(maxy<ay[i])
			maxy = ay[i];

	}

	for(i=miny-4;i<=479/*maxy+4*/;i++)
	{
		for(j=minx-4;j<=639/*maxx+4*/;j++)
		{
			if(WHITE == getpixel(i,j))
			{
				jblx[xcnt] = i;
				jbly[xcnt] = j;
				putpixel(i,j,YELLOW);
				xcnt++;
			}
		}
	}

	if(xcnt!=cnt)
	{
		cout<<"XCNT = "<<xcnt<<" and CNT = "<<cnt;
		getch();
	}

}

void bezier::joinbyline()
{
	int i,j;

	setcolor(BLUE);

	for(i=0;i<cnt-1;i++)
	{
		for(j=0;j<cnt-1;j++)
		{
			if(abs(jblx[i]-jblx[j])<4 && abs(jbly[i]-jbly[j])<4)
			{
				line(jblx[i],jbly[i],jblx[j],jbly[j]);
			}
		}
	}
}


