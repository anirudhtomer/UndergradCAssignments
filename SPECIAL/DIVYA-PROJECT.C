//QUIZ MADE BY ANIRUDH TOMER FOR DIVYA TOMER & FRIENDS

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<dos.h>

int ret;
char name[20];

void correct()
{
	printf("\n\n\nYES YOUR ANSWER IS CORRECT");
	getch();
}

void ques(int);

int mcq(int);  //3 (1,2,8 )
int numerical(int);//2(7,10)
int fil_blnk(int); //3 (3,5,9)
int tr_fl(int); //2 (4,6)

int getkey();
int start();
int rules();

int check();

void main()
{

	int i,rul_ret,mnuret;
	char t_again[5];

	begin:
	clrscr();

	printf("    ********************************************************************\n\n");
	printf("\t  S C I E N C E\t\tP R O J E C T\t\tW O R K\n\n");
	printf("    ********************************************************************\n\n");
	delay(500);
	printf("\n\n\t\tKYA   AAP   AATHVIE   PASS   SE   TEJ   HAIN\n\t  ");
	for(i=0;i<56;i++)
	{
		delay(20);
		printf("#");
	}
	delay(2000);
	printf("\n\nREAD THE FOLLOWING BEFORE YOU START:-\n");
	for(i=0;i<38;i++)
	{
		delay(40);
		printf("~");
	}
	printf("\n\n");

	rul_ret=rules();

	if(rul_ret==1)
	  mnuret=start();

	else
		exit(0);

	getch();
	clrscr();
	printf("%s YOUR RESULT IS:-\t \"%d\" marks out of 10",name,mnuret);
	if(mnuret==10)
	{
		printf("\n\n\nCONGRATS YOU ARE REALLY EXCEPTIONAL STUDENT");
		delay(1000);
		printf("\n\n* * * * *");
		printf("\n\nFIVE STAR RATING FOR YOU");
	}
	delay(2000);
	printf("\n\n\n\nDO YOU WANT TO TEST YOUR SKILLS AGAIN(yes/no):-\t");
	flushall();
	gets(t_again);

	if(strcmp(t_again,"yes")==0)
		goto begin;
}

int start()
{
	int i,stret,cnt;
	clrscr();

	printf("PLEASE ENTER YOUR NAME:-\t");
	flushall();
	gets(name);

	for(i=1,cnt=0;i<=10;i++)
	{
		switch(i)
		{
		  case 1:  stret=mcq(1);
					break;
		  case 2:  stret=mcq(2);
					break;
		  case 3:  stret=fil_blnk(3);
					break;
		  case 4:  stret=tr_fl(4);
					break;
		  case 5:  stret=fil_blnk(5);
					break;
		  case 6:  stret=tr_fl(6);
					break;
		  case 7:  stret=numerical(7);
					break;
		  case 8:  stret=mcq(8);
					break;
		  case 9:  stret=fil_blnk(9);
					break;
		  case 10: stret=numerical(10);
		}
		if(stret==1)
			cnt++;
	}
	return cnt;
}

int tr_fl(int q_no)
{
	char tf,ter;

	if(q_no==4)
	{
		ques(4);
		printf("\n\nAll metals are ductile.(t/f)");
		printf("\n\nType \"t\" for TRUE\tor \"f\" for FALSE");

		ter=check();

		if(ter==14)
			goto end;

		flushall();
		printf("\n\nYOUR OPINION:-\t");
		scanf("%c",&tf);
		if(tf=='f')
		{
			correct();
			return 1;
		}
		else
			printf("\n\n\a\aIT IS A FALSE STATEMENT");
		getch();
	}
	if(q_no==6)
	{
		ques(6);
		printf("\n\nUnicellular organisms have one celled body.(t/f)");
		printf("\n\nType \"t\" for TRUE\tor \"f\" for FALSE");
		ter=check();

		if(ter==14)
			goto end;

		flushall();
		printf("\n\nYOUR OPINION:-\t");
		scanf("%c",&tf);
		if(tf=='t')
		{
			correct();
			return 1;
		}
		else
			printf("\n\n\a\aIT IS A TRUE STATEMENT");
		getch();
	}
	end:
	return 0;
}

