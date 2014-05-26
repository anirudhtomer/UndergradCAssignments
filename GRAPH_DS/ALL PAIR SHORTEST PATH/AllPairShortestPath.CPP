//ALL PAIR SHORTEST PATH

#include<iostream.h>
#include<conio.h>

#define INFINITY 10000

class AllPair{

	int vertexcount;

	int arr[20][20];

	public:

	void getInput();
	void allPair();

	void printStat(int);

};

int main(){

	AllPair *a1 = new AllPair();

	clrscr();

	a1->getInput();
	a1->allPair();

	return 0;
}

void AllPair::allPair(){

	int i,j,k;
	int min1,min2;

	cout<<"\n\nAll pair Shortest path using Floyd Marshall Algo\n\n";

	printStat(0);
	for(k=1;k<=vertexcount;k++){
		for(i=1;i<=vertexcount;i++){
			for(j=1;j<=vertexcount;j++){

				min1 = arr[i][j];
				min2 = arr[i][k] + arr[k][j];

				if(i==j && (min1<0 || min2<0))
					cout<<"\nTHERE EXISTS A -VE CYCLE IN THE GRAPH...UNDEFINED OUTPUT GONNA COME\n";

				arr[i][j] = min1 < min2 ? min1 : min2;
			}
		}
		printStat(k);
	}
}

void AllPair::printStat(int index){

	int i,j;
	char x=236;

	cout<<"\nA ("<<index<<")\n\n";

	for(i=1;i<=vertexcount;i++){
		for(j=1;j<=vertexcount;j++){
			if(arr[i][j]==INFINITY)
				cout<<x;
			else
				cout<<arr[i][j];

			cout<<"\t";
		}
		cout<<"\n";
	}

	getch();
}

void AllPair::getInput(){

	int i,j;

	cout<<"\nEnter the number of vertices:-\t";
	cin>>vertexcount;

	cout<<"\n\nENTER THE ADJACENCY MATRIX ( 10000 for INFINITY )\n\n";

	for(i=1;i<=vertexcount;i++)
		for(j=1;j<=vertexcount;j++){
			cin>>arr[i][j];

			arr[i][j] = (arr[i][j]==INFINITY) ? INFINITY : arr[i][j];
		}
}
