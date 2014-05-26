//PROGRAM TO IMPLEMENT A LINK LIST DYNAMICALLY
//DEDICATED TO MY BEST FRIEND : AASHISH AGARWAL aka DALLA


#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<alloc.h>
#include<dos.h>
#define MAX 20


typedef struct node
{
	char name[MAX];
	struct node *next;
}ll;

typedef struct first
{
	int numin,numout;
	char namefst[20];
	struct node *next;
	struct first *nxtfst;
}fst;

typedef struct mother
{
	int numll;
	struct first* fstll,*lastll;
}god;

//CREATES MOTHER LINK LIST GLOBALLY
god *linklist;

//LIST OF FUNCTION PROTOTYPES FOR INTERNAL STRUCTURE OF THE PROGRAM
fst* displayint(fst*);
fst* add(fst*);
fst* del(fst*);
fst* edit(fst*);
fst* reverse(fst*);
fst* sort(fst*);

//LIST OF FUNCTION PROTOTYPES FOR EXTERNAL STRUCTURE OF THE PROGRAM
fst* create();
fst* choose();
void llmnu(fst*);
void concatinate();
void displayext();
void delext();
void sortext();
void reverseext();
void freeson(fst*);

//SPECIAL FUNCTIONS
int getkey();
void tomer(int);

//main starts here
void main(void)
{
	int chmnu,cntmain=0;
	fst * xfst;

	linklist->numll=0;
	linklist->fstll=NULL;
	linklist->lastll=NULL;


	while(1)
	{
		clrscr();
		cntmain++;
		chmnu=0;
		printf("\t\t\t   L I N K\t    L I S T\n\n");
		printf("\t\t    PRESS \"BACKSPACE\"TO KNOW ABOUT PROGRAMMER\n");
		printf("\t\t*************************************************");
		printf("\n\n\n1.CREATE NEW LINK LIST\n\n2.DELETE LINK LIST\n\n3.DISPLAY MOTHER LINK LIST");
		printf("\n\n4.CHOOSE A LIST TO WORK UPON\n\n5.SORT LINK LISTS IN ALPAHBETICAL ORDER");
		printf("\n\n6.REVERSE LIST OF LINK LISTS\n\n7.CONCATINATE DATA OF TWO LINK LISTS\n\n\nTO EXIT PRESS \"Esc\"");
		printf("\n\n\nEnter Your Choice:-\t");
		chmnu=getkey();

		switch(chmnu)
		{

			case 2: xfst=create();
				if(xfst==NULL)
					goto endmain;
				llmnu(xfst);
				break;

			case 3: if(linklist->numll==0)
					printf("\n\n\nTHE MOTHER LINK LIST IS EMPTY");
				else
					delext();
				break;

			case 4: if(linklist->numll==0)
					printf("\n\n\nTHE MOTHER LINK LIST IS EMPTY");
				else
					displayext();
				break;

			case 5: if(linklist->numll==0)
					printf("\n\n\nTHE MOTHER LINK LIST IS EMPTY");
				else
				{
					xfst=choose();
					llmnu(xfst);
				}
				break;

			case 6: if(linklist->numll==0)
					printf("\n\n\nTHE MOTHER LINK LIST IS EMPTY");
				else
					sortext();
				break;
			case 7: if(linklist->numll==0)
					printf("\n\n\nTHE MOTHER LINK LIST IS EMPTY");
				else
					reverseext();
				break;

			case 8: if(linklist->numll<2)
					printf("\n\n\nYOU NEED ATLEAST TWO LINK LISTS TO PERFORM CONCATINATION");
				else
					concatinate();
				break;

			case 14: tomer(cntmain);
				 break;

			case 1: goto endmain;
			default: printf("\n\n\n\aERROR !!!  FALSE INPUT ENCOUNTERED");
		}

		getch();
	}
	endmain:

}


