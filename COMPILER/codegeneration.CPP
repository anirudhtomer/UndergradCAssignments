//Program for Code Generation

#include<iostream.h>
#include<conio.h>
#include<alloc.h>

#define LEFT 0
#define RIGHT 1

struct node{
	int label;
	char name;
	struct node *left,*right;
};

class CodeGen{

	int codelen;
	int regcount,tempregcount;
	int regstacktop,tempregstacktop;

	struct node *root;
	int *regstack,*tempregstack;

	struct{
		char lhs;
		char operatr;
		char operand1;
		char operand2;
	}tac[10];

	public:
	void getInput();
	void makeDAG(struct node*,int);
	void labelDAG(struct node*,int);

	void generateCode(struct node*,int);

	struct node* getRoot(){
		return root;
	}

	void pushtempreg(int reg){
		tempregstacktop++;
		tempregstack[tempregstacktop] = reg;
	}

	int poptempreg(){
		tempregstacktop--;

		return tempregstack[tempregstacktop + 1];
	}

	void pushreg(int reg){
		regstacktop++;
		regstack[regstacktop] = reg;
	}

	int popreg(){
		regstacktop--;

		return regstack[regstacktop + 1];
	}


};

int main(){

	CodeGen *c1 = new CodeGen();

	c1->getInput();
	cout<<"\n\nTHE ASSEMBLY CODE IS:\n";
	c1->generateCode(c1->getRoot(),LEFT);

	return 0;
}

void CodeGen::generateCode(struct node* parent,int lr){

	int reg,tempreg;

	if(parent->left==NULL && parent->right==NULL && lr==LEFT){
		cout<<"\n"<<"MOV "<<parent->name<<" , R"<<regstack[regstacktop];
	}

	else{

		if(parent->right->label == 0){
			generateCode(parent->left,LEFT);

			switch(parent->name){

				case '+': 	cout<<"\n"<<"ADD "<<parent->right->name<<" , "<<"R"<<regstack[regstacktop];
							break;

				case '-':	cout<<"\n"<<"SUB "<<parent->right->name<<" , "<<"R"<<regstack[regstacktop];
							break;

				case '*':   cout<<"\n"<<"MUL "<<parent->right->name<<" , "<<"R"<<regstack[regstacktop];
							break;

				case '/':   cout<<"\n"<<"DIV "<<parent->right->name<<" , "<<"R"<<regstack[regstacktop];
							break;
			}

			return;
		}

		if(parent->left->label >= regcount && parent->right->label >= tempregcount){

			generateCode(parent->right,RIGHT);
			tempreg = poptempreg();

			cout<<"\n"<<"MOV R"<<regstack[regstacktop]<<" , "<<"T"<<tempreg;

			generateCode(parent->left,LEFT);

			switch(parent->name){

				case '+': 	cout<<"\n"<<"ADD T"<<tempreg<<" , "<<"R"<<regstack[regstacktop];
							break;

				case '-':	cout<<"\n"<<"SUB T"<<tempreg<<" , "<<"R"<<regstack[regstacktop];
							break;

				case '*':   cout<<"\n"<<"MUL T"<<tempreg<<" , "<<"R"<<regstack[regstacktop];
							break;

				case '/':   cout<<"\n"<<"DIV T"<<tempreg<<" , "<<"R"<<regstack[regstacktop];
							break;
			}

			pushtempreg(tempreg);

			return;
		}

		if(parent->right->label > parent->left->label){

			regstack[regstacktop] ^= regstack[regstacktop-1];
			regstack[regstacktop-1] ^= regstack[regstacktop];
			regstack[regstacktop] ^= regstack[regstacktop-1];

			generateCode(parent->right,RIGHT);
			reg = popreg();

			generateCode(parent->left,LEFT);

			switch(parent->name){

				case '+': 	cout<<"\n"<<"ADD R"<<reg<<" , "<<"R"<<regstack[regstacktop];
							break;

				case '-':	cout<<"\n"<<"SUB R"<<reg<<" , "<<"R"<<regstack[regstacktop];
							break;

				case '*':   cout<<"\n"<<"MUL R"<<reg<<" , "<<"R"<<regstack[regstacktop];
							break;

				case '/':   cout<<"\n"<<"DIV R"<<reg<<" , "<<"R"<<regstack[regstacktop];
							break;
			}


			pushreg(reg);

			regstack[regstacktop] ^= regstack[regstacktop-1];
			regstack[regstacktop-1] ^= regstack[regstacktop];
			regstack[regstacktop] ^= regstack[regstacktop-1];

			return;
		}

		if(parent->right->label == parent->left->label){

			generateCode(parent->left,LEFT);

			reg = popreg();

			generateCode(parent->right,RIGHT);

			switch(parent->name){

				case '+': 	cout<<"\n"<<"ADD R"<<regstack[regstacktop]<<" , "<<"R"<<reg;
							break;

				case '-':	cout<<"\n"<<"SUB R"<<regstack[regstacktop]<<" , "<<"R"<<reg;
							break;

				case '*':   cout<<"\n"<<"MUL R"<<regstack[regstacktop]<<" , "<<"R"<<reg;
							break;

				case '/':   cout<<"\n"<<"DIV R"<<regstack[regstacktop]<<" , "<<"R"<<reg;
							break;
			}

			pushreg(reg);

			return;
		}

	}
}

