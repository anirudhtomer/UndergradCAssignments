/* TO CREATE A TREE FROM A GIVEN
   preorder & inorder SEQUENCE */

#include<iostream.h>
#include<conio.h>

class node
{
	char data;
	node *left,*right;

	public:
	node()
	{
		data = '@';
		left = NULL;
		right = NULL;
	}

	friend class stackk;
	friend class btree;
};

class array
{
	char *arr;
	array *down;

	public:
	array()
	{
		arr  = NULL;
		down = NULL;
	}

	friend class stackk;
	friend class btree;
};


class stackk
{
	array *top;

	public:
	stackk()
	{
		top = NULL;
	}

	int empty()
	{
		if(top==NULL)
			return 1;
		return 0;
	}

	void pushit(array *psharr)
	{
		psharr->down = top;
		top = psharr;
	}

	array* popit()
	{
		array *retpop;

		retpop = top;
		top = top->down;

		retpop->down = NULL;
		return retpop;
	}

};

class btree
{
	node *root;

	char *oriprearr,*oriinarr;
	array *tempprearr,*tempinarr;

	int n;
	const int LEFT,RIGHT;

	stackk s1;

	public:
	btree():LEFT(48),RIGHT(49)
	{
		n = 0;

		root = new node;

		oriprearr = NULL;
		oriinarr = NULL;

		tempprearr = NULL;
		tempinarr = NULL;

	}

	~btree()
	{
		delete []tempprearr->arr;
		delete []tempinarr->arr;

		delete tempprearr;
		delete tempinarr;

		delete []oriprearr;
		delete []oriinarr;
	}

	void enter();
	void inorder(node*);
	void conversion();
	node* search(char,node*);

	void inorder()
	{
		inorder(root);
		cout<<"\b ";
	}
};


int main()
{
	btree b1;

	clrscr();

	b1.enter();
	b1.conversion();


	getch();

	clrscr();

	cout<<"THE CONVERTED TREE IS (inorder):-\t";
	b1.inorder();

	getch();
	return 0;

}

//ENTER THE PREORDER & INORDER ARRAYS

void btree::enter()
{
	int i;

	cout<<"\n\nENTER THE NUMBER OF NODES IN THE ARRAY:-\t";
	cin>>n;

	oriprearr = new char[n+1];
	oriinarr = new char[n+1];

	tempprearr = new array;
	tempinarr = new array;

	tempprearr->arr = new char[n+1];
	tempinarr->arr = new char[n+2];

	cout<<"\n\nENTER THE PREORDER TRAVERSAL:-\t";
	cin>>oriprearr;

	for(i=0;i<=n;i++)
		*(tempprearr->arr + i) = *(oriprearr+i);

	cout<<"\n\nENTER THE INORDER TRAVERSAL:-\t";
	cin>>oriinarr;

	tempinarr->arr[0] = LEFT;

	for(i=0;i<=n;i++)
		tempinarr->arr[i+1] = *(oriinarr+i);

}

//CONVERSION TO A TREE

void btree::conversion()
{
	int i,j;
	int cnt = 0,pcnt = 0,clcnt = 0 ,crcnt = 0;
	array *parent[5],*cleft[5],*cright[5];
	node *temp;

	temp = root;

	for(i=0;i<5;i++)
	{
		parent[i] = new array;
		cleft[i] = new array;
		cright[i] = new array;

		cleft[i]->arr = new char[20];
		cright[i]->arr = new char[20];
		parent[i]->arr = new char[2];


		*( (*(cleft+i))->arr + 0) = LEFT;  //cleft[i]->arr[0]
		cright[i]->arr[0] = RIGHT;
		parent[i]->arr[0] = root->data;
		parent[i]->arr[1] = '\0';

	}

	s1.pushit(tempinarr);
	clcnt++;
	s1.pushit(parent[pcnt++]);

	while(!s1.empty())
	{
		parent[--pcnt] = s1.popit();
		tempinarr = s1.popit();

		if(tempinarr->arr[0]==LEFT)
			clcnt--;
		else
			crcnt--;

		temp = search(parent[pcnt]->arr[0],root);

		if(tempinarr->arr[0] == LEFT)
		{
			temp->left = new node;
			temp->left->data = tempprearr->arr[cnt++];
			temp = temp->left;
		}

		else
		{
			temp->right = new node;
			temp->right->data = tempprearr->arr[cnt++];
			temp = temp->right;
		}

		for(i=1;tempinarr->arr[i]!=temp->data;i++)
			cleft[clcnt]->arr[i] = tempinarr->arr[i];

		cleft[clcnt]->arr[i] = '\0';

		for(i++,j=1;tempinarr->arr[i]!='\0';i++,j++)
			cright[crcnt]->arr[j] = tempinarr->arr[i];

		cright[crcnt]->arr[j] = '\0';

		if(cright[crcnt]->arr[1] != '\0')
		{
			parent[pcnt]->arr[0] = temp->data;
			s1.pushit(cright[crcnt++]);
			s1.pushit(parent[pcnt++]);
		}

		if(cleft[clcnt]->arr[1] != '\0')
		{
			parent[pcnt]->arr[0] = temp->data;
			s1.pushit(cleft[clcnt++]);
			s1.pushit(parent[pcnt++]);
		}

	}

	temp = root;
	root = root->left;

	delete(temp);

	for(i=0;i<5;i++)
	{
		delete []parent[i]->arr;
		delete []cleft[i]->arr;
		delete []cright[i]->arr;

		delete parent[i];
		delete cleft[i];
		delete cright[i];
	}

}

//INORDER TRAVERSAL TO CHECK THE RESULT

void btree::inorder(node *jade)
{
	if(jade->left!=NULL)
		inorder(jade->left);

	cout<<jade->data<<",";

	if(jade->right!=NULL)
		inorder(jade->right);

}

//SEARCH

node* btree::search(char tar,node *jade)
{

	if(tar == jade->data)
		return jade;

	if(jade->left!=NULL)
		search(tar,jade->left);

	if(jade->right!=NULL)
		search(tar,jade->right);

}