//******************MENU FOR INT- OPERATIONS ON LINK LIST *********
void llmnu(fst *xfst)
{
	int chfst;
	fst* llmnuret;

	llmnuret=xfst;

	while(1)
	{
		clrscr();
		chfst=0;
		printf("\t\t\t%d. %s\n\n",xfst->numout,xfst->namefst);

		printf("\t\t*************************");
		printf("\n\n1.ADD DATA\n\n2.DELETE DATA\n\n3.DISPLAY DATA");
		printf("\n\n4.EDIT DATA\n\n5.REVERSE DATA\n\n6.SORT DATA\n\nPRESS \"Esc\" TO EXIT TO MAIN MENU");
		printf("\n\n\nEnter Your Choice:-\t");
		chfst=getkey();

		switch(chfst)
		{
			case 2: llmnuret=add(llmnuret);
				break;

			case 3: if(llmnuret->numin==0)
					printf("\n\n\nTHE LINK LIST IS EMPTY");
				else
					llmnuret=del(llmnuret);
				break;

			case 4: llmnuret=displayint(llmnuret);
				break;

			case 5: if(llmnuret->numin==0)
					printf("\n\n\nTHE LINK LIST IS EMPTY");
				else
					llmnuret=edit(llmnuret);
				break;

			case 6: if(llmnuret->numin==0)
					printf("\n\n\nTHE LINK LIST IS EMPTY");
				else
					llmnuret=reverse(llmnuret);
				break;

			case 7: if(llmnuret->numin==0)
					printf("\n\n\nTHE LINK LIST IS EMPTY");
				else
				       llmnuret=sort(llmnuret);
				break;

			case 1: goto endllmnu;
			default: printf("\n\n\n\aERROR !!!  FALSE INPUT ENCOUNTERED");
		}

		getch();
	}
	endllmnu:
	printf("\n\nPRESS ANY KEY NOW");

}

//********************CONCATINATE TWO LINK LISTS**************
void concatinate()
{
	int i,datanum1,datanum2;
	fst *temp,*node1,*node2,*node2before,*node2after,*cngnode;
	ll* endnode;

	startcon:
	clrscr();
	displayext();

	printf("\n\nENTER THE NUMBERS OF THE TWO LISTS WHICH YOU WANT TO CONCATINATE:-\t");
	scanf("%d%d",&datanum1,&datanum2);

	if( (datanum1<1 || datanum1>linklist->numll) || (datanum2<1 || datanum2>linklist->numll) || (datanum1==datanum2) )
	{
		printf("\n\n\aERROR!!! IMPROPER INPUTS ENCOUNTERED");
		printf("\n\n\nPRESS ANY KEY TO CONTINUE");
		getch();

		goto startcon;
	}

	//POINTER ASSIGNMENTS FOR NODE 1

	temp=linklist->fstll;

	for(i=0;i<datanum1-1;i++)
		temp=temp->nxtfst;
	node1=temp;

	//POINTER ASSIGNMENTS FOR NODE 2

	temp=linklist->fstll;

	for(i=0;i<datanum2-1;i++)
	{
		cngnode=temp;
		temp=temp->nxtfst;
	}

	node2=temp;
	node2after=temp->nxtfst;

	if(datanum2!=1)
		node2before=cngnode;

	clrscr();

	printf("THE FIRST LIST IS:-");
	node1=displayint(node1);
	printf("\n\n\nTHE SECOND LIST IS:-");
	node2=displayint(node2);


	//CONCATINATION STARTS HERE
	printf("\n\nENTER NAME OF THE CONCATINATED NODE:-\t");
	flushall();
	gets(node1->namefst);

	endnode=node1->next;
	for(i=0;i<node1->numin-1;i++)
		endnode=endnode->next;

	if(endnode==NULL)
		node1->next=node2->next;
	else
		endnode->next=node2->next;

	node1->numin=node1->numin+node2->numin;

	if(datanum2==1)
		linklist->fstll=node2after;
	else
		(node2before)->nxtfst=node2after;

	if(node2after==NULL)
		linklist->lastll=node2before;

	linklist->numll--;
	clrscr();
	displayext();
	printf("\n\nTHE CONACTINATED NODE HAS FOLLOWING DATA:-");
	node1=displayint(node1);


	free(node2);

}
//********************CHOOSING A LINK LIST TO WORK UPON*******
fst* choose()
{

	int datanum,p,q;
	fst* temp;

	backchos:
	clrscr();
	displayext();
	temp=linklist->fstll;

	printf("\n\n\nENTER THE NUMBER OF THE LINK LIST YOU WANT TO WORK UPON:-\t");
	scanf("%d",&datanum);


	if(datanum==0)
	{
		printf("\n\n\aSORRY, THIS NODE HANDLES THE TOTAL COUNT OF THE DATA PRESENT.\n\nUSER'S INTERFERENCE ISN'T ALLOWED !!!!");
		printf("\n\n\nPRESS ANY KEY TO CONTINUE");
		getch();

		goto backchos;
	}

	if(datanum<0 || datanum>linklist->numll)
	{
		printf("\n\n\n\aERROR !!!  FALSE INPUT ENCOUNTERED");
		printf("\n\n\nPRESS ANY KEY TO CONTINUE");
		getch();

		goto backchos;
	}

	for(p=0;p<datanum-1;p++)
	{
		temp=temp->nxtfst;
	}

	return temp;

}
//****************MAY YOUR SPIRIT LAY IN PEACE - freeson*********
void freeson(fst *spirit)
{
	ll* temp1,*temp2;

	temp1=spirit->next;
	free(spirit);

	while(temp1!=NULL)
	{
		temp2=temp1->next;
		free(temp1);
		temp1=temp2;
	}

}