//get input as TAC & convert to a DAG & label the tree
void CodeGen::getInput(){

	int i;

	cout<<"\nEnter the number of registers that can be used:-\t";
	cin>>regcount;

	regstack = new int[regcount];

	cout<<"\n\nEnter the number of temporary registers that can be used:-\t";
	cin>>tempregcount;

	tempregstack = new int[tempregcount];

	//initialize regstack
	regstacktop = regcount-1;
	for(i=regcount-1;i>=0;i--)
		regstack[i] = (regcount-1) - i;

	//initialize tempregstack
	tempregstacktop = tempregcount-1;
	for(i=tempregcount-1;i>=0;i--)
		tempregstack[i] = (tempregcount-1) - i;

	cout<<"\n\nEnter the three address code (\"# = # # #\" for ending )\n\n";

	codelen = 0;
	while(1){

		cin>>tac[codelen].lhs>>"=">>tac[codelen].operand1>>tac[codelen].operatr>>tac[codelen].operand2;

		if(tac[codelen].lhs == '#')
			break;

		codelen += 1;
	}

	root = (struct node*) malloc(sizeof(struct node));

	makeDAG(root,codelen-1);

	cout<<"\n\nTHE LABELLED TREE IS :\n";

	labelDAG(root,LEFT);

}

//label DAG
void CodeGen::labelDAG(struct node* parent,int lr){

	if(parent->left!=NULL && parent->right!=NULL){
		labelDAG(parent->left,LEFT);
		labelDAG(parent->right,RIGHT);

		if(parent->left->label == parent->right->label)
			parent->label = parent->left->label + 1;
		else
			parent->label = parent->left->label > parent->right->label ? parent->left->label : parent->right->label;
	}
	else{ //leaf node
		if(lr==LEFT)
			parent->label = 1;
		else
			parent->label = 0;
	}

	cout<<"\nlabel ( "<<parent->name<<" ) = "<<parent->label;

}

//create DAG from TAC
void CodeGen::makeDAG(struct node* parent,int level){

	int i;
	int levelleft,levelright;

	parent->name = tac[level].operatr;

	levelleft = -1;
	levelright = -1;

	for(i=level-1;i>=0;i--){

		if(levelleft==-1 && tac[level].operand1==tac[i].lhs)
			levelleft = i;

		if(levelright==-1 && tac[level].operand2==tac[i].lhs)
			levelright = i;

	}

	parent->left = (struct node*) malloc(sizeof(struct node));
	parent->right = (struct node*) malloc(sizeof(struct node));

	if(levelleft!=-1)
		makeDAG(parent->left,levelleft);

	else{
		parent->left->name = tac[level].operand1;
		parent->left->left = NULL;
		parent->left->right = NULL;
	}

	if(levelright!=-1)
		makeDAG(parent->right,levelright);

	else{
		parent->right->name = tac[level].operand2;
		parent->right->left = NULL;
		parent->right->right = NULL;
	}

}