//PROGARM TO IMPLEMENT VARIOUS POLYGON FILLING ALGORITHMS

//ANIRUDH TOMER...SE 42028...SE COMP-I
//CAUTION !!! (copyrighted program....so everyone has the right to copy it.ha.ha.ha)

#include<iostream.h>
#include<conio.h>
#include<graphics.h>

class polygon
{
	int dimen;
	int *polx,*poly;

	public:

	polygon()
	{
		dimen=3;
	}
	//prototypes for workhorse
	void wk_hors_bfill(int,int);
	void wk_hors_ffill(int,int);

	void enterpolygon();
	void printpolygon();

	//DEFINITON OF DRIVER FUNCTION
	void boundaryfill()
	{
		int bx,by,res;

		setcolor(CYAN);

		clrscr();
		cleardevice();
		printpolygon();


		do
		{
			cout<<"\n\nENTER ANY POINT (which is surely inside polygon):-\t";
			cin>>bx>>by;

			res=mydetect(bx,by);
		}while(res==0);

		wk_hors_bfill(bx,by);

	}

	void floodfill()
	{
		int fx,fy,res;

		boundaryfill();

		do
		{
			cout<<"\n\nENTER ANY POINT (which is surely inside polygon):-\t";
			cin>>fx>>fy;

			res=mydetect(fx,fy);
		}while(res==0);

		wk_hors_ffill(fx,fy);


	}

	void edgefill();
	void scanlinefill();


	int detect(int,int);

	int mydetect(int,int); //my algorithm

	int complement(int px,int py)
	{
		if(getpixel(px,py)==RED)
			return BLACK;
		return RED;
	}

};

int main()
{

	int gd=DETECT,gm,chmnu;
	polygon p1;

	initgraph(&gd,&gm,"c:\\tc\\bgi");

	setcolor(CYAN);
	clrscr();
	cleardevice();

	p1.enterpolygon();

	cleardevice();
	p1.printpolygon();

	outtextxy(0,0,"PRESS ANY KEY TO CONTINUE");

	while(1)
	{
		getch();
		clrscr();
		cleardevice();

		cout<<"\n\nCAUTION!!! IF YOUR POLYGON IS TOO BIG THEN U R GONNA HAVE A BIG PROBLEM";
		cout<<"\n\nAVOID CONCAVE POLYGON AS MUCH AS U CAN";
		cout<<"\n\n\t\t***********POLYGON FILLING************";
		cout<<"\n\n1.BOUNDARY FILL (seed point)\n\n2.FLOOD FILL(seed point)";
		cout<<"\n\n3.EDGE FILL\n\n4.SCAN LINE FILL\n\n5.EXIT";

		cout<<"\n\nEnter Your choice:-\t";
		cin>>chmnu;

		switch(chmnu)
		{
			case 1: p1.boundaryfill();
					break;

			case 2: p1.floodfill();
					break;

			case 3: p1.edgefill();
					break;

			case 4: p1.scanlinefill();
					break;

			case 5: closegraph();
					return 0;

			default: cout<<"\n\nENTER PROPER CHOICE";
		}
	}



}

/**********FUNCTION TO ENTER POLYGON COORDINATES************/

void polygon::enterpolygon()
{
	int i;

	do
	{
		cout<<"\n\nENTER THE NUMBER OF SIDES OF THE POLYGON ( >3 ):-\t";
		cin>>dimen;
	}while(dimen<3);

	polx=new int[dimen+2];
	poly=new int[dimen+2];

	dimen++;

	cout<<"\n\nENTER THE COORDINATES OF POLYGON IN ANTICLOCKWISE WAY::\n";

	for(i=1;i<dimen;i++)
	{
		cout<<"\nEnter the coordinates of vertex "<<i<<" :-\t";
		cin>>polx[i]>>poly[i];
	}

	polx[0]=polx[dimen-1];
	poly[0]=poly[dimen-1];

	polx[dimen]=polx[1];
	poly[dimen]=poly[1];
}

/***********FUNCTION TO PRINT EMPTY POLYGON***********/
void polygon::printpolygon()
{
	int i;

	for(i=1;i<dimen;i++)
		line(polx[i],poly[i],polx[i+1],poly[i+1]);

}

/****************BOUNDARY FILL (seed point algorithm)*********/

void polygon::wk_hors_bfill(int nx,int ny)
{
	int prescolor;

	prescolor=getpixel(nx,ny);
	putpixel(nx,ny,CYAN);

	if(prescolor!=CYAN)
	{
		wk_hors_bfill(nx+1,ny); //right
		wk_hors_bfill(nx-1,ny); //left
		wk_hors_bfill(nx,ny+1); //down
		wk_hors_bfill(nx,ny-1); //up
	}
}

/**************** FLOOD FILL (seed point algorithm) *********/

void polygon::wk_hors_ffill(int fx,int fy)
{
	int prescolor;

	prescolor=getpixel(fx,fy);

	if(prescolor==CYAN)
	{
		putpixel(fx,fy,RED);
		wk_hors_ffill(fx+1,fy); //right
		wk_hors_ffill(fx-1,fy); //left
		wk_hors_ffill(fx,fy+1); //down
		wk_hors_ffill(fx,fy-1); //up
	}
}


/********************* EDGE FILL *************************/