//*********************GO TO STONE AGE - REVERSE EXT**********
void reverseext()
{
	fst *topper,*flopper,*prev,*present,*succed;

	clrscr();
	printf("THE ORIGINAL LIST IS:-\n\n");
	displayext();

	topper=linklist->fstll;
	flopper=linklist->lastll;
	present=succed=topper;
	prev=NULL;

	while(present!=NULL)
	{
		succed=present->nxtfst;
		present->nxtfst=prev;
		prev=present;
		present=succed;
	}

	linklist->lastll=topper;

	(linklist->lastll)->nxtfst=NULL;

	linklist->fstll=flopper;
	printf("\n\n\nTHE REVERSED LIST IS:-\n\n");
	displayext();
	printf("\n\n\aTHE LIST IS NOW REVERSED");
}




//*********************KILL SON OF MOTHER - DELETE************
void delext()
{
	int i,chdel,datanum;
	fst* retdel,*cngnode,*temp,*delnode;

	delnode=linklist->fstll;
	while(1)
	{
		clrscr();
		if(linklist->numll==0)
		{
			linklist->fstll=NULL;
			linklist->lastll=NULL;
			printf("\aTHE LIST IS EMPTY NOW !!!PRESS ENTER TO CONTINUE!");
			goto end;
		}

		cngnode=delnode;

		printf("\t\t\t       D E L E T E\tD A T A\t");
		printf("\n\n\t\t*********************************************");
		printf("\n\n1.DELETE FROM THE MOTHER LIST");
		printf("\n\n2.DISPLAY MOTHER\n\nPRESS \"Esc\" TO EXIT TO LINK LIST MENU");

		printf("\n\nEnter Your Choice:-\t");
		chdel=getkey();

		switch(chdel)
		{

			//DELETE AT ANY POSITION
			case 2: backdel:
				clrscr();

				displayext();


				printf("\n\nENTER THE NUMBER OF SON LIST WHICH YOU WANT TO DELETE:-\t");
				scanf("%d",&datanum);

				if(datanum==0)
				{
					printf("\n\n\aSORRY, THIS MOTHER NODE HANDLES THE TOTAL COUNT OF THE DATA PRESENT.\n\nUSER'S INTERFERENCE ISN'T ALLOWED !!!!");
					printf("\n\n\nPRESS ANY KEY TO CONTINUE");
					getch();

					goto backdel;
				}
				if(datanum<0 || datanum>linklist->numll)
				{
					printf("\n\n\n\aERROR !!!  FALSE INPUT ENCOUNTERED");
					printf("\n\n\nPRESS ANY KEY TO CONTINUE");
					getch();

					goto backdel;
				}

				linklist->numll--;
				if(datanum==1)
					goto del;

				for(i=0;i<datanum-1;i++)
				{
					retdel=cngnode;
					cngnode=cngnode->nxtfst;
					temp=cngnode->nxtfst;
				}
				printf("\n\nTHE SON NODE BEING DELETED IS:-\t%s",cngnode->namefst);
				retdel->nxtfst=temp;

				if(temp==NULL)
				{
					linklist->lastll=retdel;
				}
				freeson(cngnode);

				break;

			case 3: displayext();
				break;

			case 1: goto end;
			default: printf("\n\n\n\aERROR ENCOUNTERED!!!  FALSE INPUT ENTERED");
				 break;


			//DELETE AT FRONT
			del:
				linklist->fstll=delnode->nxtfst;
				printf("\n\nTHE SON NODE BEING DELETED IS:-\t%s",delnode->namefst);
				delnode=delnode->nxtfst;
				freeson(cngnode);
				break;

		}
		getch();
	}
	end:
	printf("\n\nPRESS ANY KEY NOW");
}


