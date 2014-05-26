#include<iostream>
#include<errno.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

#define MAX_MACHINES_SUPPORT 10
#define MYPRIORITY 9

using namespace std;

enum Status{

	NORMAL,ABNORMAL
};

enum MsgCode{
	IAM_NEWBIE,IAM_COORDINATOR,MACHINE_DEAD,HELLO,COORDINATOR_DEAD_START_ELECTION,HELLO_REPLY
};

struct Message{

	int msgcode;
	int msgsender;
	int msgactor;
};

void* coordinatorfinder(void*);
void* hellomsgsender(void*);

class BullyAlgorithm{
	
	const int SERVICEPORT,SOCKET_QUEUESIZE,MESSAGE_SIZE;
	
	int socketfd;
	int mypriority;
	int coordinator;

	Message message_send;
	Message message_recv;

	struct MachineStat{
		bool machinealive;
		bool hellorecv;
		char machineip[16];
	}machinetable[MAX_MACHINES_SUPPORT];

public:

	BullyAlgorithm():SERVICEPORT(888),SOCKET_QUEUESIZE(5),MESSAGE_SIZE(sizeof(Message)){
		mypriority = MYPRIORITY;
		coordinator = -1;
	}

	int initBullyAlgo();
	void setMessage(int,int,int);

	friend void* coordinatorfinder(void*);
	friend void* hellomsgsender(void *);
};

void* coordinatorfinder(void *param){

	BullyAlgorithm *bully = (BullyAlgorithm *) param;	

	sleep(3);

	if(bully->coordinator == -1){
		bully->coordinator = bully->mypriority;
		bully->mypriority = bully->mypriority;

		bully->machinetable[bully->mypriority].machinealive = true;
	
		cout<<"Status: No coordinator found. Declaring self as the coordinator\n";
	}	
	
	return (void*)NULL;
}

void* hellomsgsender(void *param){
	
BullyAlgorithm *bully = (BullyAlgorithm *)param;

	int machinenum;
	struct sockaddr_in broadcastsendaddr;
	struct sockaddr_in recvaddr;
	struct sockaddr_in sendaddr;
	socklen_t recvaddrlen;
	char broadcastip[16] = "192.168.1.255";
  Message message_send,message_recv;

	bzero(&broadcastsendaddr,sizeof(broadcastsendaddr));
	bzero(&sendaddr,sizeof(sendaddr));

	sendaddr.sin_family = AF_INET;
	sendaddr.sin_port = htons(bully->SERVICEPORT);

	broadcastsendaddr.sin_family = AF_INET;
	inet_pton(AF_INET,broadcastip,(void*)&broadcastsendaddr.sin_addr.s_addr);
	broadcastsendaddr.sin_port = htons(bully->SERVICEPORT);
	

	while(1){
		sleep(5);
	
		do{
			machinenum = rand() % 10;
		}while(bully->machinetable[machinenum].machinealive==false || (machinenum > (MAX_MACHINES_SUPPORT-1)) || machinenum==bully->mypriority);
	
		bully->machinetable[machinenum].hellorecv = false;

		message_send.msgcode = HELLO;
		message_send.msgsender = bully->mypriority;
		message_send.msgactor = machinenum;
	
		inet_pton(AF_INET,bully->machinetable[machinenum].machineip,(void*)&sendaddr.sin_addr.s_addr);
	
		if(sendto(bully->socketfd,(void *)&message_send,sizeof(message_send),0,(struct sockaddr*)&sendaddr,sizeof(sendaddr)) == -1){
			cout<<"sending hello failed\t"<<strerror(errno)<<"\n";
			return (void*)ABNORMAL;
		}

		cout<<"Status: Hello msg sent to machine "<<machinenum<<" with IP address "<<bully->machinetable[machinenum].machineip<<"\n";
		sleep(3);	
	
	  if(bully->machinetable[machinenum].hellorecv == false){
			//machine is dead...broadcast for election if necessary

			cout<<"Status: Found machine "<<machinenum<<" to be dead\n";	
			bully->machinetable[machinenum].machinealive = false;

			message_send.msgcode = MACHINE_DEAD;
			message_send.msgsender = bully->mypriority;
			message_send.msgactor = machinenum;
						
			inet_pton(AF_INET,broadcastip,(void*)&sendaddr.sin_addr.s_addr);
			if(sendto(bully->socketfd,(void *)&message_send,sizeof(message_send),0,(struct sockaddr*)&broadcastsendaddr,sizeof(broadcastsendaddr)) == -1){
				cout<<"announcing machine dead failed\t"<<strerror(errno)<<"\n";
				return (void*)ABNORMAL;
			}

			cout<<"Status: Broadcasted the machine dead status for machine "<<machinenum<<" to everyone\n";
			if(machinenum == bully->coordinator){
				message_send.msgcode = COORDINATOR_DEAD_START_ELECTION;
				message_send.msgsender = bully->mypriority;
				message_send.msgactor = machinenum;
		
				cout<<"Status: The machine "<<machinenum<<" was a coordinator\n";		
	
				int i;
				for(i=bully->mypriority;i<MAX_MACHINES_SUPPORT;i++){
					inet_pton(AF_INET,bully->machinetable[i].machineip,(void*)&sendaddr.sin_addr.s_addr);
					if(sendto(bully->socketfd,(void *)&message_send,sizeof(message_send),0,(struct sockaddr*)&sendaddr,sizeof(sendaddr)) == -1){
						cout<<"announcing machine dead failed\t"<<strerror(errno)<<"\n";
						return (void*)ABNORMAL;
					}
		
					cout<<"Status: Sent the coordinator dead and start election message to machine "<<machinenum<<"\n";
				}
			}
		}
	}
}

