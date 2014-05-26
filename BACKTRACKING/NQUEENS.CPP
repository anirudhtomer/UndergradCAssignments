// N Queens Problem

#include<iostream.h>
#include<conio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

class NQueen{

	int	boardsize,top;
	int *columnofqueen;

	struct stack{
		int colno,qno;
	}*queenstack;

	public:
	NQueen(){
		top=-1;
		queenstack = (struct stack *) (malloc(sizeof(struct stack)*50));
	}

	void init(int);
	void RecNQueens(int);
	void NonRecNQueens();
	int tryPlacingQueen(int,int);
	void printBoard(int,int);

	void push(struct stack *ele){
		top++;
		(queenstack + top)->colno = ele->colno;
		(queenstack + top)->qno = ele->qno;
	}

	struct stack * pop(){
		struct stack *ret = (struct stack*) (malloc(sizeof(struct stack)));

		ret->colno = (queenstack + top)->colno;
		ret->qno = (queenstack + top)->qno;

		top--;

		return ret;
	}

};

//i th queen is supposed to be in ith column

int main(){

	int n;
	NQueen *n1;

	clrscr();

	cout<<"Enter the number of the queens:-\t";
	cin>>n;

	n1 = new NQueen();

	cout<<"\n\nRECURSIVE METHOD ABOUT TO START...Press any key\n";
	getch();
	n1->init(n);
	n1->RecNQueens(0);  //start by placing first queen i.e 0th queen

	cout<<"\n\nNON RECURSIVE METHOD ABOUT TO START..Press any key";
	getch();
	n1->init(n);
	n1->NonRecNQueens();

	cout<<"\n\nProgram Over..Press any key to exit";
	getch();
	return 0;
}

void NQueen::init(int n){

	int i;

	boardsize = n;
	columnofqueen = new int[n];

	for(i=0;i<boardsize;i++){
		columnofqueen[i] =  -1;
	}
}

int NQueen::tryPlacingQueen(int queennumber,int columnnumber){

	int i;

	/*
		for nth queen I have to check whether its position is conflicting with all previous queens

		condition for two queens to be in same diagonal:

		let r1,c1 & r2,c2 be the row & column positions for two queens

		then if
				|r1-r2| = |c1-c2| then they are in same diagonal
	*/

	for(i=0;i<queennumber;i++){

		if( (columnofqueen[i] == columnnumber) || (  abs(i-queennumber) == abs(columnofqueen[i]-columnnumber) ) )
			return FALSE;
	}

	return TRUE;
}

void NQueen::NonRecNQueens(){

	int columnnumber,queennumber;
	struct stack *s1;

	s1 = (struct stack *) (malloc(sizeof(struct stack)));

	s1->qno = 0;
	s1->colno = 0;

	push(s1);
	while(top!=-1){

		s1 = pop();
		queennumber =  s1->qno;
		columnnumber = s1->colno;

		printBoard(queennumber,columnnumber);
		columnnumber = columnnumber;

		for( /*already initialized above*/ ; columnnumber < boardsize ; columnnumber++ ){

			if(tryPlacingQueen(queennumber,columnnumber)==TRUE){

				columnofqueen[queennumber] = columnnumber;

				if(queennumber==boardsize-1){
					textcolor(LIGHTBLUE);
					printBoard(queennumber,columnnumber);
					getch();
					textcolor(WHITE);
				}
				else{
					s1->qno = queennumber;
					s1->colno = columnnumber + 1;
					push(s1);

					s1->qno = queennumber + 1;
					s1->colno = 0;
					push(s1);

					break;
				}
			}
			printBoard(queennumber,columnnumber);
		}
	}
}

void NQueen::RecNQueens(int queennumber){

	int columnnumber;

	printBoard(queennumber,-1);
  //	getch();

	for( columnnumber=0 ; columnnumber < boardsize ; columnnumber++ ){

		if(tryPlacingQueen(queennumber,columnnumber)==TRUE){

			columnofqueen[queennumber] = columnnumber;

			if(queennumber==boardsize-1){
				textcolor(LIGHTBLUE);
				printBoard(queennumber,columnnumber);
				getch();
				textcolor(WHITE);
			}
			else
				RecNQueens(queennumber + 1); //try for the next queen
		}
		printBoard(queennumber,columnnumber);
//		getch();
	}

}

void NQueen::printBoard(int qno,int colno){

	int i,j;

	//I used cprintf so that the color set for showing goal gets applied
	cprintf("\nQueen Number:-     %d",qno);

	if(colno==-1)
		cout<<"\nColumn Number tried:-\tJust Started";
	else
		cout<<"\nColumn Number tried:-\t"<<colno;


	cout<<"\n\n  \t";
	for(i=0;i<boardsize;i++){
		cout<<"C"<<i<<"\t";
	}

	cout<<"\n";

	for(i=0;i<boardsize;i++){

		cout<<"R"<<i<<"\t";

		for(j=0;j<boardsize;j++){
			if(columnofqueen[i]==j)
				cprintf("%d",i);
			else
				cprintf("-");
			cout<<"\t";

		}
		cout<<"\n";
	}
}