//knapsack backtracking
//BASED ON HOROWITZ SAHANI'S CODE..thanks to preetam for teaching at crucial time

#include<iostream.h>
#include<conio.h>

#define TRUE 1
#define FALSE 0

class BackKnap{

	int knapsackcapacity,itemcount;

	int *profitof,*weightof;

	int *tempselection,*result;

	int maxprofittillnow,maxweighttillnow;

	public:

	void getInput();
	void generateChild(int,int,int);
	int getProfitOfRightSubtree(int,int,int);
	void printSolution();
};

int main(){

	/*  I would be explaining everything in later sections but lemme first tell that
		we deal with a tree here which is initially assumed to empty initially

		ah! every node in the tree represent an object of the input.
		howev	er since using a single tree we try to detect many combinations
		so do not expect tree to have N nodes.

		every node for which the LEFT traversal is being made is temporarily
		selected in output
		every node for which the RIGHT traversal is being made is supposed to be
		not selected in output

		however u will find that some nodes have both right & left child
		but remember that I was talking about CURRENT TRAVERSAL DIRECTION
		which can be right or left & depending on that a particular node is either
		IN or OUT

		so lets start with empty tree
	*/

	BackKnap *b1 = new BackKnap();

	b1->getInput();
	b1->generateChild(1,0,0); //1,0,0...1 means add 1st object as node..0 & 0 are current profit and current weight respectively
	b1->printSolution();

	return 0;
}

void BackKnap::printSolution(){
	int i;

	cout<<"\n\nTHE ITEMS SELECTED ARE:-\t";

	for(i=1;i<=itemcount;i++){
		if(result[i]==TRUE)
			cout<<i<<"\t";
	}

	cout<<"\n\nMAXPROFIT = "<<maxprofittillnow;
	cout<<"\n\nWEIGHT = "<<maxweighttillnow;
}

int BackKnap::getProfitOfRightSubtree(int currentitem,int totalprofit,int totalweight){

	/*so we do not consider currentitem here...we select all items which are
	  currently deeper in the input array & yet to be selected...
	  remember this function is called to check the if its worth opening
	  the RIGHT SUBTREE with the exclsion of current node/item from solution

	  so this function will return u some profit
	  if that profit comes out to be > maxprofittillnow
	  then its worth opening right subtree
	*/

	int nextitem;

	int tempprofit = totalprofit;
	int tempweight = totalweight;

	for(nextitem=currentitem + 1;nextitem<=itemcount;nextitem++){

		tempweight += weightof[nextitem];
		tempprofit += profitof[nextitem];
		
		//if we get past the knapsack capacity then break
		if(!(tempweight < knapsackcapacity))
			break;
	}

	return tempprofit;
}

void BackKnap::generateChild(int currentitem,int totalprofit,int totalweight){

	int i;

	if(totalweight + weightof[currentitem] <= knapsackcapacity){

		tempselection[currentitem] = TRUE;

		if(currentitem < itemcount)
			generateChild(currentitem + 1,totalprofit + profitof[currentitem],totalweight + weightof[currentitem]);

		else{   // if currentitem is the Nth item
			if((totalprofit + profitof[currentitem]) > maxprofittillnow){
				maxprofittillnow = totalprofit + profitof[currentitem];
				maxweighttillnow = totalweight + weightof[currentitem];

				//permanently select all temporarily selected objects
				for(i=1;i<=currentitem;i++){
					result[i] = tempselection[i];
				}
			}
		}
	}

	/*A case may arise when the knapsack capacity gets full
	  at that time u can't leave things as they are but u have search for a better solution
	  which may be yielded by an object which is not yet visited in the array

	  lets take an example
	  profit = 1 2 5
	  weight = 2 3 4

	  so initially the tree would be having zero nodes
	  LEFT traversal & the first object is added
	  LEFT again & second object is added
	  LEFT again....but the first IF confition wont allow to add that object

	  so I can't stop...I will now traverse RIGHT & as I said when we traverse in
	  RIGHT of a particular node it means we are trying to find solution which
	  do have the current node as a part of the final result

	  before u traverse that part of the tree its first better to check
	  if its worth to traverse that part of the tree
	  the NEXT IF condition is for that purpose only...so if its worth traversing
	  then we UNSELECT current node & MOVE RIGHT & follow the earlier process

	*/

	if(getProfitOfRightSubtree(currentitem,totalprofit,totalweight) >= maxprofittillnow){

		tempselection[currentitem] = FALSE; //as I said above unselect current item & traverse to RIGHT

		if(currentitem < itemcount) //start following the earlier process now
			generateChild(currentitem + 1,totalprofit,totalweight);

		else{  //if the current item was the last item
			if(totalprofit > maxprofittillnow){
				maxprofittillnow = totalprofit;
				maxweighttillnow = totalweight;

				//permanently select all temporarily selected objects
				for(i=1;i<=currentitem;i++){
					result[i] = tempselection[i];
				}


			}
		}

	}
}

void BackKnap::getInput(){

	int i,j;

	cout<<"\nEnter the capacity of the knapsack..:-\t";
	cin>>knapsackcapacity;

	cout<<"Enter the number of objects:-\t";
	cin>>itemcount;

	profitof = new int[itemcount+1];
	weightof = new int[itemcount+1];


	maxprofittillnow = 0;
	maxweighttillnow = 0;

	tempselection = new int[itemcount + 1];
	result = new int[itemcount + 1];
	
	cout<<"\n\nEnter the profit array:-\t";
	for(i=1;i<=itemcount;i++){
		cin>>profitof[i];
	}

	cout<<"\n\nEnter the weight array:-\t";
	for(i=1;i<=itemcount;i++){
		cin>>weightof[i];
	}

}