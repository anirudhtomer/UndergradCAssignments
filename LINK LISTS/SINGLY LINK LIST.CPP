// PROGRAM TO PERFORM OPERATIONS ON SINGLY LINK LIST

#include<iostream.h>
#include<conio.h>

class node
{
	node * next;
	int data;

	public:
	node()
	{
		next = NULL;
		data = 0;
	}
	friend class sll;

};

class sll
{
	node *head;

	public:

	//CONSTRUCTOR
	sll()
	{
		head = new node;
		head->data = 0;
	}

	//DESTRUCTOR
	~sll()
	{
		node *temp,*prev;

		temp = head;

		while(temp!=NULL)
		{
			prev = temp;
			temp = temp->next;

			delete(prev);
		}

	}

	//FUNCTIONS
	void create();
	void insert();
	void deleteee();
	void display();
	void sort();
	void revptr();
	void revdata();
	void concat(sll&);
	void merge1(sll&);       //ALLOCATION OF NEW NODES IS DONE
	void merge2(sll&);		 //WITHOUT ALLOCATING NEW NODES
};

int main()
{
	int chmnu;

	sll s1,s2;

	clrscr();

	s1.create();

	while(1)
	{
		clrscr();

		cout<<"\n\n\t\tS I N G L Y\t L I N K\t L I S T\n\n";
		cout<<"\n\n1.ADD ELEMENT\n\n2.DELETE ELEMENT\n\n3.DISPLAY LIST";
		cout<<"\n\n4.SORT BY POINTER SWAP\n\n5.REVERSE WITH POINTERS";
		cout<<"\n\n6.REVERSE BY DATA\n\n7.CONACTINATE\n\n8.MERGE";
		cout<<"\n\n9.EXIT\n\nEnter Your Choice:-\t";
		cin>>chmnu;

		clrscr();

		switch(chmnu)
		{
			case 1: s1.insert();
					break;

			case 2: s1.deleteee();
					break;

			case 3: s1.display();
					break;

			case 4: s1.sort();
					break;

			case 5: s1.revptr();
					break;

			case 6: s1.revdata();
					break;

			case 7: cout<<"ENTER THE DATA OF THE LIST TO BE CONCATINTED::\n\n";
					s2.create();
					clrscr();
					s1.concat(s2);
					break;

			case 8: cout<<"ENTER THE DATA FOR THE LIST TO BE MERGED::\n\n";
					s2.create();
					clrscr();
					s1.merge2(s2);
					break;

			case 9: return 0;

			default: cout<<"ENTER PROPER CHOICE";
		}

		getch();
	}

}

// CREATION

void sll::create()
{
	char dilemma;
	node *temp;

	temp = head;

	do
	{
		temp->next = new node;
		temp = temp->next;

		head->data++;

		cout<<"\n\nENTER DATA:-\t";
		cin>>temp->data;

		cout<<"\n\nWANNA ADD MORE:-\t";
		cin>>dilemma;


	}while(dilemma == 'Y' || dilemma == 'y');

}

//DISPLAY

void sll::display()
{
	int cnt = 1;
	node *temp;

	temp = head->next;

	if(temp==NULL)
	{
		cout<<"\n\nLIST IS EMPTY";
		return;
	}

	while(temp!=NULL)
	{
		cout<<"\n"<<cnt<<"\t"<<temp<<"\t"<<temp->data;
		cnt++;
		temp = temp->next;
	}

}

//INSERT

void sll::insert()
{
	int inspos,i;
	node *temp,*after;

	temp = head;
	after = head->next;

	display();

	do
	{
		cout<<"\n\nENTER THE POSITION AT WHICH YOU WANT TO INSERT:-\t";
		cin>>inspos;
	}while(inspos<1 || inspos>head->data+1);

	for(i=0;i<inspos-1;i++)
	{
		temp = temp->next;
		after = after->next;
	}

	temp->next = new node;
	temp = temp->next;
	temp->next = after;

	cout<<"\n\nENTER DATA YOU WANNA ADD:-\t";
	cin>>temp->data;

	head->data++;

	cout<<"\n\nDATA ADDED\n\n";

	display();

}

//DELETE

void sll::deleteee()
{
	int delpos,i;
	node *temp,*prev;

	temp = head->next;
	prev = head;

	if(temp == NULL)
	{
		cout<<"\n\nLIST EMPTY....CAN'T DELETE";
		return;
	}

	display();

	do
	{
		cout<<"\n\nENTER THE ELEMENT WHICH YOU WANNA DELETE:-\t";
		cin>>delpos;
	}while(delpos<1 || delpos >head->data);

	for(i=0;i<delpos-1;i++)
	{
		prev = prev->next;
		temp = temp->next;
	}

	prev->next = temp->next;

	head->data--;

	cout<<"\n\nELEMENT "<<temp->data<<" DELETED\n\n";

	delete(temp);

	display();

}

