//HURDLES.....anirudh tomer
//23 august 2009....11:36 AM

#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<graphics.h>
#include<math.h>
#include<time.h>

#define SIZE 5

#define UP 0
#define DOWN 1

class queuebreak;
class heli;

clock_t start, end;
float factor = -1.0;

class fractal
{
	float x1,y1,x2,y2;

	float weight;

	float sinq,cosq;  //q is actually theta (weight) for me

	int STOP;

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

	void enter_disp_koch();

	void perform_line(float,float,float,float,float*,float*);
	void perform_koch(float,float,float,float,int cnt);


	void perform_line()
	{
		perform_line(x1,y1,x2,y2,&::factor,&::factor);
	}

	void perform_koch()
	{
		perform_koch(x1,y1,x2,y2,pow(4,STOP));
	}
};

class node
{
	int loc[SIZE*2],up_down;
	int ox,oy;
	node *next;
	const int HURDLE_WIDTH;

	static int cnt_hurdle;

	public:

	node():HURDLE_WIDTH(40)
	{
		next = NULL;
		ox = getmaxx();
	}

	void reset_hurdle();
	void init_hurdle();

	friend class queuebuild;
	friend class heli;
};

int node::cnt_hurdle = 0;
static int cnt_score = 0;

class queuebuild
{
	public:
	node *head;
	node *frontq,*rearq;

	//constructor for queue
	queuebuild()
	{
		head = new node;
		head->up_down=DOWN;

		frontq = NULL;
		rearq = NULL;
	}

	void insert(node *insnode)
	{
		insnode->init_hurdle();

		node::cnt_hurdle += 1;

		if(frontq==NULL)
		{
			frontq=insnode;
			rearq=insnode;
			head->next=insnode;
		}

		else
		{
			rearq->next=insnode;
			rearq=rearq->next;
		}

		rearq->next=head;

	}

	void deleteee()
	{
		node *del;
		del=frontq;

		node::cnt_hurdle -= 1;
		cnt_score += 1;

		if(head->next!=NULL)
		{

			if(frontq->next==head)
			{
				rearq=NULL;
				frontq=NULL;
			}
			else
			{
				frontq=frontq->next;
			}
			head->next=frontq;
		}
		delete(del);
	}
};

class mouse
{
	protected:
	union REGS i,o;

	public:
	void initmouse()
	{
		i.x.ax = 0;
		int86(0x33,&i,&o);
	}
};

class heli:public mouse
{
	private:

	const int PLAY_SIDE,INCRE,HURDLE_INCRE;

	int cx,cy,tx,ty;  //for the ball only
	int arr[10];
	queuebuild hurdle;    //containment

	public:

	heli():PLAY_SIDE(10),INCRE(7),HURDLE_INCRE(4)
	{
		cx = 100;
		cy = 100;
	}

	void set_arr()  // need it inside to make it inline
	{
		arr[0] = tx;
		arr[1] = ty;

		arr[2] = tx+PLAY_SIDE;
		arr[3] = ty;

		arr[4] = tx+PLAY_SIDE;
		arr[5] = ty+PLAY_SIDE;

		arr[6] = tx;
		arr[7] = ty+PLAY_SIDE;

		arr[8] = tx;
		arr[9] = ty;
	}

	void start_play();
	//CHECK IF THE BALL HITS THE OBSTACLES
	int check_hurdle()
	{
		if(getpixel(arr[2],arr[3])==LIGHTBLUE)
			return 1;
		if(getpixel(arr[4],arr[5])==LIGHTBLUE)
			return 1;

		return 0;
	}

};

void game_intro();
void gameover();

int main()
{
	int gd = DETECT,gm;
	heli h1;

	initgraph(&gd,&gm,"c:\\tc\\bgi");
	randomize();

	start = clock();

	game_intro();

	delay(2000);
	cleardevice();

	setlinestyle(0,0,3);  // line of 3 pixel width

	h1.initmouse();
	h1.start_play();

	sound(780);
	delay(1000);
	nosound();

	cleardevice();
	gameover();

	closegraph();
	return 0;
}

