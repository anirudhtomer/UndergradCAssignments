//ANIRUDH TOMER....TE COMP-1...42037

#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>

#define SIZE 30

#define NUM 1
#define VRCHAR 2
#define FLT 3

class tuple
{
	public:

	struct NUMBER
	{
		long num;
		NUMBER *nxt_num;
	} *number;

	struct VARCHAR2
	{
		char vrchr[SIZE];
		VARCHAR2 *nxt_vrchr;
	} *vrchar;

	struct FLOAT
	{
		float flt;
		FLOAT *nxt_flt;
	} *floate;

	tuple *nexttuple;

	tuple()
	{
		number = NULL;
		floate = NULL;
		vrchar = NULL;
		nexttuple = NULL;
	}
};

class node
{
	public:

	tuple *t1;

	char *tabname;

	node *nexttab;

	node(char *name)
	{
		tabname = new char[SIZE];
		strcpy(tabname,name);
		nexttab = NULL;
		t1 = new tuple();
	}
};

class list_tab
{
	public:

	node *head;

	list_tab()
	{
		head = new node("HEAD");
	}

	node* addtab(char *);

};

class sql
{
	list_tab l1;
	char *tempstr;

	public:
	sql()
	{
		tempstr = new char[SIZE];
	}

	~sql()
	{
		delete []tempstr;
	}

	//controlling the prompt
	int prompt_control();

	//COMMANDS OF SQL TO BE IMPLEMENTED
	void create_table();
	void insert_into();
	void select_all();
	void update_table();
	void drop_table();

};

int main()
{
	return (new sql()->prompt_control());
}

//CONTROLLING THE PROMPT
int sql::prompt_control()
{
	int chprompt;

	while(1)
	{
		clrscr();

		cout<<"\n\n\t\tORACLE_TCC edition Copyrighted @ Team R1\n\n";
		cout<<"1. CREATE TABLE\n\n2. INSERT INTO TABLE \n\n";
		cout<<"3. SELECT *  FROM TABLE\n\n4. DELETE ENTRY FROM TABLE\n\n";
		cout<<"5. UPDATE TABLE \n\n6. DROP TABLE\n\n7. EXIT";
		cout<<"\n\nEnter Your Choice:-\t";
		cin>>chprompt;

		if(chprompt<7 && chprompt >0)
		{
			cout<<"\n\nEnter The Name Of TABLE:-\t";
			flushall();
			gets(tempstr);
		}

		switch(chprompt)
		{
			case 1: create_table();
					break;

			case 2: insert_into();
					break;

			case 3: select_all();
					break;

			case 5: update_table();
					break;

			case 6: drop_table();
					break;

			case 7: return 0;
			default: cout<<"\n\nENTER PROPER CHOICE";
		}

		getch();
	}
}

//CREATE TABLE
void sql::create_table()
{
	int chcreate;

	node * tempnode = NULL;
	tuple::VARCHAR2 *tempvrchr = NULL;

	tempnode = l1.addtab(tempstr);
	tempvrchr = tempnode->t1->vrchar;

	while(1)
	{
		clrscr();

		cout<<"\n\n********** ADD ENTRIES TO THE TABLE "<<tempstr<<" **********\n\n";
		cout<<"1. ADD \"number\" field\n\n";
		cout<<"2. ADD \"varchar2\" field\n\n";
		cout<<"3. ADD \"double\" field\n\n";
		cout<<"4. I AM DONE WITH ADDING THE FIELDS...CREATE THE TABLE NOW";
		cout<<"\n\nEnter Your Choice:-\t";
		cin>>chcreate;

		if(chcreate<4 && chcreate>0)
		{
			cout<<"\n\nEnter The \"NAME OF THE FIELD\":-\t";
			flushall();
			gets(tempstr);


			if(tempvrchr==NULL)
			{
				tempvrchr = new tuple::VARCHAR2();
				tempnode->t1->vrchar = tempvrchr;
			}
			else
			{
				tempvrchr->nxt_vrchr = new tuple::VARCHAR2();
				tempvrchr = tempvrchr->nxt_vrchr;
			}

			tempvrchr->vrchr[0] = chcreate + 48;
			tempvrchr->vrchr[1] = '\0';

			strcat(tempvrchr->vrchr,tempstr);
			tempvrchr->nxt_vrchr = NULL;

			cout<<"\n\nFIELD ADDED";
			getch();
			continue;
		}

		if(chcreate==4)
		{
			if(tempvrchr==NULL)
				cout<<"\n\nTABLE MUST HAVE ATLEAST ONE COLUMN";
			else
			{
				cout<<"\n\nTABLE CREATED";
				return;
			}
		}
		else
			cout<<"ENTER PROPER CHOICE";

		getch();
	}
}