void polygon::edgefill()
{
	int i,j,x_cor;

	setcolor(CYAN);
	cleardevice();

	printpolygon();  //prints the polygon


	for(i=1;i<dimen;i++) //to select edge
	{

		j=poly[i];

		if(poly[i+1]>poly[i] && i!=0)
			j++;
		if(poly[i+1]<poly[i] && i!=0)
			j--;

		while(1)           //to select scanline
		{
			for(x_cor=0;CYAN!=getpixel(x_cor,j);x_cor++)
			{
				putpixel(x_cor,j,complement(x_cor,j));
			}

			if(poly[i]==poly[i+1])
			{
				while(x_cor!=polx[i+1])
				{
					putpixel(x_cor,j,complement(x_cor,j));
					x_cor++;
				}

				break;
			}
			if(poly[i]<poly[i+1])
			{
				j++;
				if(j>poly[i+1])
					break;
			}

			else
			{
				j--;
				if(j<poly[i+1])
					break;
			}


		}
		setcolor(RED);
		line(polx[i],poly[i],polx[i+1],poly[i+1]);

		setcolor(CYAN);
		putpixel(polx[i],poly[i],CYAN);
	}

	setcolor(BLACK);

	for(i=1;i<dimen;i++)
	   line(0,poly[i],639,poly[i]);

	setcolor(RED);

	for(i=1;i<dimen;i++)
	{
		for(j=i+1;j<dimen;j++)
			if(poly[i]==poly[j])
				line(polx[i],poly[i],polx[j],poly[j]);
	}

}

/*************** SCAN LINE FILLING METHOD *******************/
void polygon::scanlinefill()
{
	int i,j,res,col,k;
	int arrcyan[10]={0,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	int y_top=poly[1],y_bottom=poly[1];
	int x_left=polx[1],x_right=polx[1];

	setcolor(CYAN);

	for(i=2;i<dimen;i++)
	{
		if(x_left>polx[i])
			x_left=polx[i];

		if(x_right<polx[i])
			x_right=polx[i];


		if(y_top>poly[i])
			y_top=poly[i];

		if(y_bottom<poly[i])
			y_bottom=poly[i];
	}

	cleardevice();
	printpolygon();

	setcolor(RED);

	for(j=y_top;j<=y_bottom;j++) //chooses a scan line
	{
		arrcyan[0]=0;
		for(i=x_left,k=0;i<=x_right;i++)
		{
			if(getpixel(i,j)==CYAN)
			{
				arrcyan[0]++;
				arrcyan[++k]=i;
			}

		}

		if(arrcyan[0]%2==0)
		{
			for(k=1;k<=arrcyan[0];k+=2)
			{
				if(detect(arrcyan[k]+1,j))
					line(arrcyan[k]+1,j,arrcyan[k+1]-1,j);
			}
		}

		else
		{
			for(k=1;k<arrcyan[0];k++)
			{
				if(detect(arrcyan[k]+1,j))
					line(arrcyan[k]+1,j,arrcyan[k+1]-1,j);
			}

		}

	}

	for(i=1;i<dimen;i++)
		line(polx[i],poly[i],polx[i+1],poly[i+1]);

}


/*********FUNCTION FOR EVEN-ODD METHOD TO CHECK STATUS OF A POINT********/

int polygon::detect(int dx,int dy)
{
	int i,j,check_color,cnt;

	int arrx[10]={0,-1,-1,-1,-1,-1,-1,-1,-1,-1}; //initialized to -1;

	int minx=polx[1];

	for(i=2;i<dimen;i++)
		if(minx>polx[i])
			minx=polx[i];


	for(i=minx,j=1;i<dx;i++)
	{
		check_color=getpixel(i,dy);

		if(check_color==CYAN)
		{
			arrx[0]++;      //arrx[0] contains number of intersections
			arrx[j]=i;
			j++;
		}
	}

	for(i=1,cnt=arrx[0];i<dimen;i++)
	{
		for(j=1;arrx[j]!=-1 && j<10;j++)
		{
			if(arrx[j]==polx[i] && dy==poly[i]) //if any point is a vertex
			{
				if( (poly[i-1]<dy && poly [i+1]<dy) ||(poly[i-1]>dy && poly[i+1]>dy) )
					cnt++;
			}

		}
	}

	if(cnt%2==0)
		return 0;

	return 1;
}


/*************MY ALGORITHM TO DETECT IF A PT. IS INSIDE A POLYGON**********/

int polygon::mydetect(int mdx,int mdy)
{
	int i,cnt=0;
	int minx=polx[1],miny=poly[1],maxx=polx[1],maxy=poly[1];

	for(i=2;i<dimen;i++)
	{
		if(minx>polx[i])
			minx=polx[i];

		if(maxx<polx[i])
			maxx=polx[i];

		if(miny>poly[i])
			miny=poly[i];

		if(maxy<poly[i])
			maxy=poly[i];
	}

	//search in left
	for(i=mdx;i>=minx;i--)
	{
		if(getpixel(i,mdy)==CYAN)
		{
			cnt++;
			break;
		}
	}

	//search in right
	for(i=mdx;i<=maxx;i++)
	{
		if(getpixel(i,mdy)==CYAN)
		{
			cnt++;
			break;
		}
	}

	//search up
	for(i=mdy;i>=miny;i--)
	{
		if(getpixel(mdx,i)==CYAN)
		{
			cnt++;
			break;
		}
	}

	//search down
	for(i=mdy;i<=maxy;i++)
	{
		if(getpixel(mdx,i)==CYAN)
		{
			cnt++;
			break;
		}
	}

	if(cnt==4)  //all 4 conditions are satisfied
		return 1;

	return 0;

}