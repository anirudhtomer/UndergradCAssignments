#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<fcntl.h>

int main(){

	struct sockaddr_in sockserv,sockclient;
	int socketfd,clientfd;
	socklen_t clientsocklen;
	int filefd;
	int count1,cnt;
	int totalcnt;
		
	char buff[BUFSIZ],buff2[BUFSIZ];
	char *ptr,strtemp[20];
	int strcnt;
	 
	filefd = open("/home/anirudh/Videos/fast_boot.ogg",O_RDONLY);
	printf("File Open: %s\n",strerror(errno));

	socketfd = socket(AF_INET,SOCK_STREAM,0);	
	printf("Socket Creation: %s\n",strerror(errno));

	bzero(&sockserv,sizeof(sockserv));

	sockserv.sin_family = AF_INET;
	sockserv.sin_addr.s_addr = INADDR_ANY;
	sockserv.sin_port = htons(80);

	bind(socketfd,(struct sockaddr *)&sockserv,sizeof(sockserv));
	printf("Socket Bind: %s\n",strerror(errno));

	listen(socketfd,10);
	printf("Socket Listen: %s\n",strerror(errno));


	clientfd = accept(socketfd,(struct sockaddr*) &sockclient,&clientsocklen);
	
	buff[read(clientfd,buff,BUFSIZ)] = '\0';
	printf("Request recieved as \n%s\n",buff);	


	cnt = read(filefd,buff2,1025);
	sprintf(buff,"HTTP/1.1 206 Partial Content\r\nContent-Type: video/ogg\r\nDate: Mon, 28 Feb 2011 10:38:19 GMT\r\nContent-Range: bytes 0-1024/1915873\r\nTransfer-Encoding: chunked\r\nServer: Myserver\r\n\r\n%x\r\n",cnt);

	count1 = strlen(buff);
	memcpy(buff + count1,buff2,cnt);	
	memcpy(buff + count1 + cnt,"\r\n0\r\n\r\n",strlen("\r\n0\r\n\r\n"));
	
	cnt = send(clientfd,buff,count1 + cnt + strlen("\r\n0\r\n\r\n"),0);
	printf("Data sent to the client %d bytes: %s",cnt,strerror(errno));

//	totalcnt = 1025;
	while(1){

		cnt = read(clientfd,buff,BUFSIZ);
		if(cnt <= 0)
			break;
		
		buff[cnt] = '\0';
		printf("Request recieved as \n%s\n",buff);	

		ptr = strstr(buff,"bytes=") + strlen("bytes=");
		strcnt = 0;
		while(*ptr!='-'){
			strtemp[strcnt] = *ptr;	
			strcnt++;
			ptr++;
		}	
		strtemp[strcnt] = '\0';

		printf("strcnt = %s\n",strtemp);

		lseek(filefd,atoi(strtemp),0);
		cnt = read(filefd,buff2,6000);
		sprintf(buff,"HTTP/1.1 206 Partial Content\r\nContent-Type: video/ogg\r\nDate: Mon, 28 Feb 2011 10:38:19 GMT\r\nContent-Range: bytes %d-%d/1915873\r\nTransfer-Encoding: chunked\r\nServer: Myserver\r\n\r\n%x\r\n",atoi(strtemp),atoi(strtemp) + cnt - 1,cnt);

		count1 = strlen(buff);
		memcpy(buff + count1,buff2,cnt);
		memcpy(buff + count1 + cnt,"\r\n0\r\n\r\n",strlen("\r\n0\r\n\r\n"));
	
		cnt = send(clientfd,buff,count1 + cnt + strlen("\r\n0\r\n\r\n"),0);
		printf("Data sent to the client %d bytes: %s\n",cnt,strerror(errno));
	}

	close(clientfd);
	close(socketfd);
	
	return 0;
}
