//MULTISTAGE GRAPH

#include<iostream.h>
#include<conio.h>

#define INFINITY 10000

class Multistage{

	int graph[30][30];

	int vertexcount,stagecount;

	int *costofvertex,*vertexforstage,*nearestvertex;

	public:

	void getInput();
	void forwardApproach();
	void backwardApproach();
};


int main(){

	Multistage *m1 = new Multistage();

	clrscr();

	m1->getInput();
	cout<<"\n\n*********SOLVING WITH FORWARD APPROACH*********\n\n";

	m1->forwardApproach();
	getch();

	cout<<"\n\n\n*********SOLVING WITH BACKWARD APPROACH*********\n\n";

	m1->backwardApproach();
	getch();

	return 0;
}

void Multistage::forwardApproach(){

	int currentvertex,i;
	int min,vertexnear;

	//in forward approach we start with the last vertex

	/*
		since I have n vertex from 0 to n-1..I call last vertex as n-1th
		we try to find the cost for every vertex....the last vertex "n-1 th"
		is supposed not to have to outgoing edge so its cost  = 0;
		& we compute cost for the left n-1 vertices in the loop

		finding the cost is the job of the algo...not ours..so we initialize it to infinity
		 & the nearest vertex to -1...hypothetical
	*/

	for(i=0;i<vertexcount;i++){
		costofvertex[i] = INFINITY;
		nearestvertex[i] = -1; //hypothetical vertex
	}


	costofvertex[vertexcount-1] = 0;

	for(currentvertex=vertexcount-2;currentvertex>=0;currentvertex--){

		/* a vertex may have many outgoing edges but we have to find
		  the one which has minimum cost...coz that edge takes us the
		  next stage in minimum cost from the currentvertex

		  in this loop our AIM is to find the cost of every vertex

		  cost[vertex] = edge cost from currentvertex to another vertex(say ith) + cost of ith vertex
		*/

		min = INFINITY;
		for(i=0;i<vertexcount;i++){

			if(graph[currentvertex][i]!=INFINITY){
				if(min > graph[currentvertex][i] + costofvertex[i]){
					min = graph[currentvertex][i] + costofvertex[i];
					vertexnear = i ;
				}
			}
		}

		costofvertex[currentvertex] = graph[currentvertex][vertexnear] + costofvertex[vertexnear];
		nearestvertex[currentvertex] = vertexnear;
	}

	/* now lets find the path */

	vertexforstage[stagecount-1] = vertexcount - 1;
	vertexforstage[0] = 0;

	for(i=1;i<stagecount-1;i++)
		vertexforstage[i] = nearestvertex[vertexforstage[i-1]];


	cout<<"\nTHE SHORTEST PATH IS:\n";
	for(i=0;i<stagecount;i++)
		cout<<vertexforstage[i]<<" - ";
	cout<<"#";

	cout<<"\n\nTHE OPTIMAL COST IS:-\t"<<costofvertex[vertexforstage[0]];

}

void Multistage::backwardApproach(){

	int currentvertex,i;
	int min,vertexnear;

	for(i=0;i<vertexcount;i++){
		costofvertex[i] = INFINITY;		//backward cost
		nearestvertex[i] = -1;	//nearest in the backward direction
	}

	costofvertex[0] = 0;  //backward cost

	for(currentvertex = 1; currentvertex<vertexcount; currentvertex++){

		min = INFINITY;
		for(i=0;i<vertexcount;i++){

			if(graph[i][currentvertex]!=INFINITY){
				/*backward cost of vertex[i]...as well as we have to
				 think backward so there exists an edge from i to currentvertex...think backward again..
				*/
				if(min > graph[i][currentvertex] + costofvertex[i]){
					min = graph[i][currentvertex] + costofvertex[i];
					vertexnear = i;  //nearest backward
				}
			}

		}

		costofvertex[currentvertex] = graph[vertexnear][currentvertex] + costofvertex[vertexnear];
		nearestvertex[currentvertex] = vertexnear;
	}

	vertexforstage[0] = 0;
	vertexforstage[stagecount-1] = vertexcount-1;

	for(i=stagecount-2;i>=1;i--)
		vertexforstage[i] = nearestvertex[vertexforstage[i+1]];

	cout<<"\nTHE SHORTEST PATH IS:\n";
	for(i=0;i<stagecount;i++)
		cout<<vertexforstage[i]<<" - ";
	cout<<"#";

	cout<<"\n\nTHE OPTIMAL COST IS:-\t"<<costofvertex[vertexforstage[stagecount-1]];


}

void Multistage::getInput(){

	int i,j;

	cout<<"\nEnter the number of vertices:-\t";
	cin>>vertexcount;

	cout<<"\nEnter the number of stages:-\t";
	cin>>stagecount;

	vertexforstage = new int[stagecount];
	costofvertex = new int[vertexcount];
	nearestvertex = new int[vertexcount];

	cout<<"\n\nENTER THE ADJACENCY MATRIX ( -1 for null edge )\n\n";

	for(i=0;i<vertexcount;i++)
		for(j=0;j<vertexcount;j++){
			cin>>graph[i][j];

			graph[i][j] = (graph[i][j]==-1) ? INFINITY : graph[i][j];
		}

}
