//ANIRUDH TOMER...SE COMP-I....42028
//subject:- computer graphics
//last date updated....23 aug 2008

//PROGRAM TO DO FLAG HOISTING

#include<graphics.h>
#include<dos.h>
#include<conio.h>
#include<stdio.h>

int getkey();
void tune();

void main()
{
	int gd=DETECT,gm,up,down,i,j,var,prev,r,w,g,hoist;

	initgraph(&gd,&gm,"c:\\tc\\bgi");

	while(1)
	{

	clrscr();
	cleardevice();

	up=16;
	down=394;

	printf("1.HOIST FLAG\n\n2.BRING FLAG DOWN\n\nPRESS \"Esc\" TO EXIT");
	printf("\n\nENTER CHOICE:-\t");
	hoist=getkey();

	switch(hoist)
	{

	     case 2:
		//ANIMATED FLAG HOISTING
		var=down;
		g=var;
		w=var-30;
		r=var-60;
		while(var>up+90)
		{
			cleardevice();
			//FLAG STAND
			setlinestyle(0,0,3);
			setcolor(BLUE);
			line(191,10,191,420);
			line(194,10,194,420);
			setcolor(BROWN);
			circle(194,7,3);

			//FLAG STAND BASE
			setfillstyle(1,BLUE);
			bar(155,420,230,440);

			//STRING ON FLAG
			setlinestyle(0,0,1);
			setcolor(WHITE);
			line(194,7,199,16);
			line(199,16,199,394);
			line(199,394,194,397);

			setfillstyle(1,GREEN);
			bar(200,w,380,g);

			setfillstyle(1,WHITE);
			bar(200,r,380,w);

			//24 TAS
			setcolor(BLUE);
			for(j=0,prev=0;j<24;j++,prev+=15)
				pieslice(290,(r+w)/2,prev,prev+15,15);

			setfillstyle(1,RED);
			bar(200,r-30,380,r);

			var-=20;
			g=var;
			w=var-30;
			r=var-60;

			delay(60);

		}
		printf("JAI HIND");
			tune();
		break;

	     case 3:
		var=up+18;
		r=var;
		w=var+30;
		g=var+60;
		while(var<down-90)
		{
			cleardevice();
			//FLAG STAND
			setlinestyle(0,0,3);
			setcolor(BLUE);
			line(191,10,191,420);
			line(194,10,194,420);
			setcolor(BROWN);
			circle(194,7,3);

			//FLAG STAND BASE
			setfillstyle(1,BLUE);
			bar(155,420,230,440);

			//STRING ON FLAG
			setlinestyle(0,0,1);
			setcolor(WHITE);
			line(194,7,199,16);
			line(199,16,199,394);
			line(199,394,194,397);


			setfillstyle(1,RED);
			bar(200,r,380,w);


			setfillstyle(1,WHITE);
			bar(200,w,380,g);

			//24 TAS
			setcolor(BLUE);
			for(j=0,prev=0;j<24;j++,prev+=15)
				pieslice(290,(g+w)/2,prev,prev+15,15);

			setfillstyle(1,GREEN);
			bar(200,g,380,g+30);

			var+=10;
			r=var;
			w=var+30;
			g=var+60;

			delay(50);


		}
		break;

	     case 1: goto end;

	     default: printf("\a\aENTER PROPER CHOICE");
	}
	setcolor(WHITE);
	outtextxy(0,0,"PRESS ANY KEY TO GO BACK");
	getch();
	}

	end:
	closegraph();
	restorecrtmode();

}

int getkey()
{
	union REGS i,o;
	while(!kbhit())

	i.h.ah=0;
	int86 (22,&i,&o);
	return(o.h.ah);
}

void tune()
{
float A,Bb,D,G,F;
A = 440;
G = 780;
Bb = 461;
D = 586;
F = 687;
sound(G);
delay(500);
nosound();
sound(G);
delay(250);
nosound();
sound(G);
delay(250);
nosound();
sound(G);
delay(500);
nosound();
sound(2*D);
delay(500);
nosound();
sound(2*A);
delay(250);
nosound();
sound(2*Bb);
delay(250);
nosound();
sound(2*A);
delay(250);
nosound();
sound(G);
delay(250);
nosound();
sound(F);
delay(500);
nosound();
sound(2*A);
delay(500);
nosound();
sound(G);
delay(250);
nosound();
sound(2*A);
delay(250);
nosound();
sound(G);
delay(250);
nosound();
sound(F);
delay(250);
sound(G);
delay(250);
sound(2*A);
delay(250);
sound(2*Bb);
delay(500);
sound(2*A);
delay(500);
sound(G);
delay(250);
sound(F);
delay(250);
sound(D);
delay(500);
nosound();
}