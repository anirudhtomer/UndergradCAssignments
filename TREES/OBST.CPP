// Optimal Binary Search Tree

#include<iostream.h>
#include<stdlib.h>
#include<conio.h>

#define INFINITY 1000

struct root{
		int x,y;
};

class Queue{


	struct root *queue;

	public:
	int front,rear;

	Queue(){
		front = 0;
		rear = 0;
		queue = (struct root*) (malloc(sizeof(struct root)*50));
	}

	void insert(struct root* ele){
		(queue + rear)->x = ele->x;
		(queue + rear)->y = ele->y;

		rear++;
	}

	struct root* delet(){

		struct root *retval = (struct root*) (malloc(sizeof(struct root)));

		retval->x = (queue + front)->x;
		retval->y = (queue + front)->y;

		front++;

		return retval;
	}
};

class OBST{

	int weightoftree[10][10],rootoftree[10][10],costoftree[10][10];

	int identifiercount;

	int *prob_success,*prob_failure;

	public:
	void getParam();
	void calcOptimal();
	int minCost(int,int);
	void printSolution();
	void printStat();
};

int main(){

	OBST *o1 = new OBST();

	clrscr();

	o1->getParam();
	o1->calcOptimal();
	o1->printSolution();

	getch();
	return 0;
}


//print process flow
void OBST::printStat(){

	int i,j,k;
	static int cnt;

	cout<<"Step "<<cnt+1<<"\n\n\t";
	for(i=0;i<identifiercount+1;i++){
		cout<<"["<<i<<"]           ";
	}

	cout<<"\n\n";

	for(i=0;i<=cnt;i++){

		cout<<"["<<i<<"]  ";

		for(j=0;j<identifiercount+1-i;j++){
			k = j+i;
			cout<<"w<"<<j<<","<<k<<"> = "<<weightoftree[j][k];
			cout<<"    ";
		}

		cout<<"\n     ";
		for(j=0;j<identifiercount+1-i;j++){
			k = j+i;
			cout<<"c<"<<j<<","<<k<<"> = "<<costoftree[j][k];
			cout<<"    ";
		}

		cout<<"\n     ";
		for(j=0;j<identifiercount+1-i;j++){
			k = j+i;
			cout<<"r<"<<j<<","<<k<<"> = "<<rootoftree[j][k]<<"    ";
		}

		cout<<"\n\n";
	}

	cnt++;

}
//calculate optimal solution
void OBST::calcOptimal(){

	/*
		*********    	JUST SCROLL DOWN AND READ "HOW PROGRAM WORKS" SECTION FIRST       ***********

		consider t<i,j> be a BST with

		Idenfiers as a<i+1>...a<j>
		r<i,j> is the root of tree t<i,j>
		w<i,j> is the weight of tree t<i,j>

		here i must always be lesser than j...if i==j then it represents the weight of the failure node.

								l=j
		w<i,j> = q<i> + SUMMATION   ( q<l> + p<l> )
								l=i+1

												l=j-1
		w<i,j> = p<j> + q<j> +  q<i> + SUMMATION   ( q<l> + p<l> )
												l=i+1

		w<i,j> = p<j> + q<j> + w<i,j-1>

		Cost of tree t<i,j> is

		cost<i,j> = prob_success for root node + cost of left subtree + cost of right subtree + weight of nodes of left subtree +  weight of nodes of right subtree

		assume the root node to be the the kth element in the array of identifiers
		from o to n

		cost<i,j> = prob_success<k> + cost<j,k-1> + cost<k,j> + w<i,k-1> + w<k,j>

		since we have considered the kth element to be the root we got the above solution
		but we have to consider all nodes from 0 to n and kth node can be any one of them
		and whichever kth node gives the minimum cost is the best node to be the root

		since t<i,j> has nodes from a<i+1>....a<j>


		cost<i,j> =    min( prob_success<k> + cost<i,k-1> + cost<k,j> + w<i,k-1> + w<k,j> )
				   i+1 <= k <=j

		now I never gave a fuck! to calculate
		the sum of "prob_success<k> + w<i,k-1> + w<k,j>" where  i+1 <= k <=j
		and assumed that most of the books are right when to summate it to give w<i,j>

		cost<i,j> =   min( cost<i,k-1> + cost<k,j>)  +    w<i,j>
				   i+1 <= k <=j
	*/


	/*
		****** EXPLANATION OF HOW PROGRAM WORKS ********

		ah! its damn! complex in Horowitz & Sahani & I am following their
		program (nirali too follows them).

		so in a BST we have nodes at each level. we had decided initially that the
		last level would be for Fictitious nodes which denote failure...so if u somehow reach them
		then u do not have any probability of success coz they denote failure of search
		so at those nodes prob_success = 0 & whatever left is prob_failure.  (1-0= 1)
		for n nodes we have n+1 failure nodes & probabibity of failure nodes is given in the problem
		statment in the array q [0 : n]

		weight of the failure nodes = q[i] where i = 0 to n

		our job is to check each and every combination of the BST's to find the optimal one
		so we start from the bottom i.e the failure nodes & go upto the top of the BST

		at each level (starting from bottom) we find the optimal right and left subtrees
		& their costs and weights are used for the nodes which are one level above
		its like propagating weights above.

		so starting from bottom...for n nodes there are n+1 failure nodes
		with weights w<0,0>,w<1,1>...w<n,n>
		weight of w<0,0> = prob_failure[0]..i.e. failure prob of 0th node
		similarly for other nodes.
		each node can be considered as a subtree at the lowest level (leaves).
		t<0,0>....t<n,n>

		now lets go one level above where nodes are available with weights
		w<0,1>,w<1,2>....w<n-1,n>...where r<0,1>=1...r<1,2>=2...r<n-1,n>=n

		possible subtrees for t<0,1> are t<0,0> & t<1,1>...for t<1,2> are t<1,1> and t<2,2>
		so weight w<0,1> = p<1> + q<1> + w[0,0]
		   cost c<0,1> = w<0,1> + (c<0,0> + c<1,1>)

		and so on for other nodes

		now lets go another level above where nodes are available with weights
		w<0,2>,w<1,3>...w<n-2,n>....where
		r<0,2> can be either root of subtree t<0,1> or t<1,2>
		so we have to calculate the cases considering each one at the root of the subtree t<0,2>
		so here are the possible cases for tree t<0,2>



   CASE 1:		 t<0,2>                                    		                                          CASE 2:   t<0,2>
		  cost<0,2> = cost<0,0> + cost<1,2> + w<0,2> 		           cost<0,2> = cost<0,1> + cost<2,2> + w<0,2>
		  w<0,2> = p[2] + q[2] + w[0,1]     			                    w<0,2> = p[2] + q[2] + w[0,1]
		  w<0,1> = p[1] + q[1] + w[0,0]    			                      w<0,1> = p[1] + q[1] + w[0,0]
               _______________________________                            ____________________________________
			    r<0,1>                                 					             r<1,2>
			   /     \                                            					   /    \
			  /       \                                             				            /      \
			 /         \                                                                                      /        \
		   r<0,0>      r<1,2>                                                                            r<0,1>     r<2,2>
				/   \                                                                               /     \
			       /     \                                                                               /      \
		              /       \                                                                              /        \
			     r<1,1>    r<2,2>    	                                                  r<0,0>    r<1,1>


					we have to find which of these gives cost minimum & we will chose that as the root node of the subtree t<0,2>
					as we go at above levels the number of node decreases(upto 1 which is the root) but the number of combinations to be checked get increased

	*/
	// ENOUGH TALKED....LETS CODE

	int i,j,k,l;

	//for failure nodes
	for(i=0;i<identifiercount+1;i++){
		weightoftree[i][i] = prob_failure[i];
		costoftree[i][i] = 0;
		rootoftree[i][i] = 0; //coz these are failure u can't allocate any of the identifiers representing these nodes
	}

	printStat();
	getch();
	//have u ever tried the SHELL SORT...the following loops are like SHELL SORT's loops
	for(i=1;i<identifiercount+1;i++){

		for(j=0;j<(identifiercount+1-i);j++){

			l = j+i;

			weightoftree[j][l] = prob_success[l] + prob_failure[l] + weightoftree[j][l-1];

			k = minCost(j,l);

			costoftree[j][l] = costoftree[j][k-1] + costoftree[k][l] + weightoftree[j][l];

			rootoftree[j][l] = k;

			//where k = identifier number of the identifier for which the cost of the subtree is minimum with the condition that k is the root of that subtree
		}
		printStat();
		getch();
	}

}


