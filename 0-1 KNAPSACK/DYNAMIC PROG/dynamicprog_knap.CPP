#include<iostream.h>
#include<conio.h>

#define INCLUDED 1
#define NOTINCLUDED 0

/**************** INPUTS MUST BE IN THE SORTED ORDER OF W[i] ascending***********/

class Knapsack{

	int maxweight,objectcount;
	int optimalweight;

	int optimalprofittable[10][130];
	/*
		Optimal profit table is a structure in which
		rows -> index of the instances
		columns -> 0 to maxweight

		table[i][j] = max profit that can be obtained for weight j using instances from i to 1

		at any row i we try to find
		for each from weight from 0 to maxweight the value of profit
		which can be gained by using instances from i to 1st instance.

		so when we are making calculations for instance 3 ...
		we can use the instances 1 and 2 in calculations coz the optimal profit is given by the
		combinations of 1,2,3 ...I mean any combo can be there

	*/

	int objectincluded[10][130];
	/*
		object included is a 2D array whose arr[i][j] val can be either 1 or 0
		so if an object "i" is included in making the weight "j"
		then arr[i][j] = 1
	*/

	struct object{

		int profit;
		int weight;

	}object[10];

	public:

	void getData();
	void dynamicprog();
	void printSolution();

};

int main(){

	Knapsack *k1 = new Knapsack();

	clrscr();

	k1->getData();
	k1->dynamicprog();
	k1->printSolution();

	getch();
	return 0;
}

void Knapsack::printSolution(){

	int i,j;
	int tempweight;

	cout<<"\n\nOPTIMAL PROFIT TABLE\t** COLUMN--->WEIGHT\tROWS---->OBJECTS **\n\n\t";

	for(i=0;i<=maxweight;i++)
		cout<<i<<"   ";

	cout<<"\n\n";
	for(i=0;i<=objectcount;i++){

		cout<<"E-"<<i<<"\t";  //E- denotes element/object
		for(j=0;j<=maxweight;j++){
			cout<<optimalprofittable[i][j]<<"   ";
		}

		cout<<"\n";
	}

	cout<<"\n\nMax Profit = "<<optimalprofittable[objectcount][maxweight];

	cout<<"\nObjects included are:-\t";


	tempweight = maxweight;

	for(i=objectcount;i>=1;i--){
			if(objectincluded[i][tempweight]==INCLUDED){
				cout<<i<<"\t";
				tempweight = tempweight - object[i].weight;
			}
	}

}

void Knapsack::dynamicprog(){

	int currentobject,currentweight;
	int oldprofit,newprofit,remprofit;
	int curobjweight,remweight;

	for(currentobject=1;currentobject<=objectcount;currentobject++){

		curobjweight = object[currentobject].weight;

		for(currentweight=1;currentweight<=maxweight;currentweight++){

			if(curobjweight <= currentweight){

				/*
					so either the old profit was good without new object's profit's inclusion

					or we include the new object
					but see if we include the new object with weight w1 for say maxweight = 10
					then 10 - w1 is the reminaing weight & we have to check what was the profit
					obtained by last object for this weight....last object coz at each level such calculations
					happen for optimality so last object is always optimal
							   2
				*/

				oldprofit = optimalprofittable[currentobject-1][currentweight];

				remweight = currentweight - curobjweight;
				remprofit = optimalprofittable[currentobject-1][remweight];

				newprofit = object[currentobject].profit + remprofit;

				if(newprofit > oldprofit){
					optimalprofittable[currentobject][currentweight] = newprofit;
					objectincluded[currentobject][currentweight] = INCLUDED;
				}

				else{
					optimalprofittable[currentobject][currentweight] = oldprofit;
					objectincluded[currentobject][currentweight] = NOTINCLUDED;
				}
			}

			else{

				optimalprofittable[currentobject][currentweight] = optimalprofittable[currentobject-1][currentweight];

				objectincluded[currentobject][currentweight] = NOTINCLUDED;
			}
		}
	}
}

void Knapsack::getData(){

	int i,j;

	cout<<"\nEnter the capacity of the knapsack..max 125..not more han!!!:-\t";
	cin>>maxweight;

	cout<<"Enter the number of objects:-\t";
	cin>>objectcount;

	cout<<"\n\nEnter the profit array:-\t";
	for(i=1;i<=objectcount;i++){
		cin>>object[i].profit;
	}

	cout<<"\n\nEnter the weight array:-\t";
	for(i=1;i<=objectcount;i++){
		cin>>object[i].weight;
	}

	//intialize the optimalprofittable
	for(i=0;i<=maxweight;i++)
		optimalprofittable[0][i] = 0;
	for(i=0;i<=objectcount;i++)
		optimalprofittable[i][0] = 0;

	/*
		 I have initialized the table with "0"
		 for table[0][j] where j is the weight from 0 to maxweight
		 ah! this is just done to make the calculations easier
		 coz we check for a object i either the profit is maximized by its inclusion with the i-1 object...or its not reqd.
		 so while calculating for 1st element the index i-1..i.e 1-1=0..0th index is gonna accessed
		 & I want it to be to be on safer side
	*/

}
