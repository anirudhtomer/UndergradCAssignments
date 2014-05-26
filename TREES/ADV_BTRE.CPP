//PROGRAM TO DO ADVANCED OPERATIONS ON BINARY TREE

#include<iostream.h>
#include<conio.h>

class node
{
	node *left,*right,*track;
	char data;

	public:
	node()
	{
		left = NULL;
		right = NULL;
		track = NULL;
		data = 0;
	}

	friend class stackk;
	friend class queuee;
	friend class btree;
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
		node *retpop;

		retpop = top;
		top = top->track;
		retpop->track = NULL;

		return retpop;

	}

	int empty()
	{
		if(top == NULL)
			return 1;
		return 0;
	}

	friend class btree;

};

class queuee
{
	node *front,*rear;

	public:
	queuee()
	{
		front = NULL;
		rear = 	NULL;
	}

	void insert(node *insnode)
	{
		if(front==NULL)
		{
			front = insnode;
			rear = insnode;
		}

		else
		{
			rear->track = insnode;
			rear = insnode;
		}
	}

	node* deleteee()
	{
		node *retnode;

		if(front == rear)
		{
			retnode = front;
			front = NULL;
			rear = NULL;
		}
		else
		{
			retnode = front;
			front = front->track;
		}
		retnode->track = NULL;

		return retnode;
	}

	int empty()
	{
		if(front==NULL)
			return 1;
		return 0;
	}
};

class btree
{
	node *root;
	stackk s1;
	queuee q1;

	public:
	btree()
	{
		root = NULL;
	}

	void mirr_other_rec(node*,node*);
	void mirr_other_nonrec();
	void mirr_same_rec(node*);
	void mirr_same_nonrec();
	void leafnoderec(node *,int);
	void leafnodenonrec();
	int depthrec(node*);
	void create();
	void depthnonrec();//postorder & bfs can do it....to practice postorder iam doing it
	void bfsprint();


	void leafnoderec()
	{
		if(root==NULL)
			cout<<"TREE IS EMPTY.... NO LEAF PRESENT YAAR";
		else
	   {
			cout<<"\n\nTHE LEAF NODES ARE::\n\n";
			leafnoderec(root,0);
			cout<<"\b ";
	   }
	}

	void depthrec()
	{
		cout<<"THE DEPTH OF THE TREE IS :-\t"<<depthrec(root);
	}

	void mirr_same_rec()
	{
		cout<<"THE MIRROR IMAGE OF THE TREE IS:-\t";
		mirr_same_rec(root);
		bfsprint();
	}

	void mirr_other_rec()
	{
		btree bo;
		bo.root = new node;

		cout<<"THE MIRRORED COPY OF THE TREE IS:-\t";
		mirr_other_rec(root,bo.root);

		bo.bfsprint();
		bo.leafnoderec(bo.root,1);  //to delete mirror image...to save memory

	}
};

int main()
{
	char chmnu;
	btree b1;

	clrscr();

	cout<<"DO YOU WANNA CREATE A TREE:-\t";
	cin>>chmnu;

	if(chmnu!='y' && chmnu!='Y')
		return 1;

	b1.create();

	while(1)
	{
		clrscr();

		cout<<"\n\n\t\tADVANCED OPERATIONS ON BINARY TREE\n";
		cout<<"\n\n1. LEAF NODES (recursive)\n\n2. LEAF NODES (non recursive)";
		cout<<"\n\n3. DEPTH (recursive)\n\n4. DEPTH (non recursive)";
		cout<<"\n\n5. BFS TRAVERSAL\n\n6. MIRROR IMAGE (same tree recursive)";
		cout<<"\n\n7. MIRROR IMAGE (same tree non recursive)\n\n";
		cout<<"8. MIRROR IMAGE (other tree recursive)\n\n";
		cout<<"9. MIRROR IMAGE (other tree non recursive)\n\n#. EXIT";

		cout<<"\n\nEnter Your Choice:-\t";
		cin>>chmnu;

		clrscr();

		switch(chmnu)
		{
			case '1': b1.leafnoderec();
					  break;

			case '2': b1.leafnodenonrec();
					  break;

			case '3': b1.depthrec();
					  break;

			case '4': b1.depthnonrec();
					  break;

			case '5': b1.bfsprint();
					  break;

			case '6': b1.mirr_same_rec();
					  break;

			case '7': b1.mirr_same_nonrec();
					  break;

			case '8': b1.mirr_other_rec();
					  break;

			case '9': b1.mirr_other_nonrec();
					  break;

			case '#': return 0;
			default: cout<<"ENTER PROPER CHOICE";
		}
		getch();
	}
}

//CREATE TREE NON RECURSIVELY