//SORT
void sll::sort()
{
	int i,j,num;

	node *temp,*prev;

	num = head->data;

	if(head->next== NULL)
	{
		cout<<"LIST IS EMPTY...CAN'T SORT";
		return;
	}

	cout<<"\n\nUNSORTED DATA\n";
	display();

	//bubble sort
	for(i=0;i<num-1;i++)
	{
		temp = head->next;
		prev = head;

		for(j=0;j<num-i-1;j++)
		{
			if(temp->data > temp->next->data )
			{
				prev->next = temp->next;
				temp->next = prev->next->next;

				prev->next->next =temp;
			}
			else
				temp = temp->next;

			prev = prev->next;
		}
	}

	cout<<"\n\nSORTED DATA\n";
	display();

}

//REVERSE BY POINTERS ........alpha/beta/gamma theory

void sll::revptr()
{
	node *alpha,*beta,*gamma;

	if(head->next == NULL)
	{
		cout<<"\n\nLIST IS EMPTY";
		return;
	}

	cout<<"\nORIGINAL LIST\n";
	display();

	alpha = head->next;
	beta = alpha->next;
	gamma = beta;

	while(gamma!=NULL)
	{
		gamma = gamma->next;

		beta->next = alpha;

		alpha = beta;
		beta = gamma;
	}

	head->next->next = NULL;
	head->next = alpha;

	cout<<"\n\nREVERSED LIST IS:-\t";
	display();
}

//REVERSE BY DATA........alpha/beta...theory........beta runs from head to toe;

void sll::revdata()
{
	int i,j;

	node *alpha,*beta;

	alpha = head;

	if(alpha ==  NULL)
	{
		cout<<"\n\nLIST IS EMPTY";
		return;
	}

	cout<<"\n\nORIGINAL DATA\n";
	display();

	for(i=0;i<head->data/2;i++)   //swap  first-last , second-secondlast, third-thirdlast.....(n/2-n/2  ||  n/2-n/2+1)
	{
		alpha = alpha->next;
		beta = head->next;

		for(j=i;j<head->data-1;j++)
			beta = beta->next;

		alpha->data ^= beta->data;
		beta->data ^= alpha->data;
		alpha->data ^= beta->data;
	}

	cout<<"\n\nREVERSED DATA\n";
	display();
}

//CONCAT

void sll::concat(sll &conlist)
{
	node *temp;

	temp = head;

	cout<<"\n\nTHE FIRST LIST IS::\n\n";
	display();

	cout<<"\n\nTHE SECOND LIST IS::\n\n";
	conlist.display();

	cout<<"\n\nPRESS ANY KEY TO CONCAT";
	getch();

	while(temp->next!=NULL)
		temp = temp->next;

	temp->next = conlist.head->next;

	conlist.head->next = NULL;
	conlist.head->data = 0;

	cout<<"\n\nTHE CONCATINATED LIST IS::\n\n";
	display();

}

//MERGE DATA  WITH THE ALLOCATION OF NEW NODES

void sll::merge1(sll &merglist)
{
	sll result;
	node *temp1,*temp2,*res;

	clrscr();

	cout<<"\n\nTHE FIRST LIST IS::\n";
	display();

	cout<<"\n\nTHE SECOND LIST IS::\n";
	merglist.display();

	cout<<"\n\nPRESS ANY KEY TO MERGE::";
	getch();

	sort();
	merglist.sort();

	clrscr();

	temp1 = head->next;
	temp2 = merglist.head->next;

	res = result.head;

	while(temp1!=NULL && temp2!=NULL)
	{
		res->next = new node;
		res = res->next;

		if(temp1->data < temp2->data)
		{
			res->data = temp1->data;
			temp1 = temp1->next;
		}

		else
		{
			res->data = temp2->data;
			temp2 = temp2->next;
		}

	}

	while(temp1!=NULL)
	{
		res->next = new node;
		res = res->next;

		res->data = temp1->data;
		temp1 = temp1->next;
	}

	while(temp2!=NULL)
	{
		res->next = new node;
		res = res->next;

		res->data = temp2->data;
		temp1 = temp2->next;
	}

	cout<<"THE MERGED LIST IS::\n";
	result.display();
}

//MERGE DATA WITHOUT ALLOCATION OF NEW NODES

void sll::merge2(sll &merglist)
{
	node *ptr1,*ptr2,*prev;

	clrscr();

	cout<<"\n\nTHE FIRST LIST IS::\n";
	display();

	cout<<"\n\nTHE SECOND LIST IS::\n";
	merglist.display();

	cout<<"\n\nPRESS ANY KEY TO MERGE::";
	getch();

	sort();
	merglist.sort();

	clrscr();

	ptr1 = head->next;
	ptr2 = merglist.head->next;
	prev = head;

	while(ptr1!=NULL && ptr2!=NULL)
	{

		if(ptr2->data < ptr1->data)
		{
			prev->next = ptr2;
			ptr2 = ptr2->next;
			prev->next->next = ptr1;

		}

		else
		{
			ptr1 = ptr1->next;
		}

		prev = prev->next;

	}

	if(ptr2!=NULL)
		prev->next = ptr2;

	cout<<"THE MERGED LIST IS::\n";
	display();
}

