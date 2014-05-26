//PROGRAM TO DO OPERATIONS ON THREADED BINARY TREE

#include<iostream.h>
#include<conio.h>

class node
{
	char data;
	node *left,*right;
	int lbit,rbit;
	int child;    //left->0............right->1

	public:
	node()
	{
		data = 0;
		left = NULL;
		right = NULL;
		lbit = 0;
		rbit = 0;
		child = -1;
	}

	friend class tbt;
};

class tbt
{
	node *root;

	public:
	tbt()
	{
		root = new node;
		root->left = root->right = root;
		root->lbit = 0;
		root->rbit = 1;
		root->data ='@';
	}

	void create(); //inorder creation
	void inorder();
	void preorder();
	void postorder();
	node* post_succ(node*);

};

int main()
{
	tbt t1;
	char dilemma;

	clrscr();

	t1.create();

	while(1)
	{
		clrscr();
		cout<<"\n\n\tOPERATIONS ON THREADED BINARY TREE\n";
		cout<<"\n\n1. INORDER TRAVERSAL\n\n2. PREORDER TRAVERSAL";
		cout<<"\n\n3. POSTORDER TRAVERSAL\n\n4. EXIT\n\n";
		cout<<"Enter Your Choice:-\t";
		cin>>dilemma;

		clrscr();

		switch(dilemma)
		{
			case '1': t1.inorder();
					  break;

			case '2': t1.preorder();
					  break;

			case '3': t1.postorder();
					  break;

			case '4': return 0;
			default: cout<<"ENTER PROPER CHOICE";
		}
		getch();
	}

}

//INORDER CREATION

void tbt::create()
{
	char dilemma;
	node *temp,*crnode;

	temp = root;

	do
	{
		while(1)
		{
			cout<<"\n\nWANNA ADD TO THE LEFT OF "<<temp->data<<" :-\t";
			cin>>dilemma;

			if(dilemma!='y' && dilemma!='Y')
				break;

			crnode = new node;
			cout<<"\n\nENTER DATA:-\t";
			cin>>crnode->data;

			crnode->child = 0;

			temp->lbit = 1;
			crnode->left = temp->left;
			crnode->right = temp;

			temp->left = crnode;
			temp = crnode;
		}

		while(temp!=root)
		{
			cout<<"\n\nWANNA ADD TO THE RIGHT OF "<<temp->data<<" :-\t";
			cin>>dilemma;

			if(dilemma=='y' || dilemma=='Y')
			{
				crnode = new node;
				cout<<"\n\nENTER DATA:-\t";
				cin>>crnode->data;

				crnode->child = 1;

				crnode->left = temp;
				crnode->right = temp->right;
				temp->rbit = 1;
				temp->right = crnode;
				temp = crnode;
				break;
			}
			temp = temp->right;
		}

	}while(temp!=root);

}

//INORDER TRAVERSAL

void tbt::inorder()
{
	node *temp;

	if(root->lbit==0)
	{
		cout<<"THE TREE IS EMPTY";
		return;
	}

	temp = root->left;

	do
	{
		while(1)
		{
			if(temp->lbit==0)
				break;
			temp = temp->left;
		}

		while(temp!=root)
		{
			cout<<temp->data<<",";

			if(temp->rbit)
			{
				temp = temp->right;
				break;
			}
			temp = temp->right;
		}

	}while(temp!=root);

	cout<<"\b ";
}



//PREORDER TRAVERSAL

void tbt::preorder()
{
	node *temp;

	if(root->lbit==0)
	{
		cout<<"THE TREE IS EMPTY";
		return;
	}

	temp = root->left;

	do
	{
		while(1)
		{
			cout<<temp->data<<",";

			if(temp->lbit==0)
				break;
			temp = temp->left;

		}

		while(temp!=root)
		{
			if(temp->rbit)
			{
				temp = temp->right;
				break;
			}
			temp = temp->right;
		}

	}while(temp!=root);

	cout<<"\b ";
}

//POSTORDER TRAVERSAL

void tbt::postorder()
{
	node *temp;

	if(root->lbit==0)
	{
		cout<<"THE TREE IS ABSENT";
		return;
	}

	temp = root;

	while(temp->rbit==1 || temp->lbit==1)   //search the element at the lowest level
	{
		if(temp->lbit==1)
			temp = temp->left;
		else
			temp = temp->right;
	}

	while(temp!=root->left)
	{
		cout<<temp->data<<",";

		temp = post_succ(temp);
	}
	cout<<temp->data;
}

//FUNCTION TO FIND THE POSTORDER SUCCESSOR
node* tbt::post_succ(node *temp)
{
	if(temp->child==1) //if it is a right child
	{
		while(temp->lbit)
			temp = temp->left;
		return(temp->left);
	}

	else   //it is a left child
	{
		while(temp->rbit)
			temp =  temp->right;
		temp = temp->right;

		if(temp->rbit==0)
			return temp;
		else
		{
			temp = temp->right;
			while(temp->rbit==1 || temp->lbit==1)
			{
				if(temp->lbit==1)
					temp = temp->left;
				else
					temp = temp->right;
			}
			return temp;

		}
	}

}