#include<iostream.h>
#include<conio.h>

#define OVER 1
#define RUNNING 0

#define MAX 1000
#define MIN -1

class CPU
{
	int n;
	int alljobover;
	int GANTT[50];
	int totaltime;
	int quantum;

	public:

	CPU()
	{
		alljobover = RUNNING;
		totaltime = 0;
		quantum = 4;//by default its 4 in my code
	}

	struct JOB
	{
		int arrtime,bursttime,waittime,endtime,turntime;
		int jobover,served;
		int priority;  //0->lowest priority
	}*job;

	void refreshGantt();
	void displayResult();
	int nextSJ(int);
	int nextPRJ(int);

	void FCFS();
	void SJFPreemptive();
	void PRPreemptive();
	void roundRobin();

};

int main()
{
	CPU cpu;

	clrscr();
	cpu.refreshGantt();

/****** uncomment the one u wanna run  & comment all others ********/

//	cpu.FCFS();
//	cpu.SJFPreemptive();
//	cpu.PRPreemptive();
	cpu.roundRobin();

	getch();
	return 0;
}

//displayResult
void CPU::displayResult()
{
	int i,j;

	//calculate result
	for(i=0;i<n;i++)
	{
		for(j=totaltime-1;j>=0;j--)
		{
			if(GANTT[j]==i)
			{
				job[i].endtime = j+1;
				break;
			}
		}

		//turntime = endtime - arrtime
		job[i].turntime = job[i].endtime - job[i].arrtime;

		//waittime = turntime - bursttime
		job[i].waittime = job[i].turntime - job[i].bursttime;
	}

	cout<<"\n\nRESULTS:\n\nSNO\tA\tB\tE\tW\tT\n\n";
	//display result now
	for(i=0;i<n;i++)
	{
		cout<<i<<":\t"<<job[i].arrtime<<"\t";
		cout<<job[i].bursttime<<"\t";
		cout<<job[i].endtime<<"\t";
		cout<<job[i].waittime<<"\t";
		cout<<job[i].turntime<<"\n";
	}

	getch();
	cout<<"\n\nGANTT CHART:\n\n";
	for(i=0;i<totaltime;i++)
	{
		cout<<i<<"-"<<i+1<<" :\t"<<GANTT[i]<<"\n";

		if(i%10==0 && i!=0)
			getch();
	}


	totaltime = 0;
	alljobover = RUNNING;
}

//refresh gantt
void CPU::refreshGantt()
{
	int i;

	for(i=0;i<50;i++)
	{
		GANTT[i] = -1;
	}
}

//round robin
void CPU::roundRobin()
{

	int i,curjob;

	cout<<"Enter the number of jobs:\t";
	cin>>n;

	job = new JOB[n];

	cout<<"\nEnter the quantum of time:\t";
	cin>>quantum;

	for(i=0;i<n;i++)
	{
		cout<<"\nEnter the arrival time of job "<<i<<":\t";
		cin>>job[i].arrtime;

		cout<<"Enter the burst time of job "<<i<<":\t";
		cin>>job[i].bursttime;

		cout<<"\n";

		job[i].jobover = RUNNING;
		job[i].served = 0;
	}

	i = 0;
	totaltime = 0;
	alljobover = 0;
	curjob = -1;

	while(alljobover!=n)
	{
		i = 0;
		while(i!=n)
		{
			if(++curjob==n)
				curjob = 0;

			if(job[curjob].arrtime <= totaltime && job[curjob].jobover==RUNNING)
				break;

			i++;
		}

		if(i==n)
		{
			totaltime++;
			continue;
		}

		for(i=0;i<4;i++)
		{
			GANTT[totaltime++] = curjob;
			job[curjob].served++;

			if(job[curjob].served == job[curjob].bursttime)
			{
				job[curjob].jobover = OVER;
				alljobover++;
				break;
			}
		}

	}

	displayResult();

}

//next PRJ
int CPU::nextPRJ(int curtime)
{
	int i;
	int ret = -1;
	int priority = MIN;

	for(i=0;i<n;i++)
	{
		if(job[i].arrtime<=curtime && job[i].jobover==RUNNING)
		{
			if(job[i].priority > priority)
			{
				ret = i;
				priority = job[i].priority;
			}
		}
	}

	return ret;
}

//PRIORITY Preemptive
void CPU::PRPreemptive()
{

	int i,retjob;

	cout<<"Enter the number of jobs:\t";
	cin>>n;

	job = new JOB[n];

	for(i=0;i<n;i++)
	{
		cout<<"Enter the arrival time of job "<<i<<":\t";
		cin>>job[i].arrtime;

		cout<<"Enter the burst time of job "<<i<<":\t";
		cin>>job[i].bursttime;

		cout<<"Enter the priority of the job "<<i<<":\t";
		cin>>job[i].priority;

		job[i].jobover = RUNNING;
		job[i].served = 0;
	}

	i = 0;
	totaltime = 0;
	alljobover = 0;
	while(alljobover!=n)
	{
		retjob = nextSJ(totaltime);
		GANTT[totaltime++] = retjob;

		if(retjob!=-1)
		{
			job[retjob].served++;

			if(job[retjob].served==job[retjob].bursttime)
			{
				job[retjob].jobover = OVER;
				alljobover++;
			}
		}
	}

	displayResult();
}

int CPU::nextSJ(int curtime)
{
	int i;
	int ret = -1;
	int bsttime = MAX;

	for(i=0;i<n;i++)
	{
		if(job[i].arrtime<=curtime && job[i].jobover==RUNNING)
		{
			if(job[i].bursttime < bsttime)
			{
				ret = i;
				bsttime = job[i].bursttime;
			}
		}
	}

	return ret;
}

//SJF Preemptive
void CPU::SJFPreemptive()
{
	int i,retjob;

	cout<<"Enter the number of jobs:\t";
	cin>>n;

	job = new JOB[n];

	for(i=0;i<n;i++)
	{
		cout<<"Enter the arrival time of job "<<i<<":\t";
		cin>>job[i].arrtime;

		cout<<"Enter the burst time of job "<<i<<":\t";
		cin>>job[i].bursttime;

		job[i].jobover = RUNNING;
		job[i].served = 0;
	}

	i = 0;
	totaltime = 0;
	alljobover = 0;
	while(alljobover!=n)
	{
		retjob = nextSJ(totaltime);
		GANTT[totaltime++] = retjob;

		if(retjob!=-1)
		{
			job[retjob].served++;

			if(job[retjob].served==job[retjob].bursttime)
			{
				job[retjob].jobover = OVER;
				alljobover++;
			}
		}
	}

	displayResult();

}

//FCFS
void CPU::FCFS()
{
	int i;

	cout<<"Enter the number of jobs:\t";
	cin>>n;

	job = new JOB[n];

	for(i=0;i<n;i++)
	{
		cout<<"Enter the arrival time of job "<<i<<":\t";
		cin>>job[i].arrtime;

		cout<<"Enter the burst time of job "<<i<<":\t";
		cin>>job[i].bursttime;

		job[i].jobover = RUNNING;
		job[i].served = 0;
	}

	for(i=0,totaltime=0;i<n;i++)
	{
		while(job[i].arrtime>totaltime)
			totaltime++;

		while(job[i].jobover==RUNNING)
		{
			GANTT[totaltime++] = i;
			job[i].served++;

			if(job[i].served==job[i].bursttime)
				job[i].jobover = OVER;
		}
		job[i].jobover = OVER;
		alljobover++;
	}

	displayResult();

}