int OBST::minCost(int i,int j){

	int k;
	int retindex,min;

	// i< retindex <=j
	min = INFINITY;

	for(k = i+1 ; k <= j ; k++){

		if(min > (costoftree[i][k-1] + costoftree[k][j]) ){

			min = costoftree[i][k-1] + costoftree[k][j];
			retindex = k;
		}
	}

	return retindex;

}

//get parameters
void OBST::getParam(){

	int i;

	cout<<"\nEnter the number of identifiers:-\t";
	cin>>identifiercount;

	/*
		assuming that the identifiers are ordered in ascending order
		i.e i1 < i2< i3 ....< means lesser than
		and the tree name is t<0,n>...so its nodes are from 1 to n...including 1 and n
   */

	prob_success = new int[identifiercount + 1];
	cout<<"\nEnter the probabilities of success:-\t";

	for(i=1;i<identifiercount+1;i++){
		cin>>prob_success[i];  //range from 1 to n
	}

	/*
		for n nodes in a BST we always have n + 1 fictititous leaf nodes
		which denote failure...so if u somehow end up at the fictitious
		leaf nodes then the search for that element is failed.
	*/

	cout<<"\nEnter the probabilities of failure:-\t";
	prob_failure = new int[identifiercount + 1];
	for(i=0;i<identifiercount + 1;i++){
		cin>>prob_failure[i];  //range from 0 to n
	}

}
void OBST::printSolution(){

	int i,x,y;
	Queue *q1 = new Queue();
	struct root *r1,*r2;
	int prevcnt,newcnt;

	cout<<"\n\n******* yippppeeee Solution!!! ********\n\n";

	cout<<"Weight of the OBST :-\t"<<weightoftree[0][identifiercount];
	cout<<"\nCost of the OBST :-\t"<<costoftree[0][identifiercount];
	cout<<"\nRoot of the OBST :-\t"<<rootoftree[0][identifiercount];

	cout<<"\nThe tree is:-\n";

	x = 0;
	y = identifiercount;

	r1 = (struct root *) (malloc(sizeof(struct root)));
	r2 = (struct root *) (malloc(sizeof(struct root)));
	r1->x = x;
	r1->y = y;

	q1->insert(r1);

	newcnt = 1;
	while(newcnt!=0){

		prevcnt = newcnt;
		newcnt=0;

		while(prevcnt--){
			r1 = q1->delet();
			r2->x = r1->x;
			r2->y = r1->y;

			cout<<"r(<"<<r2->x<<","<<r2->y<<">,"<<rootoftree[r2->x][r2->y]<<")\t";

			if(r2->x==r2->y)
				continue;

			r1->x = r2->x;
			r1->y = rootoftree[r2->x][r2->y]-1;

			q1->insert(r1);
			newcnt++;

			r1->x = rootoftree[r2->x][r2->y];
			r1->y = r2->y;
			q1->insert(r1);

			newcnt++;

		}
		cout<<"\n";
	}

}




