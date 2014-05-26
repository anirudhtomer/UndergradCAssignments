//PROGRAM TO DO OPERATIONS ON A GRAPH

#include<iostream.h>
#include<conio.h>

class node
{
	int data;
	node *next,*track;

	public:
	node()
	{
		next = NULL;
		track = NULL;
		data = -1;
	}
	friend class graph;
	friend class stackk;
	friend class queuee;
};

class stackk
{
	node *top;

	public:
	stackk()
	{
		top = NULL;
	}

	void pushit(node *pusher)
	{
		pusher->track = top;
		top = pusher;
	}

	node *popit()
	{
		node *retpop;

		retpop = top;

		top = top->track;

		return retpop;

	}

	int empty()
	{
		if(top==NULL)
			return 1;
		return 0;
	}

};

class queuee
{
	node *front,*rear;

	public:
	queuee()
	{
		front = rear =NULL;
	}

	void insert(node *insnode)
	{
		if(front == NULL)
		{
			front = insnode;
			rear = insnode;
		}

		else
		{
			rear->track = insnode;
			rear = rear->track;
		}
	}

	node* deleteee()
	{
		node *retdel;

		retdel = front;

		if(front==rear)
		{
			front = NULL;
			rear = NULL;
		}
		else
			front = front->track;

		return retdel;
	}

	int empty()
	{
		if(front == NULL)
			return 1;
		return 0;
	}

};

class graph
{
	node *list;
	int numnode,*vertex;
	stackk s1;
	queuee q1;

	public:
	graph()
	{
		list = NULL;
		numnode = 0;
	}

	void create();
	void bfsprint();
	void dfsprintrec(node *);
	void dfsprintnonrec();

	void reset();

	void dfsprintrec()
	{
		if(!numnode)
			cout<<"THE GRAPH IS EMPTY";

		dfsprintrec(list);
		cout<<"\b ";
	}

};

int main()
{
	char chmnu;
	graph g1;

	clrscr();
	g1.create();

	while(1)
	{
		clrscr();
		cout<<"\n\n\t\tO P E R A T I O N S \tO N \tG R A P H\n";
		cout<<"\n\n1. BFS TRAVERSAL\n\n2. DFS TRAVERSAL (recursive)";
		cout<<"\n\n3. DFS TRAVERSAL (non recursive)\n\n4. EXIT";
		cout<<"\n\nEnter Your Choice:-\t";
		cin>>chmnu;

		g1.reset();
		clrscr();

		switch(chmnu)
		{
			case '1': g1.bfsprint();
					  break;

			case '2': g1.dfsprintrec();
					  break;

			case '3': g1.dfsprintnonrec();
					  break;

			case '4': return 0;
			default: cout<<"ENTER PROPER CHOICE";

		}
		getch();
	}

}

//CREATION OF A GRAPH

void graph::create()
{
	int i,j,cnt;

	node *temp;

	cout<<"ENTER THE NUMBER OF NODES:-\t";
	cin>>numnode;

	list = new node[numnode];

	for(i=0;i<numnode;i++)
	{
		temp = (list+i);
		temp->data = i;

		cout<<"\n\nENTER NUMBER OF NODES ADJACENT TO NODE \""<<temp->data<<" :-\t";
		cin>>cnt;

		cout<<"\n";

		for(j=0;j<cnt;j++)
		{
			temp->next = new node;
			temp = temp->next;
			cout<<"\nENTER ADJACENT NODE "<<j+1<<" :-\t";
			cin>>temp->data;
		}

	}

}

// BFS TRAVERSAL

void graph::bfsprint()
{
	node *temp;
	int i,prevcnt,prescnt;

	if(!numnode)
	{
		cout<<"NO ELEMENT PRESENT IN THE GRAPH";
		return;
	}

	temp = list;
	q1.insert(temp);
	vertex[temp->data]=1;

	prescnt = 1;

	while(!q1.empty())
	{
		prevcnt = prescnt;
		prescnt = 0;

		for(i=0;i<prevcnt;i++)
		{
			temp = q1.deleteee();

			cout<<temp->data<<",";

			while(temp->next!=NULL)
			{
				temp = temp->next;
				if(!vertex[temp->data])
				{
					q1.insert((list+temp->data));
					vertex[temp->data]=1;
					prescnt++;
				}
			}

		}
		cout<<"\b \n";
	}

}

//DFS PRINT RECURSIVE
void graph::dfsprintrec(node *liste)
{

	cout<<liste->data<<",";
	vertex[liste->data] = 1;

	while(liste->next!=NULL)
	{
		liste = liste->next;

		if(!vertex[liste->data])
			dfsprintrec(list+liste->data);
	}


}

//DFS PRINT NON RECURSIVE

void graph::dfsprintnonrec()
{
	node *temp;

	if(!numnode)
	{
		cout<<"THE GRAPH IS EMPTY";
		return;
	}

	temp = list;

	do
	{
		if(!vertex[temp->data])
		{
			cout<<temp->data<<",";
			vertex[temp->data] = 1;
		}

		temp = temp->next;

		while(temp!=NULL)
		{
			if(!vertex[temp->data])
			{
				s1.pushit(temp);
				temp = list + temp->data;
				break;
			}
			temp = temp->next;
		}

		if(temp==NULL)
			temp = s1.popit();

	}while(!s1.empty());

	cout<<"\b ";

}

//RESET VERTEX SET

void graph::reset()
{
	int i;

	for(i=0;i<numnode;i++)
		vertex[i] = 0;
}