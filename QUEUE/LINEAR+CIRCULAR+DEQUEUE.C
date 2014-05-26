#include<stdio.h>
#include<conio.h>
#include<process.h>
#define MAX 10

typedef struct queue
{
	int front,rear;
	int data[MAX];
}Q;

void initq(Q *);
void displq(Q *,int,int);


void linq();
void addlq(Q *);
void dellq(Q *);
void displq(Q *,int,int);

void circq();
void addcq(Q *);
void delcq(Q *);
void dispcq(Q *,int,int);

void deq();
void adddql(Q *);
void adddqr(Q *);
void deldql(Q *);
void deldqr(Q *);
void dispdq(Q *,int,int);

void main()
{
	int chmnu;

	while(1)
	{
		clrscr();
		printf("\t\t\t\tQ U E U E S\n");
		printf("\n\t1.LINEAR QUEQUE\n\t2.CIRCULAR QUEUE\n\t3.DE-QUEUE\n\n\t4.E X I T");
		printf("\n\nENTER YOUR CHOICE:-\t");
		scanf("%d",&chmnu);
		switch(chmnu)
		{
			case 1: linq();
				break;

			case 2: circq();
				break;

			case 3: deq();
				break;

			case 4: exit(0);

			default: printf("\nEnter proper choice");
		}
		getch();
	}

}
//***************FUNCTION TO INITIALIZE QUEUE***************

void initq(Q *l_c_d_q)
{
	l_c_d_q->front=-1;
	l_c_d_q->rear=-1;
}


//*****************DE QUEUE STARTS HERE*****************


void deq()
{
	int chdq;
	Q dq;

	initq(&dq);

	while(1)
	{
		clrscr();
		printf("FRONT = %d\t\tREAR = %d",dq.front,dq.rear);
		printf("\n\n\t\tC I R C U L A R    Q U E U E\n");
		printf("\n\t1.ADD ELEMENT FROM LEFT\n\t2.ADD ELEMENT FROM RIGHT\n\t");
		printf("3.DELETE ELEMENT FROM LEFT\n\t4.DELETE ELEMENT FROM RIGHT\n\t");
		printf("5.DISPLAY ELEMENTS\n\n\t");
		printf("6.RETURN TO MAIN MENU\n\nEnter your choice:-\t");
		scanf("%d",&chdq);
		switch(chdq)
		{
			case 1: adddql(&dq);
				break;

			case 2: adddqr(&dq);
				break;

			case 3: deldql(&dq);
				break;

			case 4: deldqr(&dq);
				break;

			case 5: displq(&dq,dq.front,dq.rear);
				break;

			case 6: goto enddq;

			default: printf("\n\nEnter proper choice");
		}
		getch();
	}
	enddq:
}

void adddql(Q *dq)
{
	int ele,i;

	if(dq->front==0 && dq->rear==MAX-1)
		printf("\n\nQUEUE IS FULL");
	else
	{
		printf("\n\nEnter element to be added:-\t");
		scanf("%d",&ele);

		if(dq->front==-1)
			dq->front=dq->rear=0;
		else
		{

			if(dq->rear!=MAX-1)
			{
				for(i=(dq->rear+1);i>dq->front;i--)
					dq->data[i]=dq->data[i-1];

				dq->rear++;
			}
			else
				dq->front--;
		}
		dq->data[dq->front]=ele;
		printf("\n\nELEMENT ADDED FROM LEFT");

	}

}
void adddqr(Q *dq)
{
	int ele,i;

	if(dq->front==0 && dq->rear==MAX-1)
		printf("\n\nQUEUE IS FULL");
	else
	{
		printf("\n\nEnter element to be added:-\t");
		scanf("%d",&ele);

		if(dq->front==-1)
			dq->front=dq->rear=0;
		else
		{

			if(dq->front!=0)
			{
				for(i=(dq->front-1);i<dq->rear;i++)
					dq->data[i]=dq->data[i+1];

				dq->front--;
			}
			else
				dq->rear++;
		}
		dq->data[dq->rear]=ele;
		printf("\n\nELEMENT ADDED FROM RIGHT");

	}

}
void deldql(Q *dq)
{
	int ele,i;

	if(dq->front==-1)
		printf("\n\nQUEUE IS ALREADY EMPTY");

	else
	{
		if(dq->front>dq->rear)
		{
			initq(dq);
			printf("\n\nQUEUE IS INITIALIZED");
		}

		else
		{
			dq->front++;
			printf("ELEMENT \"%d\"   DELETED FROM LEFT",dq->data[dq->front-1]);
		}
	}

}
void deldqr(Q *dq)
{
	int ele,i;

	if(dq->front==-1)
		printf("\n\nQUEUE IS ALREADY EMPTY");

	else
	{
		if(dq->front>dq->rear)
		{
			initq(dq);
			printf("\n\nQUEUE IS INITIALIZED");
		}

		else
		{
			dq->rear--;
			printf("ELEMENT \"%d\"   DELETED FROM RIGHT",dq->data[dq->rear+1]);
		}
	}

}

