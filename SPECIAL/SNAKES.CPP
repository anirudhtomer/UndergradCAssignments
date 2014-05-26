

//last modification on 7th march 2009.....10:00 PM

//SNAKES ::: made by ANIRUDH TOMER aka MAVERICK
//DEDICATED TO MY DEAR FRIEND ANANYA WHOM I CONSIDER MY "logicacharya"

#include<iostream.h>
#include<fstream.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<time.h>

//SCAN CODES FOR ARROW KEYS
       
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define ESC 1
#define PAUSE 25

#define BLACKY 0
#define WHITES 1

//global variables
clock_t start, end;
int speedlevel=0;

class snake;
class queuebreak;

class node
{
	int bpx,bpy,mov;
	node *next;

	public:
	friend class queuebreak;
	friend class snake;
};


class queuebreak
{
	public:
	node *head;
	node *frontq,*rearq;

	//constructor for queue
	queuebreak()
	{
		head = new node;
		head->next=NULL;
		head->bpx= -200;
		head->bpy= -200;
		head->mov=RIGHT;   //one of the most imp factor

		frontq = NULL;
		rearq = NULL;
	}

	/*******inserting a breakpoint**************/

	void insert(node *insnode)
	{
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

	/****************deleting a breakpoint as soon as it is achieved*******/

	void deleteee()
	{
		int move;
		node *del;
		del=frontq;

		if(head->next!=NULL)
		{
			head->mov = frontq->mov;

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
		del->bpx=-200;
		del->bpy=-200;
		del->mov=0;
		delete(del);

	}
};


class snake
{
	int rear_x,rear_y,front_x,front_y;  //snake end & front

	int fx[9],fy[9];  //food coordinates

	int retkey; //return opcode for movement
	int score;

	queuebreak brake;

	public:
	snake()
	{
		score=0;

		rear_x = 100;
		rear_y = 100;

		front_x = 200;
		front_y = 100;

		retkey = RIGHT;
	}

	void startgame();

	/******CONTROL FUNCTIONS*******/

	void CONTROL_FRONT();  //controls the movement of snake
	void CONTROL_REAR();

	//MOVING THE FRONT OF THE SNAKE
	void fr_mov_right();
	void fr_mov_left();
	void fr_mov_down();
	void fr_mov_up();

	//MOVING THE REAR OF THE SNAKE
	void rr_mov_right();
	void rr_mov_left();
	void rr_mov_up();
	void rr_mov_down();

	//CHECKS IF THE REAR OF THE SNAKE HAS REACHED THE BREAK POINT
	int checkbrake();

	//returns 1 if snake gets the food else returns 0
	int checkfood();

	//increases the length of the snake (by 3 pixels) if it gets the food
	void inclen(int);

	//randomizes the food
	void food_prod();

	// DISPLAY SHOULD ALWAYS BE GOOD
	void logo();
	void gameover();
	void rules();

};

/*********PRINTING SNAKE ALONG X AXIS************/

inline void printx(int x,int y,int col)
{
	if(col==WHITES)
	{
		putpixel(x,y-1,WHITE);
		putpixel(x,y,WHITE);
		putpixel(x,y+1,WHITE);
	}

	else
	{
		putpixel(x,y-1,BLACK);
		putpixel(x,y,BLACK);
		putpixel(x,y+1,BLACK);
	}
}

/*************PRINTING SNAKE ALONG Y AXIS*************/

void printy(int x,int y,int col)
{
	if(col==WHITES)
	{
		putpixel(x-1,y,WHITE);
		putpixel(x,y,WHITE);
		putpixel(x+1,y,WHITE);
	}

	else
	{
		putpixel(x-1,y,BLACK);
		putpixel(x,y,BLACK);
		putpixel(x+1,y,BLACK);
	}
}


int getkey(); //returns scan code

//SET SPEED LEVEL (no prototype)
void setspeed()
{
	do
	{
		cout<<"\n\nENTER THE SPEED LEVEL (b/w 1 & 6):-\t";
		cin>>speedlevel;

	}while(speedlevel>6 ||speedlevel<1);
}


/********MAIN STARTS HERE**************/

int main(void)
{
	snake s;
	int gd=DETECT,gm;
	randomize();

	initgraph(&gd,&gm,"c:\\tc\\bgi");

	setlinestyle(0,0,3);   //setting a solid line with thickness 3 pixel

	//PRINTING LOGO

	s.logo();

	getch();

	s.rules();

	clrscr();
	cleardevice();
	setspeed();

	cleardevice();

	s.startgame();

	getch();
	closegraph();
	restorecrtmode();
	return 0;
}

void snake::startgame()
{
	int i;

	//MAKING BOUNDARIES

	setcolor(MAGENTA);

	//TOP BOUNDARY
	line(0,1,639,1);

	//BOTTOM BOUNDARY
	line(0,478,639,478);

	//LEFT BOUNDARY
	line(1,0,1,479);

	//RIGHT BOUNDARY
	line(638,0,638,479);

	//GAME STARTS HERE
	setcolor(WHITE);

	line(rear_x,rear_y,front_x,front_y);  //initial length of snake = 100 pixels

	while(1)
	{
	   food_prod();

	   if(fx[4]>30 && fy[4]>30)
		break;
	   for(i=0;i<9;i++)
		putpixel(fx[i],fy[i],BLACK);
	}


	start = clock();

	CONTROL_FRONT();

}

/**********CONTROLLING THE FRONT OF THE SNAKE**********/

void snake::CONTROL_FRONT()
{
	int i;
	node *temp;


	for(retkey=RIGHT;1;)
	{
		switch(retkey)
		{
			case RIGHT: fr_mov_right();
					break;

			case LEFT : fr_mov_left();
					break;

			case UP   : fr_mov_up();
					break;

			case DOWN : fr_mov_down();
					break;

			case ESC:   gameover();

			default :   exit(1);
		}

		temp = new node;

		temp->bpx = front_x;
		temp->bpy = front_y;
		temp->mov = retkey;

		brake.insert(temp);  //insert the breakpoint

	}
}

/***************CONTROLLING THE REAR OF THE SNAKE*************/
void snake::CONTROL_REAR()
{
	int r_factor;

	if(checkbrake())
	{
		brake.deleteee();
		r_factor = brake.head->mov;

		if(r_factor==LEFT||r_factor==RIGHT)
			printy(rear_x,rear_y,BLACK);
		else
			printx(rear_x,rear_y,BLACK);
	}

	else     //whenever the queue is empty (snake moving straight)
		r_factor = brake.head->mov;

	switch(r_factor)
	{
		case UP: rr_mov_up();
			   break;

		case DOWN: rr_mov_down();
				 break;

		case LEFT: rr_mov_left();
			     break;

		case RIGHT: rr_mov_right();
				break;

		default: exit(3);
	}

}

/**********MOVEMENT FRONT ALONG +ve X-AXIS***************/

void snake::fr_mov_right()
{

	for(front_x++;;front_x++)
	{
		CONTROL_REAR();
		printx(front_x,front_y,WHITES);

		if(abs(front_x-fx[4])<5)
			if(checkfood())
				inclen(RIGHT);

		if(front_x==637 || WHITE == getpixel(front_x+1,front_y))
			gameover();


		retkey = getkey();

		if(retkey==PAUSE)
			getch();

		if(retkey==UP || retkey ==DOWN || retkey == ESC)
			break;
	}
}

/**********MOVEMENT FRONT ALONG -ve X-AXIS***************/

void snake::fr_mov_left()
{

	for(front_x--;;front_x--)
	{
		CONTROL_REAR();
		printx(front_x,front_y,WHITES);

		if(abs(front_x-fx[4])<5)
			if(checkfood())
				inclen(LEFT);

		if(front_x==3 || WHITE == getpixel(front_x-1,front_y))
			gameover();

		retkey = getkey();

		if(retkey==PAUSE)
			getch();

		if(retkey==UP || retkey ==DOWN || retkey == ESC)
			break;
	}


}

/*********MOVING FRONT ALONG +ve Y-AXIS***********************/

void snake::fr_mov_up()
{

	for(front_y--;;front_y--)
	{
		CONTROL_REAR();
		printy(front_x,front_y,WHITES);

		if(abs(front_y-fy[4])<5)
			if(checkfood())
				inclen(UP);

		if(front_y==3 || WHITE == getpixel(front_x,front_y-1))
			gameover();

		retkey = getkey();

		if(retkey==PAUSE)
			getch();

		if(retkey==LEFT || retkey ==RIGHT || retkey == ESC)
			break;
	}

}

/*********MOVING FRONT ALONG -ve Y-AXIS***********************/
void snake::fr_mov_down()
{
	for(front_y++;;front_y++)
	{
		CONTROL_REAR();
		printy(front_x,front_y,WHITES);

		if(abs(front_y-fy[4])<5)
			if(checkfood())
				inclen(DOWN);


		if(front_y==477 || WHITE == getpixel(front_x,front_y+1))
			gameover();

		retkey = getkey();

		if(retkey==PAUSE)
			getch();

		if(retkey==LEFT || retkey ==RIGHT || retkey == ESC)
			break;
	}
}

/**********MOVING REAR ALONG +ve X AXIS*****************/

void snake::rr_mov_right()
{
	printx(rear_x,rear_y,BLACKY);
	rear_x++;
}

/**********MOVING REAR ALONG -ve X AXIS*****************/

void snake::rr_mov_left()
{
	printx(rear_x,rear_y,BLACKY);
	rear_x--;
}

/**********MOVING REAR ALONG +ve Y AXIS*****************/

void snake::rr_mov_up()
{
	printy(rear_x,rear_y,BLACKY);
	rear_y--;
}

/**********MOVING REAR ALONG -ve Y AXIS*****************/

void snake::rr_mov_down()
{
	printy(rear_x,rear_y,BLACKY);
	rear_y++;
}


/*********FUNCTION TO PRODUCE FOOD ON SCREEN************/

void snake::food_prod()
{
	int i;

	fx[4] = rand() % 570;
	fy[4] = rand() % 450;

	//row 1 pixels
	putpixel(fx[0]=fx[4]-1,fy[0]=fy[4]-1,YELLOW);
	putpixel(fx[1]=fx[4],fy[1]=fy[4]-1,YELLOW);
	putpixel(fx[2]=fx[4]+1,fy[2]=fy[4]-1,YELLOW);

	//row 2 pixels
	putpixel(fx[3]=fx[4]-1,fy[3]=fy[4],YELLOW);
	putpixel(fx[4],fy[4],YELLOW);
	putpixel(fx[5]=fx[4]+1,fy[5]=fy[4],YELLOW);

	//row 3 pixels
	putpixel(fx[6]=fx[4]-1,fy[6]=fy[4]+1,YELLOW);
	putpixel(fx[7]=fx[4],fy[7]=fy[4]+1,YELLOW);
	putpixel(fx[8]=fx[4]+1,fy[8]=fy[4]+1,YELLOW);

}



/**************FUNCTION TO RETURN SCAN CODE***************/

int getkey()
{
	union REGS i,o;
	int x;

	switch(speedlevel)
	{
		case 1:delay(25);
			   break;

		case 2:delay(20);
			   break;

		case 3:delay(15);
			   break;

		case 4:delay(5);
			   break;

		case 5:delay(3);
			   break;

		case 6:delay(1);
			   break;

	}


	i.h.ah=0;
	x=kbhit();

	if(x!=0)
	{
		int86(22,&i,&o);
		return (o.h.ah);
	}
	return 0;
}

//CHECKING IF REAR HAS ACHIEVED BRAKING POINT

int snake::checkbrake()
{
	if(brake.frontq!=NULL)
	{
		if(rear_x==brake.frontq->bpx && rear_y==brake.frontq->bpy)
			return 1;
	}
		return 0;
}

//CHECKING IF SNAKE HAS GOT THE FOOD

int snake::checkfood()
{
	int i;

	for(i=0;i<9;i++)
	{
		if( (front_x==fx[i]||front_x-1==fx[i]||front_x+1==fx[i]) && (front_y==fy[i]||front_y-1==fy[i]||front_y+1==fy[i]))
		{
			i=-1;
			break;
		}
	}

	if(i==-1)
		return 1;
	return 0;

}

//increments the length of the snake when food is achieved
void snake::inclen(int movcor)
{
	int i;

	for(i=0;i<9;i++)
	{
		putpixel(fx[i],fy[i],BLACK);
	}

	//produces a sound when food is eaten
	sound(780);
	delay(20);
	nosound();

	//increases score by 7 points
	score+=10;

	switch(movcor)
	{
		case RIGHT: printx(++front_x,front_y,WHITES);
					printx(++front_x,front_y,WHITES);
					printx(++front_x,front_y,WHITES);
					printx(++front_x,front_y,WHITES);

				break;

		case LEFT : printx(--front_x,front_y,WHITES);
					printx(--front_x,front_y,WHITES);
					printx(--front_x,front_y,WHITES);
					printx(--front_x,front_y,WHITES);

				break;

		case UP   : printy(front_x,--front_y,WHITES);
					printy(front_x,--front_y,WHITES);
					printy(front_x,--front_y,WHITES);
					printy(front_x,--front_y,WHITES);

				break;

		case DOWN : printy(front_x,++front_y,WHITES);
					printy(front_x,++front_y,WHITES);
					printy(front_x,++front_y,WHITES);
					printy(front_x,++front_y,WHITES);

				break;


	}

	while(1)
	{
	   food_prod();

	   if(fx[4]>30 && fy[4]>30)
		break;
	   for(i=0;i<9;i++)
		putpixel(fx[i],fy[i],BLACK);
	}
}

//PRINTING LOGO OF THE GAME
void snake::logo()
{
	int i,j;


	for(i=0;i<100;i=i+10)
	{
		cleardevice();
		setcolor(random(5));
		settextstyle(7,0,random(10));
		outtextxy(i,100,"SNAKES");


		for(j=0;j<15;j++)
		{
			setcolor(random(15));
			circle(random(600),random(400),20);
		}

		delay(100);
	}

	cout<<"\n\n\n\nPRESS ANY KEY TO CONTINUE";
}

//PRINTING GAME OVER & SHOWING SCORE
void snake::gameover()
{
	end = clock();

	int i,j;

	cout<<"\a";

	for(i=0;i<100;i=i+10)
	{
		cleardevice();
		setcolor(random(5));
		settextstyle(7,0,random(10));
		outtextxy(i,100,"GAME OVER");


		for(j=0;j<15;j++)
		{
			setcolor(random(15));
			circle(random(600),random(400),20);
		}

		delay(100);
	}
	clrscr();
	cleardevice();

	cout<<"\n\n\n\tYOUR SCORE IS::\t"<<score;

	cout<<"\n\n\n\t\tYOU PLAYED FOR::\t"<<(end - start) / CLK_TCK<<"\tSECONDS";
	cout<<"\n\n\n\nPRESS ANY KEY TO EXIT";
	getch();

	closegraph();
	restorecrtmode();


	exit(2);
}

//PRINTING RULES

void snake::rules()
{
	int i,j,k,m,n;

	for(i=0;i<13;i++)
	{
		 j=i*3;
		 for(k=0;k<j;k++)
		 {
			cout<<" ";
		 }

		 cout<<"ANIRUDH  ";

		 m=71-i*6;
		 for(n=m;n>=0;n--)
		 {
				cout<<" ";
		 }
		 cout<<"TOMER";

		 delay(100);

		 if(i!=12)
		 {
			 clrscr();
			 cleardevice();
		 }

	}


	cout<<"\n\n\t\t******************* R U L E S ******************";

	cout<<"\n\n 1. USE ARROW KEYS TO MOVE SNAKE";
	cout<<"\n\n 2. ON EATING FOOD, LENGTH OF SNAKE INCREASES.";
	cout<<"\n\n 3. YOUR SCORE INCREASES BY \"10 points\" AFTER SNAKE EATS FOOD.";
	cout<<"\n\n 4. IF YOU HIT THE WALLS OR YOURSELF THE GAME WILL BE OVER.";
	cout<<"\n\n 5. IF YOU WANNA EXIT WHILE PLAYING PRESS \"Esc\".";
	cout<<"\n\n 6. PRESS \"P\" TO \"PAUSE\" WHILE PLAYING THE GAME.";
	cout<<"\n\n 7. YOU CAN CHOOSE SPEED LEVEL B/W 1 (slowest) & 6(speedfreak level).";


	cout<<"\n\n\nPRESS ANY KEY TO CARRY ON";
	getch();

	cout<<"\n\n\n\n\nI DEDICATE THIS GAME TO MY FRIEND \"ANANYA ANURAG\"";
	cout<<" \n\nWHO IS A MASTERMIND IN PROGRAMMING.";
	cout<<"\n\nthough he is low at E.Q BUT,PROBABLY HE HAS GOT THE BEST I.Q. IN BOTH DIVISIONS.";
	cout<<"\n\nI HAVE MADE THIS GAME WITHOUT ANYBODY's HELP (not any books nor internet...)\n\n\tit's completely mine!";
	cout<<"\n\nMY FAMILY ,ANANYA(***) ,SANKET & KHALI, I THANK THEM ALL FOR SUPPROTING ME.";
	cout<<"\n\n\nTHANKS ANANYA, & KEEP APPRECIATING MY LOGIC & IDEAS AS YOU ALWAYS DO.";

	cout<<"\n\n\nPRESS ANY KEY TO CARRY ON";
	getch();

	clrscr();
	cleardevice();

	cout<<"\n\n\n\nIF U HAVE GOT A BETTER ALGORITHM OR IF U FIND ANY BUGS ";
	cout<<"\n\nCALL ME AT 9850336509 OR MEET ME IN LECTURE ROOM FOR SE COMP-I AT MIT.";
	cout<<"\n\nI WON'T BORE U MUCH....SO ENJOY SNAKES BY \"Anirudh Tomer\"";

	cout<<"\n\n\nPRESS ANY KEY (last time) TO PLAY";
	getch();
}