int fil_blnk(int q_no)
{
	int i,ter;
	char flans[20];

	if(q_no==3)
	{
		ques(3);
		printf("\n\nanswer in small case letters");
		printf("\n\nHuman Voice box is also known as ______");
		for(i=0;i<6;i++)
				printf("\b");

		ter=check();

		if(ter==14)
			goto end;

		flushall();
		gets(flans);


		if(strcmp(flans,"larynx")==0)
		{
			correct();
			return 1;
		}
		else
			printf("\n\n\a\aThe Correct answer is \"LARYNX\"");
		getch();
	}

	if(q_no==5)
	{
		ques(5);
		printf("\n\nanswer in small case letters");

		printf("\n\n\"Ferrous\" is the scientific name of ____");
		for(i=0;i<4;i++)
				printf("\b");
		ter=check();

		if(ter==14)
			goto end;

		flushall();
		gets(flans);

		if(strcmp(flans,"iron")==0)
		{
			correct();
			return 1;
		}
		else
			printf("\n\n\a\aThe Correct answer is \"IRON\"");
			getch();
	}

	if(q_no==9)
	{
		ques(9);
		printf("\n\nanswer in small case letters");

		printf("\n\nThe Process of depositing a layer of metal on \n\t\tanother metal using electicity is called as _____________");
		for(i=0;i<13;i++)
				printf("\b");

		ter=check();

		if(ter==14)
			goto end;

		flushall();
		gets(flans);

		if(strcmp(flans,"electroplating")==0)
		{
			correct();
			return 1;
		}
		else
			printf("\n\n\a\aThe Correct answer is \"ELECTROPLATING\"");
			getch();
	}
	end:
	return 0;
}
int mcq(int q_no)
{
	int op,ter;
	clrscr();

	if(q_no==1)
	{
		ques(1);
		printf("\n\nAngle of Incidence = Angle of Reflection");
		printf("\n\n1. Always\n2. Sometimes\n3. Under Special conditions\n4. Never");
		printf("\n\nCHOOSE CORRECT ANSWER");

		ter=check();

		if(ter==14)
			goto end;

		printf("\n\nYOUR OPTION:-\t");
		scanf("%d",&op);

		if(op==1)
		{
			correct();
			return 1;
		}
		else
			printf("\n\n\a\aOPTION 1 is the correct answer");
			getch();

	}
	if(q_no==2)
	{
		ques(2);
		printf("\n\nKOH is the symbol of");
		printf("\n\n1. Sodium Hydroxide\n2. Phosphorous Dioxide \n3. Potassium Hydroxide\n4. Iron Oxide");
		printf("\n\nCHOOSE CORRECT ANSWER");

		ter=check();

		if(ter==14)
			goto end;

		printf("\n\nYOUR OPTION:-\t");
		scanf("%d",&op);

		if(op==3)
		{
			correct();
			return 1;
		}
		else
			printf("\n\n\a\aOPTION 3 is the correct answer");
			getch();

	}
	if(q_no==8)
	{
		ques(8);
		printf("\n\nWhite Blood Cells (WBC)");
		printf("\n\n1. Smaller In Size than RBC's\n2. More than RBC's\n3. Help In DIGESTION \n4. Provide IMMUNITY to the body");
		printf("\n\nCHOOSE CORRECT ANSWER");

		ter=check();

		if(ter==14)
			goto end;

		printf("\n\nYOUR OPTION:-\t");
		scanf("%d",&op);

		if(op==4)
		{
			correct();
			return 1;
		}
		else
			printf("\n\n\a\aOPTION 4 is the correct answer");
			getch();

	}
	end:
	return 0;
}
int numerical(int q_no)
{
	int ans_7,ans_10,ter;
	clrscr();

//****************QUESTION 7**********************

	if(q_no==7)
	{
	 ques(7);
	printf("\n\nA Student of class 8th carries a bag of weight 10N on his shoulders.\n\nThe Pressure exerted on his shoulders by the strips of the bag is 2.5N/cm%c\n\n",253);
	printf("Find CROSS SECTIONAL AREA OF THE STRIPS (in cm%c) ?",253);
	printf("\n\n\nHINT:-   The weight of bag is already given in terms of the force acting\n~~~~~~~~ on the shoulders.\n\n\"pressure is the force acting per unit area\"");

	ter=check();

		if(ter==14)
			goto end;

	printf("\n\n\nYOUR ANSWER:-\t");
	scanf("%d",&ans_7);

	if(ans_7==4)
	{
		correct();
		return 1;
	}
	else
		printf("\n\n\n\a\aTHE CORRECT ANSWER IS    4 cm%c.",253);
		getch();
	}
//*********QUESTION 10*******************

	if(q_no==10)
	{
	ques(10);
	printf("\n\nA Car starts from pune airport at 10:30 AM, travels at a speed of 10 m/s\n\nand reaches K.V-1 after travelleling 6 Km.");
	printf("\n\nAt WHAT TIME it reaches K.V-1 ?");
	printf("\n\n\nIMPORTANT NOTE:::::if your answer is 10:54 AM then type\"1054\"\n\t\tif your answer is 10:50 AM then type \"1050\"");
	printf("\n\nSO CALCULATE THE ANSWER & TYPE IT ACCORDINGLY");

	ter=check();

	if(ter==14)
		goto end;

	printf("\n\n\nYOUR ANSWER:-\t");
	scanf("%d",&ans_10);

	if(ans_10==1040)
	{
		correct();
		return 1;
	}
	else
		printf("\n\n\n\a\aTHE CORRECT ANSWER IS   10:40 AM");

	}
	end:
	return 0;
}
int rules()
{
	char chal[5];

	delay(1000);
	printf("<1>\tTEN QUSTIONS Will Be Asked In The Quiz.\n\n");
	delay(500);
	printf("<2>\tEach Question Carries 1 MARK.\n\n");
	delay(500);
	printf("<3>\tThere are:-");
	delay(500);
	printf("\tMCQ's, ");
	delay(500);
	printf("FILL IN THE BLANKS, ");
	delay(500);
	printf("TRUE-FALSE");
	delay(500);
	printf(" & NUMERICALS\".");
	delay(500);
	printf("\n\n<4>\tFor Answering MCQ's:-\n\n");
	delay(200);
	printf("\t Press The Number On The Keyboard Corrosponding To The OPTIONS PROVIDED.");
	delay(2000);
	printf("\n\n<5>\tFor Answering FILL IN THE BLANKS:-\n\n");
	delay(200);
	printf("\t Type The \"ONE WORD ANSWER\" In \"small case\" Letters Only.");
	delay(2000);
	printf("\n\n<6>\tFor Answering TRUE/FALSE:-\n\n");
	delay(200);
	printf("\t Type \"t\" OR \"f\" (in small case)." );
	delay(2000);
	printf("\n\n<7>\tFor Answering NUMERICALS:-\n\n");
	delay(200);
	printf("\t Type The Numerical Value Obtained As The Solution." );
	delay(2000);
	printf("\n\n<8>\tPress \"ENTER\" After Typing The Answer.");
	delay(1000);
	printf("\n\n<9>\tPress \"ESC\" To Exit From The Quiz.");
	delay(1000);
	printf("\n\n<10>\tPress \"BACKSPACE\" To Skip The Question. YOU WON'T GET MARKS FOR THAT.");
	delay(1000);
	printf("\n\n<11>\tYour SCORE Will Be Printed On The Screen At The End Of Quiz.");
	delay(5000);
	printf("\n\n\nSO ARE YOU READY TO GET YOUR SKILLS TESTED:-(yes/no)\t");
	flushall();
	gets(chal);
	if(strcmp("yes",chal)==0||strcmp("YES",chal)==0)
		return 1;
	else
		return 0;
}

int getkey()
{
	union REGS i,o;
	while(!kbhit())

	i.h.ah=0;
	int86 (22,&i,&o);
	return(o.h.ah);
}
int check()
{
	ret=getkey();

	if(ret==1)
		exit(1);

	return ret;
}

void ques(int num)
{
	int i;
	clrscr();
	printf("Press \"ENTER\" if you want to answer the question");
	printf("\n\nPress \"BACKSPACE\" if you want to skip the question");
	printf("\n\nPress \"ESC\" if you want to QUIT");
	printf("\n\n\n\n\t\t\tQ U E S T I O N	   %d\n\t\t   ",num);
	for(i=0;i<30;i++)
	{
		delay(20);
		printf("~");
	}
	printf("\n\t\t   ");
	for(i=0;i<30;i++)
	{
		delay(20);
		printf("~");
	}

}
