//Code Optimization
//constant folding,copy propagation,common subexpression,dead code elim

#include<iostream.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#define END "#"

#define SEL 1
#define NOTSEL 0

#define SET 1
#define UNSET 0

class TAC{

	int codecount;

	struct item{
		char lhs[5];
		char operand1[5];
		char operatr[2];
		char operand2[5];
		int selflag;
	}taccode[20];

	public:

	void getInput();
	void printTAC();
	void cf_cp_cse();
	void deadcodeelim();

};


int main(){

	TAC *t1 = new TAC();

	clrscr();

	t1->getInput();
	cout<<"\n\nThe Three Address Code entered by you is:\n\n";
	t1->printTAC();

	t1->cf_cp_cse();
	cout<<"\n\nThe Three Address Code after CF,CP and CSE is:\n\n";
	t1->printTAC();

	t1->deadcodeelim();
	cout<<"\n\nThe Final Code after Dead code Elimination is:\n\n";
	t1->printTAC();

	getch();
	return 0;
}

//dead code elimination
void TAC::deadcodeelim(){

	int i,j;
	int flag1,flag2;

	//unselect all lines of code
	for(i=0;i<codecount;i++)
		taccode[i].selflag=NOTSEL;

	//we start from the last line & consider it to be the final statement and always select it
	taccode[codecount-1].selflag=SEL;

	for(i=codecount-1;i>=0;i--){

		if(taccode[i].selflag==NOTSEL)
			continue;

		//select all LHS which are in operand part of the selected statement

		flag1 = UNSET;
		flag2 = UNSET;

		for(j=i-1;j>=0;j--){

			if(!strcmp(taccode[i].operand1,taccode[j].lhs) && flag1==UNSET){
				taccode[j].selflag=SEL;
				flag1 = SET;
			}

			if(!strcmp(taccode[i].operand2,taccode[j].lhs) && flag2==UNSET){
				taccode[j].selflag=SEL;
				flag2 = SET;
			}
		}
	}


}

//constant folding...copy propagation...common subexpression elimination
void TAC::cf_cp_cse(){

	int i,j;
	int flag[3];
	int flag1,flag2;

	for(i=0;i<codecount;i++){

		for(j=i-1;j>=0;j--){

			//check for copy propagation
			if(!strcmp(taccode[i].operand1,taccode[j].lhs) && strcmp(taccode[j].operatr,"#") && !strcmp(taccode[i].operatr,"#")){

				strcpy(taccode[i].operand1,taccode[j].operand1);
				strcpy(taccode[i].operatr,taccode[j].operatr);
				strcpy(taccode[i].operand2,taccode[j].operand2);

				break;

			}
		}

		flag1 = UNSET;
		flag2 = UNSET;

		for(j=i-1;j>=0;j--){

			//check if constant folding can be done
			if(!strcmp(taccode[i].operand1,taccode[j].lhs) && !strcmp(taccode[j].operatr,"#") && flag1 == UNSET){
				strcpy(taccode[i].operand1,taccode[j].operand1);
				flag1 = SET;
			}

			if(!strcmp(taccode[i].operand2,taccode[j].lhs) && !strcmp(taccode[j].operatr,"#") && flag2 == UNSET){
				strcpy(taccode[i].operand2,taccode[j].operand1);
				flag2 = SET;
			}

		}

		flag[0]=flag[1]=flag[2] = UNSET;

		for(j=i-1;j>=0;j--){

			/*check for common subexpression
				1. check operand 1
				2. check operator
				3. check operand 2
			*/

			//1
			if(!strcmp(taccode[i].operand1,taccode[j].operand1))
				flag[0] = SET;
			//2
			if(!strcmp(taccode[i].operatr,taccode[j].operatr) && strcmp(taccode[i].operatr,"#"))
				flag[1] = SET;
			//3
			if(!strcmp(taccode[i].operand2,taccode[j].operand2) && strcmp(taccode[i].operatr,"#"))
				flag[2] = SET;

			//if all 3 flags are set then we can do common subexpression elimination
			if(flag[0]==SET && flag[1]==SET && flag[2]==SET){
				strcpy(taccode[i].operand1,taccode[j].lhs);
				strcpy(taccode[i].operatr,"#");
				strcpy(taccode[i].operand2,"#");
				break;
			}
		}
	}
}

void TAC::getInput(){

	int i;

	cout<<"\nEnter the number of lines of code:-\t";
	cin>>codecount;

	cout<<"\n\nEnter the code:-\n";
	for(i=0;i<codecount;i++){
		scanf("%s = %s %s %s",(taccode+i)->lhs,(taccode+i)->operand1,(taccode+i)->operatr,(taccode+i)->operand2);
		(taccode+i)->selflag=SEL;
	}
}

void TAC::printTAC(){

	int i;

	for(i=0;i<codecount;i++){

		//if the statement is not selected
		if(taccode[i].selflag==NOTSEL)
			continue;

		cout<<taccode[i].lhs<<" = "<<taccode[i].operand1<<" ";

		if(!strcmp(taccode[i].operatr,"#"))
		   cout<<";\n";
		else
		   cout<<taccode[i].operatr<<" "<<taccode[i].operand2<<" ;\n";
	}
}
