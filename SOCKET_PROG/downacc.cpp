#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<arpa/inet.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>

#define THREAD_COUNT 10

using namespace std;

class DownAcc{

	char ip[16];
	char hostname[100];
	char filename[200];
 
	struct sockaddr_in serveraddr;

	char savefileat[200];

	char tempstr[2000];
	int filesize;
	int chunksize;
public:
	void setFileSize();	
	int getContentLength(char *);
	void setIPfromHostName();
	void setParam(char *,char *,char*);
	void startDownload();

	char *getIP(){
		return ip;
	}

	friend void* threadDownload(void*);
};

struct Param{

	DownAcc *downacc;
	int startbyteoffset;	
	int threadno;
	
};

void* threadDownload(void *param){

	DownAcc *downacc = ((struct Param *) param)->downacc;
	int startbyteoffset = ((struct Param*) param)->startbyteoffset;
	int threadno = 	((struct Param*) param)->threadno;

	int socketfd;
	char buffer[BUFSIZ*2];
	char getstr[1000];
	int totalcnt = 0;
	int tempcnt;
	int endbyteoffset = (startbyteoffset + downacc->chunksize - 1) > downacc->filesize ? downacc->filesize - 1 : (startbyteoffset + downacc->chunksize - 1);
	int chunksize = endbyteoffset - startbyteoffset + 1;
	char *ptr;


	cout<<"THREAD NO = "<<threadno<<"  "<<startbyteoffset<<"--"<<endbyteoffset<<"\n";

	//sleep(50);
	socketfd = socket(AF_INET,SOCK_STREAM,0);
//	printf("socket creation: %s\n",strerror(errno));

	connect(socketfd,(struct sockaddr*)&(downacc->serveraddr),sizeof(downacc->serveraddr));		
	//printf("Connecting to server: %s\n",strerror(errno));

	int fd = open(downacc->savefileat,O_WRONLY);

	sprintf(getstr,"GET /%s HTTP/1.1\r\nHost: %s\r\nConnection: keep-alive\r\nUser-Agent: Download_Accelerator\r\nAccept-Encoding: gzip,deflate,sdch\r\nAccept-Language: en-US,en;q=0.8\r\nAccept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.3\r\nRange: bytes=%d-%d\r\n\r\n",downacc->filename,downacc->hostname,startbyteoffset,endbyteoffset);

//	cout<<getstr<<"\n\n";
	write(socketfd,getstr,strlen(getstr));
//	cout<<"sending get request: "<<strerror(errno)<<endl;

	tempcnt = read(socketfd,buffer,BUFSIZ*2);
	cout<<"THREAD NO = "<<threadno<<"  "<<"read "<<tempcnt<<" bytes from the server\n";	
		
	ptr = strstr(buffer,"\r\n\r\n") + strlen("\r\n\r\n");
	tempcnt = tempcnt - (int)(ptr - buffer);
		
//	do{
	while(1){
		cout<<"THREAD NO = "<<threadno<<"  "<<"Seeking to position "<<lseek(fd,startbyteoffset + totalcnt,SEEK_SET)<<" in the file\n";
		cout<<"THREAD NO = "<<threadno<<"  "<<"Written "<<write(fd,ptr,tempcnt)<<" bytes to the file\n";
		totalcnt += tempcnt;
	
		if(totalcnt >= chunksize)
			break;
		tempcnt = read(socketfd,buffer,BUFSIZ*2);	
		ptr = buffer;
	}//while(totalcnt < chunksize);

	close(fd);
	close(socketfd);
	return (void*) 0;

}

int DownAcc::getContentLength(char *buff){
	char *ptr;
	int cnt=0;
	char contentlengtharr[20];

	ptr = strcasestr(buff,"Content-length: ") + strlen("content-length: ");

	while(*ptr!='\r')
		contentlengtharr[cnt++] = *(ptr++);
	
	contentlengtharr[cnt] = '\0';

	cout<<contentlengtharr<<"\n";
	return atoi(contentlengtharr);
}

