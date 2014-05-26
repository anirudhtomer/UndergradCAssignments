//PROGRAM TO OPERATIONS ON A BINARY SEARCH TREE

#include<iostream.h>
#include<conio.h>

class node
{
	int data;
	node *left,*right;

	public:
	node()
	{
		left = NULL;
		right = NULL;
	}
	friend class bst;

};

class bst
{
	node *root;

	public:
	bst()
	{
		root = NULL;
	}

	~bst()
	{
		inorder(root,1);
	}


	void inorder(node*,int);
	int recsearch(node*,int);

	void create();
	void nonrecsearch();
	void deleteee();

	void inorder()
	{
		if(root==NULL)
		{
			cout<<"EMPTY.";
			return;
		}
		inorder(root,0);
		cout<<"\b ";
	}

	void recsearch()
	{
		int tar;
		cout<<"\n\nENTER THE ELEMENT TO BE SEARCHED:-\t";
		cin>>tar;

		cout<<"\n\nELEMENT "<<tar;

		tar = recsearch(root,tar);

		if(tar == -1)
			cout<<"\n\nNOT FOUND";
		else
			cout<<" FOUND AT LEVEL "<<tar;

	}
};


int main()
{
	char chmnu;
	bst b1;

	clrscr();

	cout<<"WANNA MAKE A BINARY SEARCH TREE:-\t";
	cin>>chmnu;

	if(chmnu!='y' && chmnu!='Y')
		return 1;

	b1.create();

	while(1)
	{
		clrscr();

		cout<<"\n\n\tB I N A  R Y\t S E R A C H\t T R E E\n";
		cout<<"\n\n1. RECURSIVE BSEARCH\n\n2. NON RECURSIVE BSEARCH";
		cout<<"\n\n3. DISPLAY\n\n4. DELETE\n\n5. EXIT";
		cout<<"\n\nEnter Your Choice:-\t";
		cin>>chmnu;

		clrscr();

		switch(chmnu)
		{
			case '1': b1.recsearch();
					  break;

			case '2': b1.nonrecsearch();
					  break;

			case '3': cout<<"THE TREE IS\n\n";
					  b1.inorder();
					  break;

			case '4': b1.deleteee();
					  break;

			case '5': return 0;

			default: cout<<"ENTER PROPER CHOICE";

		}

		getch();
	}

}

//CREATION

void bst::create()
{
	node *temp,*trav;
	char dilemma;

	temp = root = new node;
	cout<<"\n\nENTER DATA FOR ROOT NODE:-\t";
	cin>>temp->data;

	cout<<"\n\nWANNA ENTER MORE:-\t";
	cin>>dilemma;

	while(dilemma=='y'||dilemma=='Y')
	{
		temp = new node;
		cout<<"\n\nENTER DATA:-\t";
		cin>>temp->data;

		trav = root;

		while(1)
		{
			if(temp->data < trav->data)
			{
				if(trav->left==NULL)
				{
					trav->left = temp;
						break;
				}
				trav = trav->left;

			}

			if(temp->data > trav->data)
			{
				if(trav->right==NULL)
				{
					trav->right = temp;
						break;
				}
				trav = trav->right;
			}
		}

		cout<<"\n\nWANNA ENTER MORE:-\t";
		cin>>dilemma;

	}
}

// INORDER DISPLAY

void bst::inorder(node *jade,int factor)
{
	if(jade->left!=NULL)
		inorder(jade->left,0);

	cout<<jade->data<<",";

	if(jade->right!=NULL)
		inorder(jade->right,0);

	if(factor)
		delete(jade);
}

//RECURSIVE BSEARCH

int bst::recsearch(node *jade,int target)
{
	int depold = 0,depnew = 0;

	if(jade == NULL)
		return -1;

	if(jade->data == target)
		return depold+1;

	if(target < jade->data)
	{
		depnew = recsearch(jade->left,target);

		if(depnew > depold)
		{
			depold = depnew;
			return depold+1;
		}
	}

	else
	{
		depnew = recsearch(jade->right,target);

		if(depnew > depold)
		{
			depold = depnew;
			return depold+1;
		}
	}

	return -1;
}

//NON RECURSIVE SEARCH

void bst::nonrecsearch()
{
	node *temp;
	int target,cnt=0;

	cout<<"ENTER THE TARGET ELEMENT:-\t";
	cin>>target;

	temp = root;

	while(temp!=NULL)
	{
		if(target == temp->data)
		{
			cout<<"\n\nELEMENT "<<target<<" FOUND AT LEVEL "<<cnt+1;
			return;
		}

		if(target < temp->data)
			temp = temp->left;

		else
			temp = temp->right;

		cnt++;
	}

	cout<<"\n\nELEMENT "<<target<<" NOT FOUND";
}

//DELETION

void bst::deleteee()
{
	int target,flag=0;
	node *temp,*prev;

	if(root == NULL)
	{
		cout<<"\n\nTREE EMPTY CAN'T DELETE";
		return;
	}

	cout<<"\n\nENTER THE ELEMENT TO BE DELETED:-\t";
	cin>>target;

	temp = root;
	prev = NULL;

	while(temp!=NULL)
	{

		if(target == temp->data)
			break;

		prev = temp;

		if(target < temp->data)
			temp = temp->left;

		else
			temp = temp->right;

	}

	if(temp == NULL)
	{
		cout<<"\n\nELEMENT "<<target<<" IS NOT IN THE LIST";
		return;
	}

	else
	{
		cout<<"\n\nORIGINAL LIST::\n\n";
		inorder();
		cout<<"\n\n\nELEMENT "<<target<<" deleted successfully";
	}

	//ACTUAL DELETION

	// both child absent
	if(temp->right == NULL && temp->left == NULL)
	{
		if(prev==NULL) //root node
			root = NULL;

		else
		{
			if(temp == prev->left)
				prev->left = NULL;
			else
				prev->right =NULL;
		}

		flag = 1;
	}

	//both child

	if(temp->right != NULL && temp->left != NULL && flag!=1)
	{
		if(prev == NULL) //root node
		{
			temp = root->left;
			while(temp->right!=NULL)
				temp = temp->right;

			temp->right = root->right;

			temp = root;
			root->right = NULL;
			root = root->left;

		}

		else
		{
			if(temp == prev->left)
			{
				temp = temp->left;

				while(temp->right!=NULL)
					temp = temp->right;

				temp->right = prev->left->right;

				temp = prev->left;
				prev->left = temp->left;
			}

			else
			{
				temp = temp->left;

				while(temp->right!=NULL)
					temp = temp->right;

				temp->right = prev->right->right;

				temp = prev->right;
				prev->right = temp->left;
			}


		}

		flag = 1;
	}

	else if(flag!=1)//single child
	{
		if(prev == NULL)//root
		{
			if(temp->right!=NULL)
				root = temp->right;
			else
				root = temp->left;
		}

		else
		{
			if(prev->right==temp)
			{	
				if(temp->right!=NULL)
					prev->right = temp->right;
				else
					prev->right = temp->left;
			}

			else
			{
				if(temp->right!=NULL)
					prev->right = temp->right;
				else
					prev->right = temp->left;
				
			}
		}
	}

	delete(temp);

	cout<<"\n\n\nLIST AFTER DELETION::\n\n";
	inorder();
}