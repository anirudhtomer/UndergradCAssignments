//ANIRUDH TOMER....SE COMP-I....SE 42028

//PROGRAM TO IMPLEMENT GENERALISED LINK LIST

#include<iostream.h>
#include<conio.h>

class node
{
	int tag;
	class node *next;
	union
	{
		int data;
		class node *dlink;

	};

	public:
	friend class gll;
};

class gll
{
	class node *head;

	public:
	gll()
	{
		head=new(node);
		head->next=NULL;
	}

	void create(int);

	//PROTOTYPES FOR WORKHORSE FUNCTIONS
	void display(class node *);
	void copy(class node*,class node*);
	int equality(class node*,class node*);
	int depth(class node*);



	//DEFINITION FOR DRIVER FUNCTIONS
	void display(void)
	{
		display(head);
	}

	void copy(class gll flist)
	{
		copy(head,flist.head);
	}

	int equality(class gll slist)
	{
		return(equality(head,slist.head));
	}

	int depth()
	{
		return(depth(head));
	}


};



int main(void)
{
	int chmnu=0,x=0;
	class gll list1,list2;

	while(1)
	{
		clrscr();
		cout<<"\t  G E N E R A L I S E D\t\tL I N K\t\tL I S T\n";
		cout<<"     ----------------------------------------";
		cout<<"----------------------------\n\n";
		cout<<"\n\n1.CREATE FIRST LINK LIST\n\n2.DISPLAY FIRST LINK LIST\n\n";
		cout<<"3.COPY FIRST LIST IN ANOTHER\n\n4.EQUALITY\n\n";
		cout<<"5.DEPTH OF FIRST LIST\n\n6.EXIT";

		cout<<"\n\n\nEnter Your Choice:-\t";
		cin>>chmnu;

		switch(chmnu)
		{
			case 1: clrscr();
				  list1.create(0);
				  x=1;

				  break;

			case 2: clrscr();

				  cout<<"THE GLL IS ::\t";
				  list1.display();

				  break;

			case 3: list2.copy(list1);
				  clrscr();

				  cout<<"THE ORIGINAL LIST IS::\t";
				  list1.display();

				  cout<<"\n\nTHE COPYED LIST IS::\t";
				  list2.display();

				  break;

			case 4: clrscr();

				  if(!x) //TO CHECK IF FIRST LIST IS CREATED OR NOT
				  {
					cout<<"ENTER THE DATA FOR FIRST GLL::\n\n";
					list1.create(0);
				  }
				  x=1;
				  clrscr();

				  cout<<"ENTER THE DATA FOR SECOND GLL::\n\n";
				  list2.create(0);

				  clrscr();
				  cout<<"THE FIRST LIST IS::\t";
				  list1.display();

				  cout<<"\n\nTHE SECOND LIST IS::\t";
				  list2.display();

				  if(list1.equality(list2))
					cout<<"\n\n\n\n\nTHE LISTS ARE EQUAL";
				  else
					cout<<"\n\n\n\n\n\THE LISTS ARE NOT EQUAL";

				  break;

			case 5: clrscr();
				  cout<<"THE FIRST LIST IS::\t";
				  list1.display();

				  x=list1.depth();
				  cout<<"\n\n\nTHE DEPTH OF THE FIRST GLL IS "<<x;
				  x=1;
				  break;

			case 6:return 0;
			default: cout<<"\n\n\n\aERROR !!!  FALSE INPUT ENCOUNTERED";
		}

		getch();
	}
}


//*********CREATING A GENERALISED LINK LIST****************
void gll::create(int listnum)
{
	int flag;
	char chcreate='n';
	class node *temp,*prev;
	gll *ptr;


	head->next=NULL;
	prev=head;

	if(listnum!=0)
		cout<<"\n\nDO U WANNA ADD (y/n) IN SUBLIST \""<<listnum<<"\" :-\t";
	else
		cout<<"\n\nDO U WANNA ADD (y/n) IN \"MAIN\" LIST :-\t";

	cin>>chcreate;

	while(chcreate=='y'||chcreate=='Y')
	{
		temp=new(node);
		prev->next=temp;
		prev=temp;
		temp->next=NULL;

		flag=0;

		do
		{
			if(flag)
				cout<<"\n\nENTER PROPER TAG (for list "<<listnum<<" ) ::\t";
			else
				cout<<"\n\nENTER THE TAG (for list "<<listnum<<" ) ::\t";

			cin>>temp->tag;

			flag=1;

		}while(temp->tag!=0 && temp->tag!=1);


		if(temp->tag==0)
		{
			cout<<"\n\nENTER DATA:-\t";
			cin>>temp->data;
		}

		else
		{
			listnum++;

			ptr = new gll;

			temp->dlink = ptr->head;
			ptr->create(listnum);

			listnum--;

		}

		if(listnum!=0)
			cout<<"\n\nDO U WANNA ADD MORE (y/n) IN SUBLIST \""<<listnum<<"\" :-\t";
		else
			cout<<"\n\nDO U WANNA ADD MORE (y/n) IN \"MAIN\" LIST :-\t";

		cin>>chcreate;

	}
}

//*****************DISPLAY GLL***************
void gll::display(class node *dean)
{
	class node *temp;

	temp=dean->next;

	cout<<"(";

	while(temp!=NULL)
	{
		if(temp->tag==0)
			cout<<temp->data;

		else
			display(temp->dlink);

		temp=temp->next;

		if(temp!=NULL)
			cout<<",";
	}
	cout<<")";


}

//***************COPY LIST***********************
void gll::copy(class node *dean,class node *dean_first)
{
	class node *copnode,*temp,*tphead;

	temp=dean_first->next;

	if(temp==NULL)
		dean->next=NULL;

	else
	{
		copnode=new(node);
		dean->next=copnode;
	}


	while(temp!=NULL)
	{
		copnode->tag=temp->tag;

		if(temp->tag==0)
			copnode->data=temp->data;

		else
		{
			tphead=new(node);
			tphead->next=NULL;

			copnode->dlink=tphead;

			copy(tphead,temp->dlink);
		}

		temp=temp->next;
		copnode->next=NULL;

		if(temp!=NULL)
		{
			copnode->next=new(node);
			copnode=copnode->next;
		}

	}

}


//************* COMPARE TWO GLL's FOR EQUALITY ************
int gll::equality(class node *dean1,class node *dean2)
{
	class node *temp1,*temp2;

	temp1=dean1->next;
	temp2=dean2->next;


	while(temp1!=NULL && temp2!=NULL)
	{
		if(temp1->tag==temp2->tag)
		{
			if(temp1->tag==0)
			{
				if(temp1->data!=temp2->data)
					return 0;

			}

			else
				return(equality(temp1->dlink,temp2->dlink));

		}

		else
			return 0;

		temp1=temp1->next;
		temp2=temp2->next;


	}

	if(temp1==NULL && temp2==NULL)
		return 1;

	return 0;

}

//*************** DEPTH OF LINK LIST**************
int gll::depth(class node *dean)
{
	int depnew,depold=0;

	class node *temp;

	temp=dean->next;

	if(temp==NULL)
		return 0;


	while(temp!=NULL)
	{
		if(temp->tag)
		{
			depnew=depth(temp->dlink);

			if(depnew>depold)
				depold=depnew;
		}
		temp=temp->next;

	}

	return depold+1;

}