int main(){

	BullyAlgorithm *p = new BullyAlgorithm();

	srand((unsigned)time(NULL));

	if(p->initBullyAlgo() == ABNORMAL)
		return ABNORMAL;

	return 0;
}

void BullyAlgorithm::setMessage(int msgcode,int firstp,int thirdp){

	message_send.msgcode = msgcode;
	message_send.msgsender = firstp;
	message_send.msgactor = thirdp;

}

int BullyAlgorithm::initBullyAlgo(){

	struct sockaddr_in servaddr;
	struct sockaddr_in broadcastsendaddr;
	struct sockaddr_in recvaddr;
	struct sockaddr_in sendaddr;
	
	socklen_t recvaddrlen;

	char broadcastip[16] = "192.168.1.255";
	int broadcaston = 1;

	for(int i=0;i<MAX_MACHINES_SUPPORT;i++)
		machinetable[i].machinealive = false;


	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERVICEPORT);

	socketfd = socket(AF_INET,SOCK_DGRAM,0);

	if(socketfd == -1){
		cout<<"getting socket descriptor\t"<<strerror(errno)<<"\n";
		return ABNORMAL;
	}
	
	if(bind(socketfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1){
		cout<<"binding the socket\t"<<strerror(errno)<<"\n";
		return ABNORMAL;
	}

	//setsocketoptions to broadcast
	if(setsockopt(socketfd,SOL_SOCKET,SO_BROADCAST,&broadcaston,sizeof(broadcaston)) == -1){
		cout<<"set socket opt to broadcast\t"<<strerror(errno)<<"\n";
		return ABNORMAL;
	}
	
	//broadcast your presence	
	bzero(&broadcastsendaddr,sizeof(broadcastsendaddr));
	bzero(&sendaddr,sizeof(sendaddr));

	sendaddr.sin_family = AF_INET;
	sendaddr.sin_port = htons(SERVICEPORT);

	broadcastsendaddr.sin_family = AF_INET;
	inet_pton(AF_INET,broadcastip,(void*)&broadcastsendaddr.sin_addr.s_addr);
	broadcastsendaddr.sin_port = htons(SERVICEPORT);
	
	setMessage(IAM_NEWBIE,mypriority,mypriority);	
	if(sendto(socketfd,(void *)&message_send,sizeof(message_send),0,(struct sockaddr*)&broadcastsendaddr,sizeof(broadcastsendaddr)) == -1){
		cout<<"announcing newbie failed\t"<<strerror(errno)<<"\n";
		return ABNORMAL;
	}

	pthread_t coordinatefinder;
	if(pthread_create(&coordinatefinder,NULL,coordinatorfinder,this)!=0){
		cout<<"could not invoke coordinator finder\t"<<strerror(errno)<<"\n";
		return ABNORMAL;
	}
	
	//pthread_join(coordinatefinder,NULL);
	
	if(pthread_create(new pthread_t,NULL,hellomsgsender,this)!=0){
		cout<<"could not invoke hellomsgsender finder\t"<<strerror(errno)<<"\n";
		return ABNORMAL;
	}

	while(1){

		recvfrom(socketfd,(void*)&message_recv,sizeof(message_recv),0,(struct sockaddr*)&recvaddr,&recvaddrlen);

		if(message_recv.msgsender == mypriority && message_recv.msgcode!=COORDINATOR_DEAD_START_ELECTION){
			cout<<"Got a self message from "<<message_recv.msgsender<<" : Ignoring it\n";
			continue;
		}

		switch(message_recv.msgcode){

			case IAM_NEWBIE: 	cout<<"Message recieved:\t"<<"I am Newbie looking for the coordinator.\n";
												cout<<"Message Sender:\t"<<message_recv.msgsender<<"\n"; 											
												cout<<"Message Actor:\t"<<message_recv.msgactor<<"\n";
												
												inet_ntop(AF_INET,(void*)&recvaddr.sin_addr.s_addr,machinetable[message_recv.msgsender].machineip,15);
												sendaddr.sin_addr.s_addr = recvaddr.sin_addr.s_addr;

												message_send.msgcode = IAM_COORDINATOR;
												message_send.msgsender = mypriority;
												message_send.msgactor = coordinator;
												if(sendto(socketfd,(void *)&message_send,sizeof(message_send),0,(struct sockaddr*)&sendaddr,sizeof(sendaddr)) == -1){
													cout<<"telling newbie about coordinator failed\t"<<strerror(errno)<<"\n";
													return ABNORMAL;
												}
												
												
												machinetable[message_recv.msgsender].machinealive = true;
												break;

			case IAM_COORDINATOR:	cout<<"Message recieved:\t"<<"I am the coordinator.\n";
														cout<<"Message Sender:\t"<<message_recv.msgsender<<"\n"; 											
														cout<<"Message Actor:\t"<<message_recv.msgactor<<"\n";
														
														machinetable[message_recv.msgsender].machinealive = true;
														inet_ntop(AF_INET,(void*)&recvaddr.sin_addr.s_addr,machinetable[message_recv.msgsender].machineip,15);
		
														if(message_recv.msgactor > mypriority){ 
															coordinator = message_recv.msgactor;
															cout<<"Status: Got the new coordinator as "<<coordinator<<"\n";
														}
														else{ //I am coordinator
																coordinator = message_recv.msgactor;					
																setMessage(IAM_COORDINATOR,mypriority,mypriority);
																if(sendto(socketfd,(void *)&message_send,sizeof(message_send),0,(struct sockaddr*)&broadcastsendaddr,sizeof(broadcastsendaddr)) == -1){
																cout<<"telling newbie about coordinator failed\t"<<strerror(errno)<<"\n";
																return ABNORMAL;
																}
																cout<<"Status: Broadcasted that I am the new coordinator\n";
													}											
													
																																									 
														

														break;

			case HELLO_REPLY:		cout<<"Message recieved:\tHello's Reply\n";
													cout<<"Message Sender:\t"<<message_recv.msgsender<<"\n"; 											
													cout<<"Message Actor:\t"<<message_recv.msgactor<<"\n";
													machinetable[message_recv.msgsender].hellorecv = true;	
													break;


			case HELLO:					cout<<"Message recieved:\tHello\n";
													cout<<"Message Sender:\t"<<message_recv.msgsender<<"\n"; 											
													cout<<"Message Actor:\t"<<message_recv.msgactor<<"\n";
																									
													message_send.msgcode = HELLO_REPLY;	
													message_send.msgsender = mypriority;
													message_send.msgactor = message_recv.msgsender;									
	
													sendaddr.sin_addr.s_addr = recvaddr.sin_addr.s_addr;
													if(sendto(socketfd,(void *)&message_send,sizeof(message_send),0,(struct sockaddr*)&sendaddr,sizeof(sendaddr)) == -1){
														cout<<"sending hello reply failed\t"<<strerror(errno)<<"\n";
														return ABNORMAL;
													}

													break;

			case MACHINE_DEAD:	cout<<"Message recieved:\t"<<"Machine Dead\n";
													cout<<"Message Sender:\t"<<message_recv.msgsender<<"\n"; 											
													cout<<"Message Actor:\t"<<message_recv.msgactor<<"\n";
													machinetable[message_recv.msgactor].machinealive = false;	
													break;


			case COORDINATOR_DEAD_START_ELECTION:	cout<<"Message recieved:\t"<<"Coordinator Dead\n";
													cout<<"Message Sender:\t"<<message_recv.msgsender<<"\n"; 											
													cout<<"Message Actor:\t"<<message_recv.msgactor<<"\n";
													
													cout<<"Status: Found that the coordinator machine "<<message_recv.msgactor<<" is dead\n";
													setMessage(IAM_COORDINATOR,mypriority,mypriority);
													if(sendto(socketfd,(void *)&message_send,sizeof(message_send),0,(struct sockaddr*)&broadcastsendaddr,sizeof(broadcastsendaddr)) == -1){
														cout<<"telling newbie about coordinator failed\t"<<strerror(errno)<<"\n";
														return ABNORMAL;
													}
													cout<<"Status: Broadcasted that I am the new coordinator\n";
													coordinator = mypriority;
			
			default: cout<<"Unknown code recieved";						
		}	
	}	
	
	return NORMAL;

}
