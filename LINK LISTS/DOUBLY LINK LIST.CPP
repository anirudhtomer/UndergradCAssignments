//*******************DOUBLY LINK LIST *******************

#include<iostream.h>
#include<stdlib.h>
#include<conio.h>

class node
{
	int data;
	class node *next;
	class node *prev;

	public:
	friend class linklist;
};

class linklist
{
	class node *head;

	public:
	linklist()
	{
		head=new(node);
		head->data=0;
		head->next=NULL;
		head->prev=NULL;
	}

	void create(void);

	void displaylr(void);
	void displayrl(void);

	void inspos(void);
	void delpos(void);

	void sort_link(void);
	void reverse(void);
	void merge(void);
};



int main(void)
{
	int chmnu;
	class linklist list1;

	while(1)
	{
		clrscr();
		cout<<"\n\n1.CREATE LINK LIST\n2.DISPLAY LEFT-RIGHT\n";
		cout<<"3.DISPLAY RIGHT-LEFT\n4.INSERT BY POSITION\n";
		cout<<"5.DELETE BY POSITION\n6.SORTING BY LINK\n";
		cout<<"7.REVERSE LIST\n8.MERGING OF LISTS\n\n9.EXIT";

		cout<<"\n\n\nEnter Your Choice:-\t";
		cin>>chmnu;

		switch(chmnu)
		{
			case 1: clrscr();
					list1.create();
					break;

			case 2: list1.displaylr();
					break;

			case 3: list1.displayrl();
					break;

			case 4: list1.inspos();
					break;

			case 5:	list1.delpos();
					break;

			case 6: list1.sort_link();
					break;

			case 7: list1.reverse();
					break;

			case 8: list1.sort_link();
					clrscr();
					list1.merge();
					break;

			case 9: return 0;
			default: cout<<"\n\n\n\aERROR !!!  FALSE INPUT ENCOUNTERED";
		}

		getch();
	}
}


//*********CREATING A LINK LIST****************
void linklist::create(void)
{
	char chcreate='n';
	class node *temp;

	//ALLOCATING MEMORY FOR A NEW LINK LIST
	temp=new(node);

	if(temp==NULL)
	{
		cout<<"\a\aNO MORE FREE SPACE AVAILABLE";
		exit(0);
	}
	head->next=temp;
	temp->prev=head;

	do
	{
		head->data++;
		cout<<"\n\nENTER DATA:-\t";
		cin>>temp->data;
		temp->next=NULL;

		cout<<"\n\nWANNA ADD NEW DATA(y/n):-\t";
		cin>>chcreate;

		if(chcreate=='y')
		{
			temp->next=new(node);
			(temp->next)->prev=temp;
			temp=temp->next;
		}

	}while(chcreate=='y');

}

//*********************DISPLAY LEFT TO RIGHT**********************
void linklist::displaylr(void)
{
	int cnt=1;
	class node *disnode;

	disnode=head->next;

	if(head->next==NULL)
	{
		cout<<"\n\nTHE LINK LIST IS EMPTY!!";

		goto enddis;
	}

	cout<<"\n\nTHE DATA IN THE LIST ARE (from L-R):-\n";
	cout<<"---------------------------------------\n\n";
	cout<<"PREVIOUS LINK\t\tDATA\t\tPRESENT LINK\n\n";

	do
	{
		cout<<disnode->prev<<"\t\t"<<cnt<<". "<<disnode->data<<"\t\t"<<disnode<<"\n";
		cnt++;
		disnode=disnode->next;

	}while(disnode!=NULL);

	enddis:
}

//*********************DISPLAY RIGHT TO LEFT **********************
void linklist::displayrl(void)
{
	int cnt=0;
	class node *disnode;

	disnode=head;

	while(disnode->next!=NULL)
	{
		disnode=disnode->next;
		cnt++;
	}

	if(head->next==NULL)
	{
		cout<<"\n\nTHE LINK LIST IS EMPTY!!";

		goto enddis;
	}

	cout<<"\n\nTHE DATA IN THE LIST ARE (from R-L):-\n";
	cout<<"---------------------------------------\n\n";
	cout<<"PREVIOUS LINK\t\tDATA\t\tPRESENT LINK\n\n";

	do
	{
		cout<<disnode->prev<<"\t\t"<<cnt<<". "<<disnode->data<<"\t\t"<<disnode<<"\n";
		cnt--;
		disnode=disnode->prev;

	}while(disnode!=head);


	enddis:
}