//*********************DISPLAY MOTHER & SONS******************
void displayext()
{
	int cnt=0;
	fst* disnode;

	disnode=linklist->fstll;

	if(linklist->numll==0)
	{
		printf("\n\nTHE MOTHER LINK LIST IS EMPTY");
	}
	printf("\n\nTHE NAMES IN THE LIST ARE:-\n\n");
	do
	{
		if(cnt==0)
		{
			printf("0. (THIS NODE SHOWS) TOTAL NUMBER OF ITEMS IN LIST = %d\n\n",linklist->numll);
			cnt++;
			continue;
		}
		else
			printf("%d. %s\n",disnode->numout=cnt,disnode->namefst);
		cnt++;
		disnode=disnode->nxtfst;

	}while(disnode!=NULL);

}


//*********************ADD DATA TO A LINK LIST****************
fst* add(fst *ori)
{
	int i,chadd,datanum;
	ll *retadd,*cngnode,*temp,*adnode;

	adnode=ori->next;

	if(ori->numin==0)
	{
		clrscr();
		goto front;
	}

	while(1)
	{
		cngnode=adnode;

		clrscr();

		printf("\t\t\t       A D D\tD A T A\t");
		printf("\n\n\t\t*********************************************");
		printf("\n\n1.ADD IN THE LIST");
		printf("\n\n2.DISPLAY DATA\n\nPRESS \"Esc\" TO EXIT TO LINK LIST MENU");

		printf("\n\nEnter Your Choice:-\t");
		chadd=getkey();

		switch(chadd)
		{

			//ADD AT ANY POSITION
			case 2: backadd:
				clrscr();
				ori=displayint(ori);
				cngnode=adnode;


				printf("\n\nENTER THE NUMBER AFTER WHICH YOU WANT TO ENTER THE DATA:-\t");
				scanf("%d",&datanum);

				if(datanum<0 || datanum>ori->numin)
				{
					printf("\n\n\n\aERROR !!!  FALSE INPUT ENCOUNTERED");
					printf("\n\n\n	press any key to continue");
					getch();
					goto backadd;
				}

				if(datanum==0)
					goto front;

				temp=(ll*)malloc(sizeof(struct node));

				printf("\n\nENTER THE NAME:-\t");
				flushall();
				gets(temp->name);
				printf("\n\nDATA IS ADDED");

				for(i=0;i<datanum-1;i++)
					cngnode=cngnode->next;

				retadd=cngnode->next;
				temp->next=retadd;
				cngnode->next=temp;
				ori->numin++;
				break;

			case 3: ori=displayint(ori);
				break;

			case 1: goto end;

			default: printf("\n\n\n\aERROR ENCOUNTERED!!!  FALSE INPUT ENTERED");
				 break;


			//ADD AT FRONT
				front:

				printf("\n\nENTER THE NAME:-\t");
				temp=(ll*)malloc(sizeof(struct node));
				flushall();
				gets(temp->name);
				printf("\n\nDATA IS ADDED");


				ori->next=temp;
				temp->next=adnode;
				adnode=temp;
				ori->numin++;
				break;

		}
		getch();
	}
	end:
	printf("\n\nPRESS ANY KEY NOW");
	return (ori);
}

