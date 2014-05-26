//PROGRAM TO DO OPEARTIONS ON A BINARY TREE NON RECURSIVELY

#include<iostream.h>
#include<conio.h>

class node
{
	char data;
	node *left,*right,*track;

	public:
	node()
	{
		left = NULL;
		right = NULL;
		track = NULL;
	}

	friend class btree;
	friend class stackk;

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

	node* popit()
	{
		node *retnode;

		retnode = top;
		top = top->track;
		retnode->track = NULL;

		return retnode;
	}

	int empty()
	{
		if(top==NULL)
			return 1;
		return 0;
	}

	friend class btree;
};


class btree
{
	node *root;
	stackk s1;

	public:
	btree()
	{
		root = NULL;
	}

	void createnonrec();
	void inordernonrec();
	void preordernonrec();
	void postordernonrec();

};

int main()
{
	char chmnu;
	btree b1;

	cout<<"WANNA create A TREE:-\t";
	cin>>chmnu;

	if(chmnu!='y' && chmnu!='Y')
		return 1;

	b1.createnonrec();

	while(1)
	{
		clrscr();
		cout<<"\n\n\t\tBINARY TREE NON RECURSIVE ALGORITHM\n";
		cout<<"\n\n1. inorder nonrec TRAVERSAL\n\n2. preorder nonrec TRAVERSAL";
		cout<<"\n\n3. postorder nonrec TRAVERSAL\n\n4. EXIT";
		cout<<"\n\nEnter Your Choice:-\t";
		cin>>chmnu;

		clrscr();

		switch(chmnu)
		{
			case '1': b1.inordernonrec();
					  break;

			case '2': b1.preordernonrec();
					  break;

			case '3': b1.postordernonrec();
					  break;

			case '4': return 0;

			default: cout<<"ENTER PROPER CHOICE!!!";

		}
		getch();
	}

}

//NON RECURSIVE CREATION

void btree::createnonrec()
{
	char dilemma;
	node *temp;

	root = new node;

	cout<<"\n\nENTER DATA FOR ROOT NODE:-\t";
	cin>>root->data;

	temp = root;
	s1.pushit(temp);

	do
	{

		while(1)
		{
			cout<<"\n\nWANNA ADD TO THE LEFT OF "<<temp->data<<" :-\t";
			cin>>dilemma;

			if(dilemma == 'y' ||dilemma == 'Y')
			{
				temp->left = new node;
				temp = temp->left;

				cout<<"\n\nENTER DATA:-\t";
				cin>>temp->data;
				s1.pushit(temp);
			}

			else
				break;
		}

		while(!s1.empty())
		{
			temp =  s1.popit();

			cout<<"\n\nWANNA ADD TO THE RIGHT OF "<<temp->data<<" :-\t";
			cin>>dilemma;

			if(dilemma == 'y' || dilemma == 'Y')
			{
				temp->right = new node;
				temp = temp->right;

				cout<<"\n\nENTER DATA:-\t";
				cin>>temp->data;

				s1.pushit(temp);
				break;
			}
		}

	}while(!s1.empty());


}

//NON RECURSIVE inordernonrec TRAVERSAL

void btree::inordernonrec()
{
	node *temp;

	if(root==NULL)
	{
		cout<<"\n\nTHE TREE IS EMPTY";
		return;
	}

	temp = root;
	s1.pushit(temp);

	do
	{
		while(1)
		{
			if(temp->left==NULL)
				break;

			temp = temp->left;
			s1.pushit(temp);

		}

		while(!s1.empty())
		{
			temp = s1.popit();

			cout<<temp->data<<",";

			if(temp->right!=NULL)
			{
				temp = temp->right;
				s1.pushit(temp);
				break;
			}
		}

	}while(!s1.empty());

	cout<<"\b ";

}

//NON RECURSIVE preordernonrec TRAVERSAL
void btree::preordernonrec()
{
	node *temp;

	if(root==NULL)
	{
		cout<<"THE TREE IS EMPTY";
		return;
	}

	temp = root;
	s1.pushit(temp);

	do
	{
		while(1)
		{
			cout<<temp->data<<",";

			if(temp->left==NULL)
				break;

			temp = temp->left;
			s1.pushit(temp);
		}

		while(!s1.empty())
		{
			temp = s1.popit();

			if(temp->right!=NULL)
			{
				temp = temp->right;
				s1.pushit(temp);
				break;
			}
		}


	}while(!s1.empty());

	cout<<"\b ";

}

//NON RECURSIVE postordernonrec TRAVERSAL

void btree::postordernonrec()
{
	node *temp;

	if(root==NULL)
	{
		cout<<"THE TREE IS EMPTY";
		return;
	}

	temp = root;
	s1.pushit(temp);

	while(1)
	{
		while(1)
		{
			if(temp->left==NULL)
				break;
			temp = temp->left;

			s1.pushit(temp);
		}

		while(s1.top->right == NULL || s1.top->right == temp)
		{
			temp = s1.popit();

			cout<<temp->data<<",";

			if(s1.empty())
				break;
		}

		if(s1.empty())
			break;

		temp = s1.top->right;
		s1.pushit(temp);

	}
	cout<<"\b ";
}
