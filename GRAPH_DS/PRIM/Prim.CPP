/******** PRIM's ALGORITHM ***********/

#include<iostream.h>
#include<conio.h>

#define TRUE 1
#define FALSE 0

#define INFINITY 10000

class Edge{

	int vertexcount,solutionedgecount;
	int *vertexvisited,*mindistancetoanyvertex,*closestvertex;

	int adjmatrix[20][20];
	struct edge{
		int vertex1,vertex2;
		int edgeweight;
	}solutionedgearr[10];

	public:

	int spanningweight;

	void getAdjMatrix();
	void printSolutionMatrix();
	void prim();
	void printProcessStat(int);

	int edgeweight(int v1,int v2){
		return adjmatrix[v1][v2];
	}
};

int main(){

	Edge *e1 = new Edge();

	clrscr();

	e1->getAdjMatrix();
	e1->prim();
	e1->printSolutionMatrix();

	cout<<"\n\nThe weight of the minimum cost spannig tree is :-\t"<<e1->spanningweight;

	getch();
	return 0;
}

//get adjancency matrix
void Edge::getAdjMatrix(){

	int i,j;

	cout<<"Enter the number of vertices:-\t";
	cin>>vertexcount;

	vertexvisited = new int[vertexcount];
	mindistancetoanyvertex = new int[vertexcount];
	closestvertex = new int[vertexcount];

	cout<<"\n\nEnter the adjacency matrix (-1 for no edge) :-\t";

	for(i=0;i<vertexcount;i++){

		for(j=0;j<vertexcount;j++){

			cin>>adjmatrix[i][j];

			if(adjmatrix[i][j]==-1){
				adjmatrix[i][j] = INFINITY;
			}
		}
	}

}

void Edge::printSolutionMatrix(){

	int i,n;
	cout<<"\n\nThe Solution edge Matrix is:";
	cout<<"\n\nV1\tV2\tEDGE-WT\n\n";

	for(i=0;i<solutionedgecount;i++){
		cout<<solutionedgearr[i].vertex1<<"\t"<<solutionedgearr[i].vertex2<<"\t"<<solutionedgearr[i].edgeweight<<"\n";
	}
}


// Prim's Algorithm
void Edge::prim(){

	int i;
	int min;

	int currentvertex,nextcurrentvertex;
	int tempwt;

	solutionedgecount = 0;
	spanningweight = 0;

/*
	since we have just started and not visited any vertex we must initialize vertexvisited to false
*/
	for(i=0;i<vertexcount;i++){
		vertexvisited[i] = FALSE;
	}

/*
	we are not supposed to find the minimum edge weights b/w vertices
	hehehehe...the PRIM's ALGO is supposed to find it.

	So as humans we don't know anything & we have to depend on PRIM ALGO
	so let "mindistancetoanyvertex" for all vertices be INFINITY

	during the processing this INFINITY would be replaced by the actual distance
	PRIM is gonna do that, not us coz if we do that using our brain(algorithm) then there is no use
	PRIM algo here.
*/

	for(i=0;i<vertexcount;i++){
		//imagine a hypothetical vertex to be closest...initially ... I am imagining to it to be "-1"...ya its a hypothetical vertex
		closestvertex[i] = -1;
		
		//distance to hypothetical vertex
		mindistancetoanyvertex[i]=INFINITY;
	}


	//initial status of the prim process
	printProcessStat(-1);
	getch();

/*
	in prim's algorithm I am starting with vertex 0...u can start with any
*/
	nextcurrentvertex = 0;

	while(solutionedgecount!=vertexcount-1){

		currentvertex = nextcurrentvertex;

		//yes we have visited the current vertex
		vertexvisited[currentvertex] = TRUE;

		for(i=0;i<vertexcount;i++){
		//so if vertex i is nearer to current vertex than the previous minimum distanced vertex then do following
			if(vertexvisited[i]==FALSE){

				tempwt = edgeweight(currentvertex,i);

				if(mindistancetoanyvertex[i] > tempwt){

					closestvertex[i] = currentvertex;
					mindistancetoanyvertex[i] = tempwt;

				}
			}
		}

		//now we have to find the next vertex which is not yet visited & which is nearest to anyt vertex v(say) in the set of vertices already visited
		min = INFINITY; //its the temp variable I am using to find the min distance

		for(i=0;i<vertexcount;i++){

			if(vertexvisited[i]==FALSE){
				if(min > mindistancetoanyvertex[i]){

					min = mindistancetoanyvertex[i];
					nextcurrentvertex = i;
				}
			}
		}

		//add to the solution the nextcurrentvertex and the vertex which is minimum distanced to it
		solutionedgearr[solutionedgecount].vertex1 = nextcurrentvertex;
		solutionedgearr[solutionedgecount].vertex2 = closestvertex[nextcurrentvertex];
		solutionedgearr[solutionedgecount].edgeweight = edgeweight(nextcurrentvertex,closestvertex[nextcurrentvertex]);
		spanningweight+=solutionedgearr[solutionedgecount].edgeweight;
		solutionedgecount++;

		printProcessStat(currentvertex);
		getch();

		/*mindistancetoanyvertex[nextcurrentvertex]=INFINITY;
		vertexvisited[closestvertex[nextcurrentvertex]] = TRUE;*/
	}
}

//print process stat
void Edge::printProcessStat(int curvertex){

	int i;
	static int cnt;
	char infi = 236;

	cout<<"\nStep:"<<cnt++<<"\t\tCurrent Vertex:      "<<curvertex<<"\n\t\t";
	for(i=0;i<vertexcount;i++){
		cout<<"\t"<<i;
	}

	cout<<"\n\nvertex visited\t\t";
	for(i=0;i<vertexcount;i++){
		if(vertexvisited[i]==TRUE)
			cout<<"T\t";
		else
			cout<<"F\t";
	}

	cout<<"\nmindistancetoanyvertex\t";
	for(i=0;i<vertexcount;i++){
		if(mindistancetoanyvertex[i]==INFINITY)
			cout<<infi<<"\t";
		else
			cout<<mindistancetoanyvertex[i]<<"\t";
	}

	cout<<"\nclosestVertex\t\t";
	for(i=0;i<vertexcount;i++){
		cout<<closestvertex[i]<<"\t";
	}

	cout<<"\n\nV1\tV2\tEDGE-WT\n\n";
	for(i=0;i<solutionedgecount;i++){
		cout<<solutionedgearr[i].vertex1<<"\t"<<solutionedgearr[i].vertex2<<"\t"<<solutionedgearr[i].edgeweight<<"\n";
	}
	cout<<"\nPress any key...";

}