//*********************REVERSING A LINK LIST***********************
fst* reverse(fst* ori)
{
	int cnt=0;
	char tempstr[MAX];
	ll *retnode,*cgnode,*tmpnode,*revnode;

	clrscr();

	ori=displayint(ori);

	revnode=ori->next;
	retnode=revnode;
	cgnode=(ll*)malloc(sizeof(struct node));

	while(revnode!=NULL)
	{
		strcpy(tempstr,revnode->name);

		revnode=revnode->next;

		if(cnt==0)
		  cgnode->next=NULL;


		else
		{
			cgnode=(ll*)malloc(sizeof(struct node));
			cgnode->next=tmpnode;
		}

		strcpy(cgnode->name,tempstr);
		tmpnode=cgnode;
		cnt++;
	}

	while(retnode!=NULL)
	{
		revnode=retnode;
		retnode=retnode->next;
		free(revnode);
	}

	printf("\n\nTHE REVRESED LIST IS:-");
	ori->next=cgnode;
	ori=displayint(ori);
	printf("\n\n\n\aTHE LIST IS REVERSED NOW");

	return ori;
}

//*********************EDITING DATA OF A LINK LIST*****************
fst* edit(fst *ori)
{
	int i,datanum;
	char chedt;
	ll* retedt,*edtnode;

	edtnode=ori->next;
	do
	{
		backedt:
		clrscr();
		printf("press 0 to change name of LINK LIST");
		retedt=edtnode;
		ori=displayint(ori);


		printf("\n\n\nENTER THE NUMBER OF THE NODE WHICH YOU WANT TO EDIT:-\t");
		scanf("%d",&datanum);

		if(datanum==0)
		{
			printf("\n\n\aENTER NEW NAME OF THIS LINK LIST:-\t");
			flushall();
			gets(ori->namefst);
			goto more;
		}

		if(datanum<0 || datanum>ori->numin)
		{
			printf("\n\n\n\aERROR !!!  FALSE INPUT ENCOUNTERED");
			printf("\n\n\n	press any key to continue");
			getch();

			goto backedt;
		}

		for(i=0;i<datanum-1;i++)
		{
			retedt=retedt->next;
		}

		printf("\n\nEnter New Data at NODE %d:-\t",datanum);
		flushall();
		gets(retedt->name);

		more:
		printf("\n\n\n\nWANT TO EDIT ANOTHER NODE:-(y/n)\t");
		flushall();
		scanf("%c",&chedt);

	}while(chedt=='y');

	return ori;
}
//*********************DELETE DATA FROM A LINK LIST****************
fst* del(fst *ori)
{
	int i,chdel,datanum;
	ll* retdel,*cngnode,*temp,*delnode;

	delnode=ori->next;
	while(1)
	{
		clrscr();
		if(ori->numin==0)
		{
			ori->next=NULL;
			printf("\aTHE LIST IS EMPTY NOW !!!PRESS ENTER TO CONTINUE!");
			return ori;
		}

		cngnode=delnode;

		printf("\t\t\t       D E L E T E\tD A T A\t");
		printf("\n\n\t\t*********************************************");
		printf("\n\n1.DELETE FROM THE LIST");
		printf("\n\n2.DISPLAY DATA\n\nPRESS \"Esc\" TO EXIT TO MAIN MENU");

		printf("\n\nEnter Your Choice:-\t");
		chdel=getkey();

		switch(chdel)
		{

			//DELETE AT ANY POSITION
			case 2: backdel:
				clrscr();

				ori=displayint(ori);


				printf("\n\nENTER THE NUMBER OF NODE WHICH YOU WANT TO DELETE:-\t");
				scanf("%d",&datanum);

				if(datanum==0)
				{
					printf("\n\n\aSORRY, THIS NODE HANDLES THE TOTAL COUNT OF THE DATA PRESENT.\n\nUSER'S INTERFERENCE ISN'T ALLOWED !!!!");
					printf("\n\n\n	press any key to continue");
					getch();

					goto backdel;
				}
				if(datanum<0 || datanum>ori->numin)
				{
					printf("\n\n\n\aERROR !!!  FALSE INPUT ENCOUNTERED");
					printf("\n\n\n	press any key to continue");
					getch();

					goto backdel;
				}

				ori->numin--;
				if(datanum==1)
					goto del;

				for(i=0;i<datanum-1;i++)
				{
					retdel=cngnode;
					cngnode=cngnode->next;
					temp=cngnode->next;
				}
				printf("\n\nTHE DATA BEING DELETED IS:-\t%s",cngnode->name);
				free(cngnode);
				retdel->next=temp;
				break;

			case 3: ori=displayint(ori);
				break;

			case 1: goto end;
			default: printf("\n\n\n\aERROR ENCOUNTERED!!!  FALSE INPUT ENTERED");
				 break;


			//DELETE AT FRONT
			del:
				ori->next=delnode->next;
				printf("\n\nTHE DATA BEING DELETED IS:-\t%s",delnode->name);
				delnode=delnode->next;
				free(cngnode);
				break;

		}
		getch();
	}
	end:
	printf("\n\nPRESS ANY KEY NOW");
	return ori;
}

