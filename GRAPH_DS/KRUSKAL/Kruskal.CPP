/******** KRUSKAL ALGORITHM ***********/

#include<iostream.h>
#include<conio.h>

#define EDGEMAT 1
#define SOLUTIONMAT 2

class Edge{

	int vertexcount,edgecount,solutionedgecount;
	int *vertexset;

	struct edge{
		int vertex1,vertex2;
		int edgeweight;
	}edgearr[10],solutionedgearr[10],*edgearrptr;

	public:

	int spanningweight;

	void getAdjMatrix();
	int checkEdgearr(int,int);
	void printEdgeMatrix(int);
	void sortEdgeMatrix();
	void kruskal();
	int memberOfSet(int);
	void unitem1m2(int,int);

};

int main(){

	Edge *e1 = new Edge();

	clrscr();

	e1->getAdjMatrix();
	e1->sortEdgeMatrix();
	e1->printEdgeMatrix(EDGEMAT);
	e1->kruskal();
	e1->printEdgeMatrix(SOLUTIONMAT);

	cout<<"\n\nThe weight of the minimum cost spannig tree is :-\t"<<e1->spanningweight;

	getch();
	return 0;
}

//checkEdgearr
int Edge::checkEdgearr(int v1,int v2){

	int retval = 1;
	int i;

	for(i=0;i<edgecount;i++){

		if( (edgearr[i].vertex1==v1 && edgearr[i].vertex2==v2)  || (edgearr[i].vertex2==v1 && edgearr[i].vertex1==v2) ){
			retval = 0;
			break;
		}
	}

	return retval;

}

//get adjancency matrix
void Edge::getAdjMatrix(){

	int i,j;
	int adjmatrix[20][20];

	cout<<"Enter the number of vertices:-\t";
	cin>>vertexcount;

	vertexset = new int[vertexcount];

	for(i=0;i<vertexcount;i++){
		vertexset[i] = i;
	}

	cout<<"\n\nEnter the adjacency matrix (-1 for no edge) :-\t";

	for(i=0;i<vertexcount;i++){
		for(j=0;j<vertexcount;j++){
			cin>>adjmatrix[i][j];
		}
	}

	//now copy the edges in edge matrix

	edgecount=0;

	for(i=0;i<vertexcount;i++){

		for(j=0;j<vertexcount;j++){

			/*
				checkAdgearr() function is to check the repetition of edges
				it returns 0 if edge is already present & 1 if edge is not present
			*/

			if(adjmatrix[i][j]!=-1 && checkEdgearr(i,j)){
				edgearr[edgecount].vertex1 = i;
				edgearr[edgecount].vertex2 = j;
				edgearr[edgecount].edgeweight = adjmatrix[i][j];

				edgecount++;
			}

		}
	}

}

//bubble sort
void Edge::sortEdgeMatrix(){

	int i,j;
	edge tempedge;

	for(i=0;i<edgecount-1;i++){
		for(j=0;j<edgecount-i-1;j++){
			if(edgearr[j].edgeweight > edgearr[j+1].edgeweight){

				tempedge.vertex1 = edgearr[j].vertex1;
				tempedge.vertex2 = edgearr[j].vertex2;
				tempedge.edgeweight = edgearr[j].edgeweight;

				edgearr[j].vertex1 = edgearr[j+1].vertex1;
				edgearr[j].vertex2 = edgearr[j+1].vertex2;
				edgearr[j].edgeweight = edgearr[j+1].edgeweight;

				edgearr[j+1].vertex1 = tempedge.vertex1;
				edgearr[j+1].vertex2 = tempedge.vertex2;
				edgearr[j+1].edgeweight = tempedge.edgeweight;

			}
		}
	}
}

void Edge::printEdgeMatrix(int type){

	int i,n;
	cout<<"\n\n";

	if(type==EDGEMAT){
		cout<<"The edge Matrix is :";
		edgearrptr=edgearr;
		n=edgecount;
	}
	else{
		cout<<"The Solution edge Matrix is:";
		edgearrptr=solutionedgearr;
		n=solutionedgecount;
	}

	cout<<"\n\nV1\tV2\tEDGE-WT\n\n";

	for(i=0;i<n;i++){
		cout<<edgearrptr[i].vertex1<<"\t"<<edgearrptr[i].vertex2<<"\t"<<edgearrptr[i].edgeweight<<"\n";
	}
}

void Edge::kruskal(){

	int i;
	int m1,m2;

	cout<<"\n\nProcess Flow...\n";
	i=0;
	solutionedgecount = 0;
	spanningweight = 0;
	//for n vertices there must be n-1 edges in the spanning tree
	while(solutionedgecount!=vertexcount-1){

		cout<<"(<"<<edgearr[i].vertex1<<","<<edgearr[i].vertex2<<"> , "<<edgearr[i].edgeweight<<")";

		m1 = memberOfSet(edgearr[i].vertex1);
		m2 = memberOfSet(edgearr[i].vertex2);

		if(m1==m2){
			cout<<"\tRejected";
		}
		else{

			unitem1m2(m1,m2);

			solutionedgearr[solutionedgecount].vertex1 = edgearr[i].vertex1;
			solutionedgearr[solutionedgecount].vertex2 = edgearr[i].vertex2;
			solutionedgearr[solutionedgecount].edgeweight = edgearr[i].edgeweight;

			spanningweight += solutionedgearr[solutionedgecount].edgeweight;
			solutionedgecount++;

			cout<<"\tSelected";
		}

		cout<<"\n";
		i++;

	}

}


int Edge::memberOfSet(int vertex){
	int i;
	int retval;

	for(i=0;i<vertexcount;i++){
		if(vertex==i){
			retval = vertexset[i];
			break;
		}
	}

	return retval;
}

void Edge::unitem1m2(int m1,int m2){

	int i;

	/*
		if v1 is the member of set s1 & v2 is the member of set s2
		and there is a edge between v1 and v2
		then we have to merge set s1 & s2's all elements
	*/

	for(i=0;i<vertexcount;i++){
		if(vertexset[i]==m2){
			vertexset[i]=m1;
		}
	}
}






