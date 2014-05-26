//Graph Coloring Problem

#include<iostream.h>
#include<conio.h>
#include<stdlib.h>

#define EDGE 1
#define NOEDGE 0

#define NOCOLOR 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4

//any graph coloring problem in the world can be solved by at most 4 colors
struct stack{
	int vertexno;
	int colorno;
};

class GColor{

	int top;
	int vertexcount,colorcount;
	int graph[15][15];
	int *colorofvertex;

	struct stack *colorstack;

	public:

	GColor(){
		top = -1;
		colorstack = (struct stack *) (malloc(sizeof(struct stack)*50));
	}

	void getData();
	void RecGcolor(int);
	void NonRecGcolor();
	void selectNextColor(int);
	void printStat(int);

	void push(struct stack *ele){

		top++;

		(colorstack + top)->colorno = ele->colorno;
		(colorstack + top)->vertexno = ele->vertexno;

	}

	struct stack * pop(){

		struct stack *ret = (struct stack*) (malloc(sizeof(struct stack)));

		ret->colorno = (colorstack + top)->colorno;
		ret->vertexno = (colorstack + top)->vertexno;

		top--;

		return ret;
	}

};

int main(){

	GColor *g1 = new GColor();

	clrscr();

	g1->getData();

	cout<<"\n\nRecursive Method Starting...Press any key";
	getch();
	g1->RecGcolor(0);
	getch();

	cout<<"\n\nNon Recursive Method starting..Press any key";
	getch();
	g1->NonRecGcolor();
	cout<<"\n\nProgram Over...";

	getch();
	return 0;
}


void GColor::selectNextColor(int vertexnumber){

	int i;

	printStat(vertexnumber);

	while(1){

		colorofvertex[vertexnumber] = (colorofvertex[vertexnumber]+1) % (colorcount+1);

		/*
			another method to solve the problem can be
			initializing colorvertex[i]=0 before u call recgcolor for it
			and not using the % operator here....& checking

			colorofvertex[i] > colorcount instead of checking colorofvertex[i]=0
			since we have used % op to set it to zero ..that's why we check for 0
			& the hidden advantage is that color get initialized to 0...i.e null as well

			I know I am talking weird but ya that is the next best solution
		*/
		if(colorofvertex[vertexnumber]==NOCOLOR)
			break;

		for(i=0;i<vertexcount;i++){

			if(graph[i][vertexnumber]==EDGE && colorofvertex[i]==colorofvertex[vertexnumber])
				break;
		}

		if(i==vertexcount) //all vertices have been checked and the selected color does not conflict
			break;
	}

}

void GColor::NonRecGcolor(){

	struct stack *s1 = (struct stack*) (malloc(sizeof(struct stack)));
	int vertexnumber;

	s1->colorno = NOCOLOR;
	s1->vertexno = 0;

	push(s1);

	while(top!=-1){

		s1 = pop();

		vertexnumber = s1->vertexno;
		colorofvertex[vertexnumber] = s1->colorno;

		while(1){

			selectNextColor(vertexnumber);

			if(colorofvertex[vertexnumber]==NOCOLOR)
				break;

			if(vertexnumber==vertexcount-1){

				textcolor(BLUE);
				printStat(vertexnumber);
				getch();
				textcolor(WHITE);

			}
			else{

				s1->vertexno = vertexnumber;
				s1->colorno = colorofvertex[vertexnumber];
				push(s1);

				s1->vertexno = vertexnumber + 1;
				s1->colorno = colorofvertex[vertexnumber + 1];
				push(s1);

				break;

			}
		}
	}

}

void GColor::RecGcolor(int vertexnumber){

	while(1){
		selectNextColor(vertexnumber);

		if(colorofvertex[vertexnumber]==NOCOLOR)
			break;

		if(vertexnumber==vertexcount-1){

			textcolor(BLUE);
			printStat(vertexnumber);
			getch();
			textcolor(WHITE);

		}

		else
			RecGcolor(vertexnumber+1);
	}

}

void GColor::printStat(int k){

	int i;

	cprintf("\n\nNode Number:-    %d",k);

	cout<<"\n\n";
	for(i=0;i<vertexcount;i++){
			cout<<"Vertex "<<i<<"'s Color :-\t";

			switch(colorofvertex[i]){

				case NOCOLOR: cout<<"--------";
								break;

				case RED:  		cout<<"RED";
								break;

				case GREEN:     cout<<"GREEN";
								break;

				case BLUE:      cout<<"BLUE";
								break;

				case YELLOW:    cout<<"YELLOW";
								break;

			}
			cout<<"\n";
	}
}

void GColor::getData(){

	int i,j;

	cout<<"Enter the number of colors:-\t";
	cin>>colorcount;

	cout<<"\n\nEnter the number of vertices:-\t";
	cin>>vertexcount;

	colorofvertex = new int[vertexcount];

	cout<<"\n\nEnter the adjancency matrix( 1 for edge / 0 for no edge ):-\n";

	for(i=0;i<vertexcount;i++){

		colorofvertex[i]=NOCOLOR;
		for(j=0;j<vertexcount;j++){
			cin>>graph[i][j];
		}
	}

}