//***************INSERT BY POSITION***********
void linklist::inspos()
{

	int i,chadd,datanum;
	class node *retadd,*cngnode,*temp,*adnode;

	adnode=head->next;

	if(head->next==NULL)
	{
		clrscr();
		goto front;
	}

	while(1)
	{
		cngnode=adnode;

		clrscr();

		cout<<"\t\t\t       A D D\tD A T A\t";
		cout<<"\n\n1.INSERT IN THE LIST\n2.DISPLAY DATA\n3.BACK TO MAIN MENU";
		cout<<"\n\nEnter Your Choice:-\t";
		cin>>chadd;

		switch(chadd)
		{

			//ADD AT ANY POSITION
			case 1: backadd:
				clrscr();
				displaylr();
				cngnode=adnode;


				cout<<"\n\nENTER POSITION OF NEW NODE:-\t";
				cin>>datanum;
				datanum--;

				if(datanum<0 || datanum>head->data)
				{
					cout<<"\n\n\n\aERROR !!!  FALSE INPUT ENCOUNTERED";
					cout<<"\n\n\n	press any key to continue";
					getch();
					goto backadd;
				}

				if(datanum==0)
					goto front;

				temp=new(node);

				cout<<"\n\nENTER THE DATA:-\t";
				cin>>temp->data;
				cout<<"\n\nDATA IS ADDED";

				for(i=0;i<datanum-1;i++)
					cngnode=cngnode->next;

				temp->prev=cngnode;
				retadd=cngnode->next;
				temp->next=retadd;
				if(retadd!=NULL)
					retadd->prev=temp;

				cngnode->next=temp;
				head->data++;

				break;

			case 2: displaylr();
				break;

			case 3: goto endinspos;

			default: cout<<"\n\n\n\aERROR ENCOUNTERED!!!  FALSE INPUT ENTERED";
				 break;


			//ADD AT FRONT
				front:

				cout<<"\n\nENTER THE DATA:-\t";
				temp=new(node);
				cin>>temp->data;
				cout<<"\n\nDATA IS ADDED";

				head->next=temp;
				temp->next=adnode;
				adnode->prev=temp;
				adnode=temp;
				adnode->prev=head;
				head->data++;

				break;

		}
		getch();
	}
	endinspos:
}

//*********************DELETE DATA FROM A LINK LIST****************
void linklist::delpos()
{
	int i,chdel,datanum;
	class node *retdel,*cngnode,*temp,*delnode;


	while(1)
	{
		delnode=head->next;
		clrscr();
		if(head->data==0)
		{
			head->next=NULL;
			cout<<"\aTHE LIST IS EMPTY NOW !!!PRESS ENTER TO CONTINUE!";
			goto enddelpos;
		}

		cngnode=delnode;

		cout<<"\t\t\t       D E L E T E\tD A T A\t";
		cout<<"\n\n1.DELETE FROM THE LIST\n2.DISPLAY DATA\n3.EXIT TO MAIN MENU";

		cout<<"\n\nEnter Your Choice:-\t";
		cin>>chdel;

		switch(chdel)
		{

			//DELETE AT ANY POSITION
			case 1: backdel:
				clrscr();

				displaylr();


				cout<<"\n\nENTER THE NUMBER OF NODE WHICH YOU WANT TO DELETE:-\t";
				cin>>datanum;

				if(datanum==0)
				{
					cout<<"\n\n\aSORRY, WITH THE HEAD NODE USER'S INTERFERENCE ISN'T ALLOWED!!!!";
					cout<<"\n\n\n	press any key to continue";
					getch();

					goto backdel;
				}
				if(datanum<0 || datanum>head->data)
				{
					cout<<"\n\n\n\aERROR !!!  FALSE INPUT ENCOUNTERED";
					cout<<"\n\n\n	press any key to continue";
					getch();

					goto backdel;
				}

				head->data--;

				if(datanum==1)
					goto del;

				for(i=0;i<datanum-1;i++)
				{
					retdel=cngnode;
					cngnode=cngnode->next;
					temp=cngnode->next;
				}

				cout<<"\n\nTHE DATA BEING DELETED IS:-\t"<<cngnode->data;
				delete(cngnode);
				retdel->next=temp;

				if(temp!=NULL)
					temp->prev=retdel;
				break;

			case 2: displaylr();
				break;

			case 3: goto enddelpos;
			default: cout<<"\n\n\n\aERROR ENCOUNTERED!!!  FALSE INPUT ENTERED";
				 break;


			//DELETE AT FRONT
			del:
				head->next=delnode->next;
				if(delnode->next!=NULL)
					(delnode->next)->prev=head;

				cout<<"\n\nTHE DATA BEING DELETED IS:-\t"<<delnode->data;
				delete(delnode);
				break;

		}
		getch();
	}
	enddelpos:
	cout<<"\n\nPRESS ANY KEY NOW";
}