//SELECT * FROM TABLE
void sql::select_all()
{
	int arr[10],i;

	node *tempnode = NULL;
	tuple *temptuple = NULL;

	tuple::VARCHAR2 *tempvrchr = NULL;
	tuple::NUMBER *tempnum = NULL;
	tuple::FLOAT *tempflt = NULL;

	tempnode = l1.head->nexttab;

	while(tempnode!=NULL)
	{
		if(!strcmpi(tempnode->tabname,tempstr))
			break;

		tempnode = tempnode->nexttab;
	}

	if(tempnode==NULL)
	{
		cout<<"NO SUCH TABLE FOUND";
		return;
	}

	clrscr();

	temptuple = tempnode->t1->nexttuple;
	tempvrchr = tempnode->t1->vrchar;

	cout<<"\t\t\t ************ "<<strupr(tempnode->tabname)<<" *************\n\n";
	if(temptuple==NULL)
	{
		cout<<"\n\nNO DATA PRESENT";
		return;
	}

	i=0;

	while(tempvrchr!=NULL)
	{
		cout<<strupr(tempvrchr->vrchr + 1);
		arr[i++] = tempvrchr->vrchr[0] - 48;

		tempvrchr = tempvrchr->nxt_vrchr;
		cout<<"\t\t";
	}
	arr[i]=-1;

	tempvrchr = temptuple->vrchar;
	tempflt = temptuple->floate;
	tempnum = temptuple->number;

	cout<<"\n";
	while(temptuple!=NULL)
	{
		i=0;
		cout<<"\n";
		while(arr[i]!=-1)
		{
			switch(arr[i++])
			{
				case NUM:	 cout<<tempnum->num;
							 tempnum = tempnum->nxt_num;
							 break;

				case VRCHAR: cout<<tempvrchr->vrchr;
							 tempvrchr = tempvrchr->nxt_vrchr;
							 break;

				case FLT: 	 cout<<tempflt->flt;
							 tempflt = tempflt->nxt_flt;
							 break;

			}
			cout<<"\t\t";
		}

		temptuple = temptuple->nexttuple;
		tempvrchr = temptuple->vrchar;
		tempflt = temptuple->floate;
		tempnum = temptuple->number;

	}
}

