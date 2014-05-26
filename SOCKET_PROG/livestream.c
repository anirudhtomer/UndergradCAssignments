#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<signal.h>
#include<unistd.h>

int main(){

	struct sockaddr_in sockserv,sockclient;
	int socketfd,clientfd;
	socklen_t clientsocklen;
	int filefd;
	int cnt;
	int finalcnt = 0;
	int chancecnt;
	
	char buff[BUFSIZ],buff2[BUFSIZ];

	signal(SIGPIPE,SIG_IGN);
	printf("Signal handler for SIGPIPE over ridden : %s\n",strerror(errno));


	socketfd = socket(AF_INET,SOCK_STREAM,0);	
	printf("Socket Creation: %s\n",strerror(errno));

	filefd = open("/home/anirudh/Videos/fast_boot.ogg",O_RDONLY);
	printf("File open: %s\n",strerror(errno));

	bzero(&sockserv,sizeof(sockserv));

	sockserv.sin_family = AF_INET;
	sockserv.sin_addr.s_addr = INADDR_ANY;
	sockserv.sin_port = htons(8500);

	/*sockintermediate.sin_family = AF_INET;
	inet_pton(AF_INET,"127.0.0.1",(void*)&sockintermediate.sin_addr.s_addr);
	sockintermediate.sin_port = htons(81);
	*/

	bind(socketfd,(struct sockaddr *)&sockserv,sizeof(sockserv));
	printf("Socket Bind: %s\n",strerror(errno));

	listen(socketfd,10);
	printf("Socket Listen: %s\n",strerror(errno));

	clientfd = accept(socketfd,(struct sockaddr*)&sockclient,&clientsocklen);
	printf("1st Request accepted\n");

	read(clientfd,buff,BUFSIZ);
	printf("%s\n\n",buff);

	strcpy(buff,"HTTP/1.0 200 OK\r\nDate: Tue, 01 Mar 2011 06:14:58 GMT\r\nConnection: close\r\nCache-control: private\r\nContent-type: video/ogg\r\nServer: lighttpd/1.4.26\r\n\r\n");

	cnt = send(clientfd,buff,strlen(buff),0);
	printf("Sent this reply : %s \nwith size = %d : %s\n",buff,cnt,strerror(errno));

	int xcnt = 0;
	while(1){
	
		cnt = read(filefd,buff,1025);
		printf("Read %d bytes from the file : %s\n",cnt,strerror(errno));		
	
		if(xcnt==7)
          break;
                    else if(xcnt > 0 && cnt != 0)
                      xcnt = 0;
                    else if(xcnt >=0 && cnt == 0){
                      sleep(1);
                      xcnt++;
                      continue;
                    }

	
		finalcnt = send(clientfd,buff,cnt,0);
		printf("Data written = %d bytes: %s\n",finalcnt,strerror(errno));
	
		if(finalcnt <= 0){
			memcpy(buff2,buff,cnt);				
			finalcnt = cnt;
			close(clientfd);
			printf("%s\n",strerror(errno));
			break;
		}
	}

	clientfd = accept(socketfd,(struct sockaddr*)&sockclient,&clientsocklen);
	printf("2nd Request accepted\n");

	read(clientfd,buff,BUFSIZ);
	printf("%s\n\n",buff);

	strcpy(buff,"HTTP/1.0 200 OK\r\nDate: Tue, 01 Mar 2011 06:14:58 GMT\r\nConnection: close\r\nCache-control: private\r\nContent-type: video/webm\r\nServer: lighttpd/1.4.26\r\n\r\n");

	cnt = send(clientfd,buff,strlen(buff),0);
	printf("Sent this reply : %s \nwith size = %d : %s\n",buff,cnt,strerror(errno));


	lseek(filefd,0,0);
	while(1){
	
		cnt = read(filefd,buff,1025);
		//printf("Read %d bytes from the file : %s\n",cnt,strerror(errno));		
			if(xcnt==7)
          break;
                    else if(xcnt > 0 && cnt != 0)
                      xcnt = 0;
                    else if(xcnt >=0 && cnt == 0){
                      sleep(1);
                      xcnt++;
                      continue;
                    }



		finalcnt = send(clientfd,buff,cnt,0);
//		printf("Data written = %d bytes: %s\n",finalcnt,strerror(errno));

		if(finalcnt <= 0){
			break;
		}

	}
	
	close(clientfd);
	close(socketfd);
	
	return 0;
}
