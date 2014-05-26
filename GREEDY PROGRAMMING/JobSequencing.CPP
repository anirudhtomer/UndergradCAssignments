//JOB SEQUENCING

#include<iostream.h>
#include<conio.h>

class JobSeq{

	int jobcount;
	int maxdeadline;

	int *deadline,*profit;
	int *result;

	int resultcnt;

	public:

	void getInput();
	void sortInputProfitWise();
	void jobsequencing();
	void printStat(int);
	void printResult();

};

int main(){

	JobSeq *js = new JobSeq();

	clrscr();

	js->getInput();
	js->sortInputProfitWise();
	js->jobsequencing();
	js->printResult();

	getch();

	return 0;
}

void JobSeq::printResult(){

	int profitcnt=0;
	int i;

	cout<<"\n\nTHE FOLLOWING JOBS WERE SELECTED:\n";
	cout<<"(Profit , Deadline )\n";

	for(i=1;i<=resultcnt;i++){

		cout<<"\n("<<profit[result[i]]<<" , "<<deadline[result[i]]<<")";

		profitcnt+=profit[result[i]];

	}

	cout<<"\n\nNet Profit:\t"<<profitcnt;

}

void JobSeq::jobsequencing(){

	int nextjob;
	int lastaddedjobindex;
	int insertindex;
	int shiftindex;

	//we are working with sorted list now

	/* add the first job as it is...coz
	we are gonna work like insertion sort in this algo */

	result[0] = 0;       //               D P   D P
	deadline[0] = 0;   //imagine a case   8,6   8,6   6,4   4,2    4,2
	profit[0] = 0;     // and run this algo..u'll surely understand its significance

	result[1] = 1; //add the job 0 as it is & it has highest profit...sorted list
	lastaddedjobindex = 1;  //yeah the first job was added at index 0

	/*
	with each loop try to add a new element by inserting it into already
	inserted element remember that already inserted elements have better
	profit...& the new job can be added only if there is a job having bigger
	deadline than the current job & there is still a space left
	(I mean it can fit into the deadlines which are left)...so its like if we
	have jobs with deadlines 2 and 2 inside & u ask me to add a new job with
	deadline 1..that's not possible...coz the jobs inside coz they have better profit
	*/

	printStat(1);
	for(nextjob = 2; nextjob <= jobcount  && lastaddedjobindex!=maxdeadline ; nextjob++){

		/*
			the variable insert index is used coz this specifies the index after which ur
			going to try to insert ur new job...so if there are already 3 jobs inside
			then insertindex = 3 initially coz (insertindex + 1)=4 is the first
			perspective postion where u can add ur job....
		*/
		insertindex = lastaddedjobindex;

		/* in the following loop::
		suppose the job to inserted has deadline 2 and already 2 jobs are inserted so our job is to
		check with everyjob already inside that if the job to be inserted has a lesser deadline than the already inserted jobs
		then we have our chances to insert the new job at a place deeper inside the result array

		I knw I was NOT ABLE TO EXPLAIN it so lets take example

		jobs with deadlines  1 2 3 are inserted at locations 1 2 3 inside
		now a new job with deadline 1 comes...now u knw that jobs inside have better profit
		coz we are working on sorted so jobs come in order of decreasing profit

		so initially u can insert it at position 4 but then the deadline dosen't match
		so lets try inside till we get jobs with higher deadlines inside

		so once u reach index 1 u see that there is already a job with deadline 1 inside
		& ur deadline is 1 too..so u can either insert ur job at index 2 or more coz the job
		already at location 1 with deadline 1 has a better profit than u....

		we do this till the above situation comes or we reach the beginning of the result array.

		*/

		while( deadline[result[insertindex]] > deadline[nextjob]  && insertindex >0 )
			insertindex--;

		/*
			so we check 2 conditions here
			1st is related to the above for loop..that u can easily MAP
			2nd one is IMP**
			just remember the example I gave above
			jobs with deadline 1 2 3 are inserted at postions 1 2 3 respectively

			so after the while loop ur insertindex becomes 1 ..that means
			the prospective insertable position is insertindex + 1 =2
			but the deadline of the job to inserted is 1 too so there is no
			point in inserting a job at position 2(deadline 2) when its deadline is 1 & already expired

		*/

		if( deadline[result[insertindex]] <= deadline[nextjob] && deadline[nextjob] > insertindex ){

			/*
				now u must insert ur element at the insertindex position
				but everything inside is packed up..so to make some space
				u have to shift things...so star shifting from RIGHT SIDE
				till u reach the insertindex + 1 postion ...
			*/
			for(shiftindex = lastaddedjobindex; shiftindex >= insertindex + 1;shiftindex--){
				result[shiftindex + 1] = result[shiftindex];
				printStat(nextjob);
			}

			//after shifting we have insertindex + 1 position empty so add ur job here

			result[insertindex + 1] = nextjob;
			lastaddedjobindex++;
		}
		printStat(nextjob);
	}

	resultcnt = lastaddedjobindex;

}


//print intermediate status
void JobSeq::printStat(int index){

	int i;

	cout<<"\n\nStatus for jobtobeadded = "<<index<<"\t";
	for(i=1;i<=jobcount;i++){
		if(result[i]==-1)
			cout<<"-\t";
		else
			cout<<result[i]<<"\t";
	}
	getch();
}

void JobSeq::sortInputProfitWise(){

	int i,j;
	int temp;

	for(i=1;i<=(jobcount-1);i++){
		for(j=1;j<=(jobcount-i);j++){

			if(profit[j] < profit[j+1]){

				temp = deadline[j];
				deadline[j] = deadline[j+1];
				deadline[j+1] = temp;

				temp = profit[j];
				profit[j] = profit[j+1];
				profit[j+1] = temp;

			}
		}
	}
}

void JobSeq::getInput(){

	int i;

	cout<<"\nEnter the number of jobs:-\t";
	cin>>jobcount;

	result = new int[jobcount + 1];
	deadline = new int[jobcount + 1];
	profit = new int[jobcount + 1];

	cout<<"\n\nTAKING INPUT\n";

	maxdeadline = -1;

	for(i=1;i<=jobcount;i++){

		cout<<"\nEnter the deadline of job "<<i<<" :\t";
		cin>>deadline[i];

		if(maxdeadline < deadline[i])
			maxdeadline = deadline[i];

		cout<<"\nEnter the profit of job "<<i<<" :\t";
		cin>>profit[i];

		result[i] = -1;
	}

}