//*********************DISPLAY LINK LIST**********************
fst* displayint(fst* ori)
{
	int cnt=0;
	ll* disnode;

	disnode=ori->next;

	if(ori->numin==0)
	{
		printf("\n\nTHE LINK LIST IS EMPTY");
		return ori;
	}
	printf("\n\nTHE NAMES IN THE LIST \"%s\" ARE:-\n\n",ori->namefst);
	do
	{
		if(cnt==0)
		{
			printf("0. (THIS NODE SHOWS) TOTAL NUMBER OF ITEMS IN LIST = %d\n\n",ori->numin);
			cnt++;
			continue;
		}
		else
			printf("%d. %s\n",cnt,disnode->name);
		cnt++;
		disnode=disnode->next;

	}while(disnode!=NULL);

	return ori;
}

//*********************CREATING A NEW LINK LIST********************
fst* create()
{
	char chcreate='n';
	ll *crnewnode;
	fst* newllfst;
	clrscr();
	//ALLOCATING MEMORY FOR A NEW LINK LIST
	newllfst=(fst*)malloc(sizeof(struct first));

	if(newllfst==NULL)
	{
		printf("\a\aNO MORE FREE SPACE AVAILABLE");
		return newllfst;
	}

	//to get heading of a new link list
	printf("ENTER THE NAME OF THE NEW LIST:-\t");
	flushall();
	gets(newllfst->namefst);

	newllfst->numin=0; //initializes number of internal data nodes
	linklist->numll++;  //increases mother's count of link lists
	newllfst->numout=linklist->numll;//tells each link list its position

	if(linklist->numll==1)
	{
		linklist->fstll=newllfst; //connects very first linklist to mother
		linklist->lastll=newllfst; //the last node is the first node too
		newllfst->nxtfst=NULL; //the next node of the type "first" is not yet there
	}
	else
	{
		(linklist->lastll)->nxtfst=newllfst;//connects new son to last son of mother
		linklist->lastll=newllfst;//increments "last son pointer" of mother
		newllfst->nxtfst=NULL; //the next node of the type "first" is not yet there

	}


	//space allocation for very first data node
	crnewnode=(ll*)malloc(sizeof(struct node));
	newllfst->next=crnewnode;//links 0th node to first data node

	do
	{
		printf("\n\nENTER DATA:-\t");
		flushall();
		gets(crnewnode->name);
		crnewnode->next=NULL;
		newllfst->numin++;

		clrscr();
		newllfst=displayint(newllfst);

		printf("\n\nWANNA ADD NEW DATA(y/n):-\t");
		flushall();
		scanf("%c",&chcreate);


		if(chcreate=='y')
		{
			//ALLOCATING SPACE FOR INTERNAL NODES OF A LINK LIST
			crnewnode->next=(ll*)malloc(sizeof(struct node));
			crnewnode=crnewnode->next;
			crnewnode->next=NULL;
		}

	}while(chcreate=='y');

	return newllfst;
}

//*******************SORTING ALL SONS IN ALPHABETICAL ORDER**********
void sortext()
{
	int m,n,dif;
	int ex=linklist->numll;
	fst *compnode,*prev,*succed,*present,*temp;

	clrscr();
	printf("ALL LINK LISTS WILL BE SORTED IN ALPHABETICAL ORDER");
	printf("\n\nUNSORTED LIST:-\n\n");

	displayext();

	//BUBBLE SORT
	for(m=0;m<ex-1;m++)
	{
		present=linklist->fstll;
		compnode=present->nxtfst;

		for(n=0;n<ex-m-1;n++)
		{
			temp=present;
			dif=strcmp(present->namefst,compnode->namefst);
			succed=compnode->nxtfst;

			if(dif > 0 && dif!=32 && dif!=-32)
			{
				present->nxtfst=succed;

				if(n==0)
					linklist->fstll=compnode;
				else
					prev->nxtfst=compnode;

				compnode->nxtfst=present;
				temp=compnode;
				prev=compnode;
			}

			else//if swap does not takes place
			{
				prev=present;
				present=present->nxtfst;
			}
			compnode=present->nxtfst;

			if(n==0)
				linklist->fstll=temp;
			if(m==0 && n==ex-2)
			{
				linklist->lastll=present;
				(linklist->lastll)->nxtfst=NULL;
			}
		}
	}
	printf("\n\nSORTED LIST:-\n\n");
	displayext();
	printf("\n\n\n\aTHE LIST IS SORTED NOW");
}