void heli::start_play()
{
	int btn = -1,j,k=0;
	node *temp;

	tx = cx;
	ty = cy;

	while(1)
	{
		i.x.bx = -1;
		i.x.ax = 3;
		int86(0x33,&i,&o);

		btn = o.x.bx;

		if(btn==1 && cy>10)
		{
			ty = cy;
			set_arr();

			setcolor(BLACK);
			setfillstyle(SOLID_FILL,BLACK);

			drawpoly(5,arr);
			fillpoly(5,arr);

			cy -= INCRE;

			ty = cy;
			set_arr();

			setcolor(RED);
			setfillstyle(SOLID_FILL,LIGHTRED);

			drawpoly(5,arr);
			fillpoly(5,arr);

		}

		else if(cy<400)
		{

			ty = cy;
			set_arr();

			setcolor(BLACK);
			setfillstyle(SOLID_FILL,BLACK);
			drawpoly(5,arr);
			fillpoly(5,arr);

			cy += INCRE;

			ty = cy;
			set_arr();

			setcolor(RED);
			setfillstyle(SOLID_FILL,LIGHTRED);

			drawpoly(5,arr);
			fillpoly(5,arr);

		}

		temp = hurdle.frontq;

		for(j=0;j<node::cnt_hurdle;j++)  // can use while loop here too
		{
			setcolor(BLACK);
			drawpoly(SIZE,temp->loc);

			temp->ox -= HURDLE_INCRE;

			temp->reset_hurdle();

			setcolor(LIGHTBLUE);
			drawpoly(SIZE,temp->loc);

			temp = temp->next;
		}

		if(k%40==0)
		{
			temp = new node();
			hurdle.insert(temp);
		}

		if(hurdle.frontq->ox<=-(hurdle.frontq->HURDLE_WIDTH+50))
			hurdle.deleteee();
		k++;

		if(check_hurdle())
		{
			return;
		}
	}
}


//NOW THE BUILDINGS HAN

void node::reset_hurdle()
{

	if(up_down == UP)
	{
		loc[0] = loc[8] = ox;
		loc[1] = loc[9] = oy;

		loc[2] = ox + HURDLE_WIDTH;
		loc[3] = oy;

		loc[4] = ox + HURDLE_WIDTH;
		loc[5] = getmaxy();

		loc[6] = ox;
		loc[7] = getmaxy();

	}

	else
	{
		loc[0] = loc[8] = ox;
		loc[1] = loc[9] = oy;

		loc[2] = ox + HURDLE_WIDTH;
		loc[3] = oy;

		loc[4] = ox + HURDLE_WIDTH;
		loc[5] = 0;

		loc[6] = ox;
		loc[7] = 0;

	}


}

void node::init_hurdle()
{
	if(random(1000) % 2 == UP)
	{
		up_down = UP;

		do
		{
			oy = random(350);
		}while(oy<140);
	}
	else
	{
		up_down = DOWN;

		do
		{
			oy = random(240);
		}while(oy<70);
	}

	if(up_down == UP)
	{
		loc[0] = loc[8] = ox;
		loc[1] = loc[9] = oy;

		loc[2] = ox + HURDLE_WIDTH;
		loc[3] = oy;

		loc[4] = ox + HURDLE_WIDTH;
		loc[5] = getmaxy();

		loc[6] = ox;
		loc[7] = getmaxy();

	}

	else
	{
		loc[0] = loc[8] = ox;
		loc[1] = loc[9] = oy;

		loc[2] = ox + HURDLE_WIDTH;
		loc[3] = oy;

		loc[4] = ox + HURDLE_WIDTH;
		loc[5] = 0;

		loc[6] = ox;
		loc[7] = 0;

	}
}

/////////////////////////   DECORATION PART ////////////////////

void game_intro()
{
	fractal f1;

	f1.enter_disp_koch();

	setcolor(MAGENTA);
	delay(1000);
	cleardevice();

	f1.perform_koch();

	setcolor(LIGHTGREEN);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
	outtextxy(100,400,"HURDLES");

	setcolor(WHITE);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
	outtextxy(500,400,"ANIRUDH_TOMER");
	outtextxy(500,450,"GET_READY____");

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
/***************** KOCH CURVE STARTS HERE ***************/

//ENTER THE LINE FOR A KOCH CURVE

void fractal::enter_disp_koch()
{
	x1 = 100;
	y1 = 200;

	x2 = 500;
	y2 = 200;

	STOP = 7;

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

void gameover()
{
	end = clock();

	settextstyle(GOTHIC_FONT,HORIZ_DIR,7);
	setcolor(LIGHTRED);

	outtextxy(100,100,"GAME_OVER");

	cout<<"YOU CROSSED "<<cnt_score<<" HURDLE(S)";
	cout<<"\n\nYOU PLAYED FOR "<<(end-start)/CLK_TCK<<" SECONDS";

	getch();
}