void btree::create()
{
	node *temp;
	char dilemma;

	temp = root = new node;

	cout<<"\n\nENTER DATA FOR ROOT NODE:-\t";
	cin>>temp->data;

	s1.pushit(temp);

	do
	{
		while(1)
		{
			cout<<"\n\nWANNA ADD TO THE LEFT OF "<<temp->data<<" :-\t";
			cin>>dilemma;

			if(dilemma!='y' && dilemma!='Y')
				break;

			temp->left = new node;
			temp = temp->left;

			cout<<"\n\nENTER DATA:-\t";
			cin>>temp->data;
			s1.pushit(temp);
		}

		while(!s1.empty())
		{
			temp = s1.popit();

			cout<<"\n\nWANNA ADD TO THE RIGHT OF "<<temp->data<<" :-\t";
			cin>>dilemma;

			if(dilemma=='y' || dilemma=='Y')
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

//LEAF NODES RECURSIVELY
void btree::leafnoderec(node *jade,int factor)
{
	if(!factor)
		if(jade->left==NULL && jade->right==NULL)
			cout<<jade->data<<",";

	if(jade->left!=NULL)
		leafnoderec(jade->left,factor);

	if(jade->right!=NULL)
		leafnoderec(jade->right,factor);

	if(factor)
	{
		delete(jade);
	}

}

//LEAF NODES.....NON RECURSIVE APPROACH
void btree::leafnodenonrec()
{
	node *temp;

	if(root==NULL)
	{
		cout<<"THE TREE IS EMPTY...no leaf nodes";
		return;
	}

	temp = root;

	s1.pushit(root);

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

			if(temp->left==NULL && temp->right==NULL)
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

//DEPTH RECURSIVE APPROACH
int btree::depthrec(node *jade)
{
	int depold = 0,depnew = 0;

	if(jade==NULL)
		return 0;

	if(jade->left!=NULL)
		depnew = depthrec(jade->left);

	if(depnew>depold)
		depold = depnew;

	if(jade->right!=NULL)
		depnew = depthrec(jade->right);

	if(depnew>depold)
		depold = depnew;

	return depold+1;

}

//DEPTH NON RECURSIVE APPROACH
void btree::depthnonrec()
{
	node *temp;
	int depvar =1,depmax = 1;  //depth is initially 1 because iam pushing root before any loop starts ...go to *******

	cout<<"THE DEPTH OF THE TREE IS:-\t";

	if(root==NULL)
	{
		cout<<"0";
		return;
	}

	temp = root;
	s1.pushit(temp);  //********* pushing root before any loop starts

	while(1)
	{
		while(1)
		{
			if(temp->left==NULL)
				break;
			temp = temp->left;
			s1.pushit(temp);
			depvar++;
		}

		if(depvar>depmax)
			depmax = depvar;

		while(s1.top->right==NULL || s1.top->right==temp)
		{
			temp = s1.popit();
			depvar--;
			if(s1.empty())
				break;
		}

		if(s1.empty())
			break;

		temp = s1.top->right;
		s1.pushit(temp);
		depvar++;

	}

	cout<<depmax;
}

//TO DO BFS TRAVERSAL
void btree::bfsprint()
{
	int i,prevcnt,prescnt;

	node *temp;

	if(root==NULL)
	{
		cout<<"THE TREE IS EMPTY";
		return;
	}

	temp = root;

	q1.insert(temp);
	prescnt = 1;

	while(!q1.empty())
	{
		cout<<"\b \n\n\t";
		prevcnt = prescnt;
		prescnt = 0;

		for(i=0;i<prevcnt;i++)
		{
			temp = q1.deleteee();

			cout<<temp->data<<",";

			if(temp->left!=NULL)
			{
				q1.insert(temp->left);
				prescnt++;
			}

			if(temp->right!=NULL)
			{
				q1.insert(temp->right);
				prescnt++;
			}
		}

	}
	cout<<"\b ";
}

//MIRROR IMAGE....SAME TREE...RECURSIVELY

void btree::mirr_same_rec(node *jade)
{
	node *temp;

	temp = jade->left;
	jade->left = jade->right;
	jade->right = temp;

	if(jade->left!=NULL)
		mirr_same_rec(jade->left);

	if(jade->right!=NULL)
		mirr_same_rec(jade->right);
}

//MIRROR IMAGE SAME TREE NON RECURSIVE

void btree::mirr_same_nonrec()  //preorder
{
	node *temp,*swapp;

	if(root==NULL)
	{
		cout<<"NO TREE PRESENT TO BE MIRRORED";
		return;
	}

	temp = root;
	s1.pushit(temp);

	do
	{
		while(1)
		{
			swapp = temp->left;
			temp->left=temp->right;
			temp->right=swapp;

			if(temp->left==NULL)
				break;
			temp = temp->left;
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

	cout<<"THE MIRROR IMAGE OF THE TREE IS::\n\n";
	bfsprint();
}
//MIRROR IMAGE ...OTHER TREE ...RECURSIVE

void btree::mirr_other_rec(node *jade1,node *jade2)
{
	jade2->data = jade1->data;

	if(jade1->left!=NULL)
	{
		jade2->right = new node;
		mirr_other_rec(jade1->left,jade2->right);
	}

	if(jade1->right!=NULL)
	{
		jade2->left = new node;
		mirr_other_rec(jade1->right,jade2->left);
	}


}

//MIRROR IMAGE OTHER TREE NON RECURSIVE

void btree::mirr_other_nonrec()
{
	stackk s2;
	btree bo;
	node *temp1,*temp2;

	if(root==NULL)
	{
		cout<<"EMPTY TREE ... MIRROR IMAGE CAN'T BE MADE";
		return;
	}

	bo.root = new node;
	temp2 = bo.root;

	temp1 = root;
	s1.pushit(temp1);
	s2.pushit(temp2);

	do
	{
		while(1)
		{
			temp2->data = temp1->data;

			if(temp1->left==NULL)
				break;

			temp2->right = new node;
			temp1 = temp1->left;
			temp2 = temp2->right;

			s1.pushit(temp1);
			s2.pushit(temp2);
		}

		while(!s1.empty())
		{
			temp1 = s1.popit();
			temp2 = s2.popit();

			if(temp1->right!=NULL)
			{
				temp1 = temp1->right;
				temp2->left = new node;
				temp2 = temp2->left;

				s1.pushit(temp1);
				s2.pushit(temp2);
				break;
			}
		}

	}while(!s1.empty());

	bo.bfsprint();
	bo.leafnoderec(bo.root,1);

}