//********************SORTING DATA************************
fst* sort(fst* ori)
{
	int m,n,dif,ex=ori->numin;
	ll*temp,*cngnode,*srtnode;

	clrscr();
	printf("ALL ITEMS WILL BE SORTED IN ALPHABETICAL ORDER");
	printf("\n\nUNSORTED LIST:-\n\n");

	ori=displayint(ori);

	cngnode=ori->next;
	srtnode=cngnode;

	for(m=0;m<ex-1;m++)
	{
		for(n=0;n<ex-m-1;n++)
		{
			dif=strcmp (srtnode->name,(srtnode->next)->name);
			strcpy(temp->name,NULL);

			if(dif > 0 && dif!=32 && dif !=-32)
			{
				strcpy(temp->name,srtnode->name);
				strcpy(srtnode->name,(srtnode->next)->name);
				strcpy((srtnode->next)->name,temp->name);
			}
			srtnode=srtnode->next;
		}
		srtnode=cngnode;
	}

	printf("\n\nSORTED LIST:-\n\n");
	ori=displayint(ori);
	printf("\n\n\n\aTHE LIST IS SORTED NOW");
	return ori;
}

int getkey()
{
	union REGS i,o;
	while(!kbhit())

	i.h.ah=0;
	int86 (22,&i,&o);
	return(o.h.ah);
}
//hi its me ANIRUDH TOMER
void tomer(int timer)
{
	int i,j,k,m,n;

	clrscr();

	printf("HI Mr.USER\n\n");
	printf("I TOOK 3%c DAYS TO COMPLETE THIS PROGRAM\n\n& IT IS THE BIGGEST PROGRAM I HAVE EVER MADE.",171);

	delay(1000);
	printf("\n\nI HAVEN'T COPYED A SINGLE WORD FROM ANY BOOK TO MAKE IT (except the function to get scan codes)...I SWEAR!!!");
	printf("\n\n\n\nTHE COMPLETE IDEA OF CREATING THIS PROGRAM IS JUST AN IMAGINATION OF MY MIND.");
	delay(4000);
	printf("\n\n\n\nIAM");
	for(i=0;i<6;i++)
	{
		delay(250);
		printf(".");
	}
	clrscr();

	textcolor(RED);
	for(i=0;i<13;i++)
	{
	     j=i*3;
	     for(k=0;k<j;k++)
	     {
		printf(" ");
	     }

	     cprintf("%c%c%c%c%c%c%c%c-%c",65,78,73,82,85,68,72,32,32);

	     m=71-i*6;
	     for(n=m;n>=0;n--)
	     {
		printf(" ");
	     }
	     cprintf("%c%c%c%c%c",84,79,77,69,82);

	     delay(100);
	     if(i!=12)
		clrscr();
	     else
		textcolor(WHITE);
	}
	printf("\n\n\nSIZE OF THE PROGRAM FILE ON DISK = 22 Kb");
	printf("\n\nNO OF LINES GETTING COMPILED = 2276");
	printf("\n\nDATE & TIME OF CREATION :-\t 23 JAN 2009\t10:33 PM");
	printf("\n\nNUMBER OF LINES TYPED = 1101");
	printf("\n\nDEDICATED TO MY BEST FRIEND \"AASHISH AGARWAL aka DALLA\"");

	delay(1000);
	if(timer==1)
		printf("\n\n\nI KNOW THAT AFTER PRESSING \"Ctrl+F9\" \n\nTHE VERY NEXT BUTTUON YOU PRESSED WAS \"BACKSPACE\"");


	printf("\n\n\n\nI HOPE YOU WILL LOVE MY WORK.");
	printf("\n\n\nPRESS ENTER TO GO BACK");
}