//INSERT COMMAND
void sql::insert_into()
{
	node *tempnode = NULL;
	tuple *temptuple = NULL;

	tuple::VARCHAR2 *tempvrchr = NULL,*field = NULL;
	tuple::NUMBER *tempnum = NULL;
	tuple::FLOAT *tempflt = NULL;

	tempnode = l1.head->nexttab;

	while(tempnode!=NULL)
	{
		if(!strcmpi(tempnode->tabname,tempstr))
			break;

		tempnode = tempnode->nexttab;
	}

	if(tempnode==NULL)
	{
		cout<<"NO SUCH TABLE FOUND";
		return;
	}

	clrscr();

	temptuple = tempnode->t1;

	while(temptuple->nexttuple!=NULL)
		temptuple = temptuple->nexttuple;

	temptuple->nexttuple = new tuple();
	temptuple = temptuple->nexttuple;

	field = tempnode->t1->vrchar;

	tempvrchr = temptuple->vrchar;
	tempnum = temptuple->number;
	tempflt = temptuple->floate;

	do
	{
		cout<<"Enter The Value Of The Field \""<<strupr(field->vrchr +1 )<<"\"";
		switch(field->vrchr[0]-48)
		{
			case NUM: 	 cout<<" (NUMBER) :-\t";

						 if(tempnum==NULL)
						 {
							temptuple->number = new tuple::NUMBER();
							tempnum = temptuple->number;
						 }
						 else
						 {
							tempnum->nxt_num = new tuple::NUMBER();
							tempnum = tempnum->nxt_num;
						 }

						 tempnum->nxt_num = NULL;
						 cin>>tempnum->num;

						 break;

			case VRCHAR: cout<<" (VARCHAR2) :-\t";
						 if(tempvrchr==NULL)
						 {
							temptuple->vrchar = new tuple::VARCHAR2();
							tempvrchr = temptuple->vrchar;
						 }
						 else
						 {
							tempvrchr->nxt_vrchr = new tuple::VARCHAR2();
							tempvrchr = tempvrchr->nxt_vrchr;
						 }

						 tempvrchr->nxt_vrchr = NULL;
						 flushall();
						 gets(tempvrchr->vrchr);

						 break;

			case FLT: 	 cout<<" (DOUBLE) :-\t";
						 if(tempflt==NULL)
						 {
							temptuple->floate = new tuple::FLOAT();
							tempflt = temptuple->floate;
						 }
						 else
						 {
							tempflt->nxt_flt = new tuple::FLOAT();
							tempflt = tempflt->nxt_flt;
						 }

						 tempflt->nxt_flt = NULL;
						 cin>>tempflt->flt;

						 break;
		}
		cout<<"\n\n";
		field = field->nxt_vrchr;
	}while(field!=NULL);

	cout<<"\n\nVALUES INSERTED";
}

//UPDATE TABLE
void sql::update_table()
{

}

//DROP THE TABLE
void sql::drop_table()
{
	int arr[10],i;

	node *prevnode;
	node *tempnode = NULL;
	tuple *temptuple = NULL;

	tuple::VARCHAR2 *tempvrchr = NULL;
	tuple::NUMBER *tempnum = NULL;
	tuple::FLOAT *tempflt = NULL;

	tempnode = l1.head->nexttab;
	prevnode = l1.head;

	while(tempnode!=NULL)
	{
		if(!strcmpi(tempnode->tabname,tempstr))
			break;

		prevnode = prevnode->nexttab;
		tempnode = tempnode->nexttab;
	}

	if(tempnode==NULL)
	{
		cout<<"NO SUCH TABLE FOUND";
		return;
	}
	prevnode->nexttab = tempnode->nexttab;

	//////////TABLE FOUND /////////////

	temptuple = tempnode->t1->nexttuple;

	if(temptuple==NULL)
	{
		delete tempnode;
		return;
	}

	i=0;

	while(tempvrchr!=NULL)
	{
		cout<<strupr(tempvrchr->vrchr + 1);
		arr[i++] = tempvrchr->vrchr[0] - 48;

		tempvrchr = tempvrchr->nxt_vrchr;
		cout<<"\t\t";
	}
	arr[i]=-1;

	tempvrchr = temptuple->vrchar;
	tempflt = temptuple->floate;
	tempnum = temptuple->number;

	cout<<"\n";
	while(temptuple!=NULL)
	{
		i=0;
		cout<<"\n";
		while(arr[i]!=-1)
		{
			switch(arr[i++])
			{
				case NUM:	 cout<<tempnum->num;
							 tempnum = tempnum->nxt_num;
							 break;

				case VRCHAR: cout<<tempvrchr->vrchr;
							 tempvrchr = tempvrchr->nxt_vrchr;
							 break;

				case FLT: 	 cout<<tempflt->flt;
							 tempflt = tempflt->nxt_flt;
							 break;

			}
			cout<<"\t\t";
		}

		temptuple = temptuple->nexttuple;
		tempvrchr = temptuple->vrchar;
		tempflt = temptuple->floate;
		tempnum = temptuple->number;

	}
}



//ADD A NEW TABLE TO SQL
node* list_tab::addtab(char *name)
{
	node * temp;
	temp = head;
	while(temp->nexttab!=NULL)
		temp = temp->nexttab;

	temp->nexttab = new node(name);
	temp = temp->nexttab;

	return temp;
}
