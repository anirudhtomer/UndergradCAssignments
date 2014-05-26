//Program to compare the time complexities of algorithms

#include<iostream.h>
#include<conio.h>
#include<time.h>
#include <dos.h>

#define DELAY 100

class Sort{

	int n;
	int *oriarr,*copyarr;

	public:

	void getData();
	void recMergeSort(int,int);
	void recQuickSort(int,int);

	int partition(int,int);
	void merge(int,int,int);

	void copy_oriarr_into_copyarr();

	int getSize(){
		return n;
	}

	void displayStat(double);

};

int main()
{
	Sort *s1 = new Sort();
	clock_t start,end;

	clrscr();

	s1->getData();

	cout<<"\n\nNOW PLEASE WAIT TO GET THE RESULTS OF BOTH ALGORITHMS:\n\n";

	//MERGE SORT
	s1->copy_oriarr_into_copyarr();
	start = clock();
	s1->recMergeSort(0,s1->getSize()-1);
	end = clock();

	cout<<"\n\nMERGE SORT RESULTS:\n";
	s1->displayStat((end-start)/CLK_TCK);

	//QUICK SORT
	s1->copy_oriarr_into_copyarr();//the array was sorted by merge...so we need to initialize again to the values entered by user
	start = clock();
	s1->recQuickSort(0,s1->getSize()-1);
	end = clock();

	cout<<"\n\nQUICK SORT RESULTS:\n";
	s1->displayStat((end-start)/CLK_TCK);

	getch();

	return 0;

}

void Sort::copy_oriarr_into_copyarr(){

	int i;

	for(i=0;i<n;i++)
		copyarr[i] = oriarr[i];

}

void Sort::displayStat(double timetaken){
	int i;

	cout<<"\n";
	for(i=0;i<n;i++)
		cout<<copyarr[i]<<"\t";

	cout<<"\n\nTime taken to sort:\t"<<timetaken<<"\n";

}

void Sort::recMergeSort(int startindex,int endindex){

	int mid;


	if(startindex==endindex)
		return;

	delay(DELAY);

	mid = (startindex + endindex)/2;

	recMergeSort(startindex,mid);
	recMergeSort(mid+1,endindex);

	merge(startindex,mid,endindex);

}

void Sort::merge(int startindex,int mid,int endindex){

	int i,j,tempcnt;
	int *temparr = new int[endindex - startindex + 1];

	i = startindex;
	j = mid+1;

	tempcnt=0;

	while( i<=mid && j<=endindex){

		if(copyarr[i] < copyarr[j])
			temparr[tempcnt++] = copyarr[i++];
		else
			temparr[tempcnt++] = copyarr[j++];
	}

	while( i<=mid)
		temparr[tempcnt++] = copyarr[i++];

	while(j<=endindex)
		temparr[tempcnt++] = copyarr[j++];

	for(i=0,j=startindex;i<tempcnt;i++)
		copyarr[j++] = temparr[i];

	delete [] temparr;
}

void Sort::recQuickSort(int startindex,int endindex){

	int mid;

	//assuming pivot to be the first element always

	/*  its not that u can put delay anywhere u have to put it
		at a place which gives equal oppurtunities to both Quick & Merge Sort
	*/

	if(startindex>=endindex)
		return;

	delay(DELAY);

	mid = partition(startindex,endindex);

	recQuickSort(startindex,mid-1);
	recQuickSort(mid+1,endindex);
}


/* our aim is to make partitions such that

(from TENENBAUM )

for an element at index J
all elements from index 0 to j-1 should be less than or equal to element at index J
all elements from index j+1 to max should be greater than or equal to element at index J

*/

int Sort::partition(int startindex,int endindex){

	int down,up;
	int pivot;
	int temp;

	pivot = startindex;

	down = startindex;
	up = endindex;

	while(up > down){

		while(1){

			//if the element is greater than pivot or UP is not greaterthan down
			if( (copyarr[down] > copyarr[pivot]) || !(up>down) )
				break;

			down++;
		}

		while(1){

			//if the element is less than or equal to element at pivot
			if(copyarr[up] <= copyarr[pivot])
				break;

			up--;
		}

		/* for the clarity of understanding I havent put the conditions at while
		& used while(1) instead */

		if(up > down){
			//swap the elements

			temp = copyarr[down];
			copyarr[down] = copyarr[up];
			copyarr[up] = temp;
		}
	}

	//swap the element at pivot and the element at UP..REASON??? written in comments just before this function started
	temp = copyarr[up];
	copyarr[up] = copyarr[pivot];
	copyarr[pivot] = temp;

	return up;
}

void Sort::getData(){

	int i;

	cout<<"\nEnter the number of elements:-\t";
	cin>>n;

	oriarr = new int[n];
	copyarr = new int[n];

	cout<<"\n\nEnter the Elements:\t";
	for(i=0;i<n;i++)
		cin>>oriarr[i];

}