void DownAcc::setFileSize(){

	char *ptr;
	int cnt = 0;
	char filesizearr[20];

  ptr = strstr(tempstr,"Content-Range");
	ptr = strchr(ptr,'/') + 1;

	while(*ptr != '\r'){
		filesizearr[cnt] = *ptr;
		cnt++;
		ptr++;
	}
	
	filesizearr[cnt] = '\0';

	filesize = atoi(filesizearr);
}

void DownAcc::setIPfromHostName(){

	struct hostent *hostentry;
	
	hostentry = gethostbyname(hostname);

	if(hostentry==NULL){
		cout<<"HOST NOT REACHABLE\n";
		exit(1);
	}
	
	inet_ntop(AF_INET,(void *) hostentry->h_addr_list[0],ip,15);


	printf("IP Address of the host %s is %s\n",hostname,ip);
}

void DownAcc::setParam(char *host,char *file,char *saveat){

	strcpy(hostname,host);
	strcpy(filename,file);
	strcpy(savefileat,saveat);

	creat(savefileat,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	
}

//program_name,hostname,filename...  e.g->      ./a.out www.w3schools.com sql/default.asp
int main(int argc,char *argv[]){

	DownAcc downloadacc;

	downloadacc.setParam(argv[1],argv[2],argv[3]);
	downloadacc.setIPfromHostName();
	downloadacc.startDownload();
	return 0;

}

void DownAcc::startDownload(){
	
	int socketfd;	
	pthread_t threaddownacc[THREAD_COUNT];
	struct Param *paramarr = new struct Param[THREAD_COUNT];
 
	socketfd = socket(AF_INET,SOCK_STREAM,0);
	printf("Socket connection: %s\n",strerror(errno));

	bzero(&serveraddr,sizeof(serveraddr));	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(80);
	inet_pton(AF_INET,getIP(),(void *) &(serveraddr.sin_addr.s_addr));
	
	sprintf(tempstr,"GET /%s HTTP/1.1\r\nHost: %s\r\nConnection: keep-alive\r\nUser-Agent: Download_Accelerator\r\nAccept-Encoding: gzip,deflate,sdch\r\nAccept-Language: en-US,en;q=0.8\r\nAccept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.3\r\nRange: bytes=0-1024\r\n\r\n",filename,hostname);

	connect(socketfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));		
	printf("Connecting to server: %s\n",strerror(errno));

	write(socketfd,tempstr,strlen(tempstr));	
	printf("Writing to server: %s\n",strerror(errno));
	
	int cnt = read(socketfd,tempstr,2000);	
	tempstr[cnt] = '\0';

	printf("%d bytes of Data read from the server :\n\n%s\n",cnt,tempstr);
	
	setFileSize();

	cout<<"content length recieved as: "<<getContentLength(tempstr)<<endl;

	int fd = open(savefileat,O_WRONLY);
	char *ptr = strstr(tempstr,"\r\n\r\n") + strlen("\r\n\r\n");
	
	write(fd,ptr,1025);
	close(fd);
	close(socketfd);

	if(filesize < 1025)
		return;

	if( (filesize - 1025) < 10000 ){ 
//its just one of the cases...this download acc is still dumb...I hate to HARD CODE THINGS
		chunksize = filesize - 1025;
		paramarr[0].downacc = this;
		paramarr[0].startbyteoffset = 1025;
		paramarr[0].threadno = 0;
		pthread_create(&threaddownacc[0],NULL,threadDownload,(void*)&paramarr[0]);
		pthread_join(threaddownacc[0],NULL);
		return;
	}
	else
		chunksize = (filesize-1025)/(THREAD_COUNT - 1);

	int prevcnt = 1025;
	
	for(int i=0;i<THREAD_COUNT;i++){
		
		paramarr[i].downacc = this;
		paramarr[i].startbyteoffset = prevcnt;  
		paramarr[i].threadno = i;
		pthread_create(&threaddownacc[i],NULL,threadDownload,(void*)&paramarr[i]);
	
		prevcnt += chunksize;
	}
	
	for(int i=0;i<THREAD_COUNT;i++){
		pthread_join(threaddownacc[i],NULL);
	}	
	

}