//*****************CIRCULAR QUEUE STARTS HERE*****************


void circq()
{
	int chcq;
	Q cq;

	initq(&cq);

	while(1)
	{
		clrscr();
		printf("FRONT = %d\t\tREAR = %d",cq.front,cq.rear);

		printf("\n\n\t\tC I R C U L A R    Q U E U E\n");
		printf("\n\t1.ADD ELEMENT\n\t2.DELETE ELEMENT\n\t3.DISPLAY ELEMENTS\n\n\t");
		printf("4.RETURN TO MAIN MENU\n\nEnter your choice:-\t");
		scanf("%d",&chcq);
		switch(chcq)
		{
			case 1: addcq(&cq);
				break;

			case 2: delcq(&cq);
				break;

			case 3: dispcq(&cq,cq.front,cq.rear);
				break;

			case 4: goto endcq;

			default: printf("\n\nEnter proper choice");
		}
		getch();
	}
	endcq:
}

void addcq(Q *cq)
{
	int ele;

	if( (cq->rear+1)%MAX == cq->front)
		printf("\n\nQUEUE IS FULL");

	else
	{
		printf("\n\nENTER ELEMENT TO BE ADDED:-\t");
		scanf("%d",&ele);

		if(cq->front==-1)
			cq->front=cq->rear=0;

		else
			cq->rear=(cq->rear +1)%MAX;

		cq->data[cq->rear]=ele;
		printf("\n\nELEMENT IS ADDED");

	}


}

void delcq(Q *cq)
{
	if(cq->front==-1)
		printf("\n\nQUEUE IS ALREADY EMPTY");

	else
	{
		if( (cq->rear+1)%MAX ==cq->front)
		{
			initq(cq);
			printf("\n\nLINEAR QUEUE IS INITIALIZED");
		}
		else
		{
			cq->front=(cq->front+1)%MAX;
			printf("\n\nELEMENT \"%d\" IS DELETED",cq->data[cq->front -1]);
		}
	}
}
void dispcq(Q *cq,int f,int r)
{
	int i;

	if(f==-1)
		printf("\n\nQUEUE IS EMPTY");

	else
	{
		printf("\n\nTHE ELEMENTS IN QUEUE ARE:-\n\n");

		for(i=f;i!=r;i=(i+1)%MAX)
			printf("%d\t",cq->data[i]);
	}
	printf("%d",cq->data[i]);

}

//*********************LINEAR QUEUE STARTS HERE*********************
void linq()
{
	int chlq;
	Q lq;

	initq(&lq);

	while(1)
	{
		clrscr();
		printf("FRONT = %d\t\tREAR = %d",lq.front,lq.rear);

		printf("\n\n\t\tL I N E A R    Q U E U E\n");
		printf("\n\t1.ADD ELEMENT\n\t2.DELETE ELEMENT\n\t3.DISPLAY ELEMENTS\n\n\t");
		printf("4.RETURN TO MAIN MENU\n\nEnter your choice:-\t");
		scanf("%d",&chlq);
		switch(chlq)
		{
			case 1: addlq(&lq);
				break;

			case 2: dellq(&lq);
				break;

			case 3: displq(&lq,lq.front,lq.rear);
				break;

			case 4: goto endlq;

			default: printf("\n\nEnter proper choice");
		}
		getch();
	}
	endlq:
}

void addlq(Q *lq)
{
	int ele;

	if(lq->rear==MAX-1)
		printf("\n\nQUEUE IS FULL");

	else
	{
		printf("\n\nENTER ELEMENT TO BE ADDED:-\t");
		scanf("%d",&ele);

		if(lq->front==-1)
			lq->front=lq->rear=0;

		else
			lq->rear++;

		lq->data[lq->rear]=ele;
		printf("\n\nELEMENT IS ADDED");

	}

}

void dellq(Q *lq)
{
	if(lq->front==-1||lq->front>lq->rear)
		printf("\n\nQUEUE IS ALREADY EMPTY");

	else
	{
		if(lq->rear==MAX-1)
		{
			initq(lq);
			printf("\n\nLINEAR QUEUE IS INITIALIZED");
		}
		else
		{
			lq->front++;
			printf("\n\nELEMENT \"%d\" IS DELETED",lq->data[lq->front -1]);
		}
	}
}
void displq(Q *lq,int f,int r)
{
	int i;

	if(f==-1)
		printf("\n\nQUEUE IS EMPTY");

	else
	{
		printf("\n\nTHE ELEMENTS IN QUEUE ARE:-\n\n");

		for(i=f;i<=r;i++)
			printf("%d\t",lq->data[i]);
	}
}