//*******************SORTING BY LINK**********
void linklist::sort_link()
{
	int m,n,dif;
	int ex=head->data;
	class node *compnode,*previous,*succed,*present,*temp;

	clrscr();
	if(head->next==NULL)
	{
		cout<<"THE LIST IS EMPTY";
		goto endsrtlink;
	}
	cout<<"\n\nUNSORTED LIST:-\n\n";

	displaylr();

	//BUBBLE SORT
	for(m=0;m<ex-1;m++)
	{
		present=head->next;
		compnode=present->next;

		for(n=0;n<ex-m-1;n++)
		{
			temp=present;
			succed=compnode->next;

			if(present->data>compnode->data)
			{
				present->next=succed;
				succed->prev=present;

				if(n==0)
				{
					head->next=compnode;
					compnode->prev=head;
				}
				else
				{
					previous->next=compnode;
					compnode->prev=previous;
				}

				compnode->next=present;
				present->prev=compnode;

				temp=compnode;
				previous=compnode;
			}

			else//if swap does not takes place
			{
				previous=present;
				present=present->next;
			}
			compnode=present->next;

			if(n==0)
			   head->next=temp;
		}
	}
	cout<<"\n\nSORTED LIST:-\n\n";
	displaylr();
	cout<<"\n\n\nTHE LIST IS SORTED NOW";
	endsrtlink:
}

//**************REVERSE LINK LIST (by links)*****************
void linklist::reverse()
{
	class node *previous,*present,*succed;

	clrscr();
	cout<<"THE ORIGINAL LIST IS:-\n\n";
	displaylr();

	present=succed=head->next;
	previous=NULL;

	while(present!=NULL)
	{
		succed=present->next;
		present->prev=succed;
		present->next=previous;
		previous=present;
		present=succed;
	}
	if(present==NULL)
	{
		head->next=previous;
		previous->prev=head;
	}

	cout<<"\n\n\nTHE REVERSED LIST IS:-\n\n";
	displaylr();
	cout<<"\n\n\aTHE LIST IS NOW REVERSED";
}

//************MERGING OF LINK LISTS*****************
void linklist::merge()
{
	class node *fst1,*fst2,*prev1;
	class linklist conky;

	clrscr();
	cout<<"IF U HAVEN'T CREATED 1st LIST IT WILL BE CREATED ITSELF & INITIALIZED TO NULL";
	cout<<"\n\nENTER THE FOLLOWING FOR 2nd NODE\n";
	conky.create();


	while(conky.head->next!=NULL)
	{
		prev1=head;
		fst1=head->next;
		fst2=conky.head->next;

		while(fst1!=NULL)
		{
			if(fst2->data<fst1->data)
			{
				conky.head->next=fst2->next;
				if(fst2->next!=NULL)
					(fst2->next)->prev=conky.head;

				prev1->next=fst2;
				fst2->prev=prev1;
				fst2->next=fst1;
				fst1->prev=fst2;
				goto endmerge;
			}
			prev1=fst1;
			fst1=fst1->next;
		}
		if(fst1==NULL)
		{
			conky.head->next=fst2->next;
			if(fst2->next!=NULL)
				(fst2->next)->prev=conky.head;

			prev1->next=fst2;
			fst2->prev=prev1;
			fst2->next=NULL;
		}
		endmerge:
		head->data++;
		conky.head->data--;
	}
	clrscr();
	cout<<"THE MERGED LINK LIST IS:-\t";
	displaylr();

}




