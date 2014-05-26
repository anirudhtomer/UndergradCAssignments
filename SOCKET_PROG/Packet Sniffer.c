//PACKET SNIFFER IN PROMISCUOUS MODE

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<features.h>
#include<linux/if_packet.h>
#include<linux/if_ether.h>
#include<errno.h>
#include<sys/ioctl.h>
#include<net/if.h>
#include<linux/ip.h>
#include<linux/tcp.h>
#include<linux/udp.h>
#include<linux/icmp.h>
#include<linux/igmp.h>
#include<netinet/in.h>

#define PACKET_SIZE 2048
#define MAC_LENGTH 6

//function to activate promiscuous mode
int setpromisc(char *device,int set){

	int sock;
	struct ifreq eth;  //ifreq is the interface request structure
	struct packet_mreq mr;
		
	sock = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
	if( sock < 0)
	{
	    printf("Socket Errorn");
	    return 1;
	}
	
    //copy the device name interface request structure
	strcpy(eth.ifr_name, device);
	
	//request for the flags
	ioctl(sock, SIOCGIFFLAGS, &eth);
	
	//set the promiscuous flag
	if(set==1) //set the prmomisc flag	
		eth.ifr_flags |= IFF_PROMISC;
	else 
		eth.ifr_flags ^= IFF_PROMISC;
	
	//set the flag in device as well
	ioctl(sock, SIOCSIFFLAGS, &eth);

	//to make sure of other processess do not remove the promiscuous mode
	if(set==1)
	{
		memset(&mr,0,sizeof(mr));
		mr.mr_ifindex = eth.ifr_ifindex;
		mr.mr_type = PACKET_MR_PROMISC;
	
		setsockopt(sock,SOL_PACKET,PACKET_ADD_MEMBERSHIP,(char*)&mr,sizeof(mr));
	}
}

//function to create raw socket
int createSocket()
{
	int sock;

	sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	return sock;
}

//function to bind socket to a device
void bindSocket_Device(char *device,int sock,int protocol)
{
	int ioctlerr,binderr;	
	struct sockaddr_ll sll;
	struct ifreq ifr;

	//fill all the members of the structure as zero
	bzero(&sll,sizeof(sll));
	bzero(&ifr,sizeof(ifr));

	//get the interface index
	strcpy(ifr.ifr_name,device);
	
	ioctlerr = ioctl(sock,SIOCGIFINDEX,&ifr);	//#define SIOCGIFINDEX	0x8933		/* name -> if_index mapping	*/ to get interface index
	if(ioctlerr==-1)
	{
		printf("INTERFACE NAME CAN'T BE MAPPED TO INDEX");
		exit(1);
	}

	//BINDING RAW SOCKET TO INTERFACE
	sll.sll_family = AF_PACKET;  //packet family
	sll.sll_ifindex = ifr.ifr_ifindex; //interface index
	sll.sll_protocol = htons(protocol); //host to network byte ordering & protocol is given	

	binderr = bind(sock,(struct sockaddr *)&sll,sizeof(sll));
	if(binderr==-1)
	{
		printf("SOCKET CAN'T BE BOUND TO DEVICE %s",device);
		exit(1);
	}

}

void printHex(unsigned char *data,int len)
{
	int i;

	for(i=0;i<len;i++)
	{
		printf("%.2x ",*data);
		data++;
	}


}

//print the ethernet header
void printEthernetHeader(unsigned char *buffer,int len)
{
	struct ethhdr *ethernet_header;

	if(len >= sizeof(struct ethhdr))
	{
		ethernet_header = (struct ethhdr*)buffer;

		printf("Destination MAC Address: ");
		printHex(ethernet_header->h_dest,MAC_LENGTH);
		
		printf("\nSource MAC Address : ");
		printHex(ethernet_header->h_source,MAC_LENGTH);

		printf("\nProtocol : ");
		printHex((unsigned char*)&ethernet_header->h_proto,2);

	}
	else
	{
		printf("PACKET SIZE IS TOO SMALL :: ETHERNET\n");
	}	
}

//print the IP Header
void printIPHeader(unsigned char *buffer,int len)
{
	struct ethhdr *ethernet_header;
	struct iphdr *ip_header;

	ethernet_header = (struct ethhdr*)buffer;

	if(ntohs(ethernet_header->h_proto)==0x0800) //if its IP packet
	{
		if(len >= sizeof(struct ethhdr) + sizeof(struct iphdr))
		{	
			ip_header = (struct iphdr*)(buffer + sizeof(struct ethhdr));

			printf("IP Version : %d\n",(unsigned int)ip_header->version);
		    printf("IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)ip_header->ihl,((unsigned int)(ip_header->ihl))*4);
		    printf("Type Of Service : %d\n",(unsigned int)ip_header->tos);
		    printf("IP Total Length : %d\n",ntohs(ip_header->tot_len));
		    printf("Identification  : %d\n",ntohs(ip_header->id));
		    printf("TTL : %d\n",(unsigned int)ip_header->ttl);
		    printf("Protocol : %d\n",(unsigned int)ip_header->protocol);
		    printf("Checksum : %d\n",ntohs(ip_header->check));
		    printf("Destination IP : %s\n",inet_ntoa(ip_header->daddr));
		    printf("Source IP : %s\n",inet_ntoa(ip_header->saddr));

		}
		else
		{
			printf("\n\nPACKET SIZE IS TOO SMALL :: IP\n");
		}
	}	
	else
	{	
		printf("\n\nNon IP Packet : \n");
		printHex(buffer + sizeof(struct ethhdr),len);	
	}

}

//print the TCP header
void printTCPHeader(unsigned char *buffer,int len)
{
	struct ethhdr *ethernet_header;
	struct iphdr *ip_header;
	struct tcphdr *tcp_header;
	struct udphdr *udp_header;
	struct icmphdr *icmph;
	struct igmphdr *igmph;
	
	ethernet_header = (struct ethhdr *)buffer;

	if(ntohs(ethernet_header->h_proto) == ETH_P_IP)
	{
		ip_header = (struct iphdr *)(buffer + sizeof(struct ethhdr));

		switch(ip_header->protocol)
		{
			//FOR TCP PROTOCOL	
			case IPPROTO_TCP:	if(len >= (sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct tcphdr)))
								{
									tcp_header = (struct tcphdr*)(buffer + sizeof(struct ethhdr) + ip_header->ihl*4);
									/* Print the Dest and Src ports */
									printf("\n---TCP Packet---\n");
									printIPHeader(buffer,len);
			    					printf("\n\nSequence Number : %u\n",ntohl(tcp_header->seq));
			    					printf("Acknowledge Number : %u\n",ntohl(tcp_header->ack_seq));
			    					printf("Header Length : %d DWORDS or %d BYTES\n" ,(unsigned int)tcp_header->doff,(unsigned int)tcp_header->doff*4);
			    					printf("Urgent Flag : %d\n",(unsigned int)tcp_header->urg);
			    					printf("Acknowledgement Flag : %d\n",(unsigned int)tcp_header->ack);
			    					printf("Push Flag : %d\n",(unsigned int)tcp_header->psh);
			    					printf("Reset Flag : %d\n",(unsigned int)tcp_header->rst);
			    					printf("Synchronise Flag : %d\n",(unsigned int)tcp_header->syn);
			    					printf("Finish Flag : %d\n",(unsigned int)tcp_header->fin);
			    					printf("Window : %d\n",ntohs(tcp_header->window));
			    					printf("Checksum : %d\n",ntohs(tcp_header->check));
			    					printf("Urgent Pointer : %d\n",tcp_header->urg_ptr);
									printf("Dest Port : %d\n", ntohs(tcp_header->dest));	    
									printf("Source Port : %d\n", ntohs(tcp_header->source));

									printf("Data:\n");
								    printData(buffer + sizeof(struct iphdr) + tcp_header->doff*4 ,( len - tcp_header->doff*4 - ip_header->ihl * 4 ));
	 
								}
								else
								printf("\nInvalid TCP packet :\n");
					
								break;

			//FOR UDP PROTOCOL
			case IPPROTO_UDP:	if(len >= (sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr)))
								{
									udp_header = (struct udphdr*)(buffer + sizeof(struct ethhdr) + ip_header->ihl*4);
									printf("\n---UDP Packet---\n");
									printIPHeader(buffer,len);
									printf("Source Port      : %d\n" , ntohs(udp_header->source));
				    				printf("Destination Port : %d\n" , ntohs(udp_header->dest));
	   								printf("UDP Length       : %d\n" , ntohs(udp_header->len));
	    							printf("UDP Checksum     : %d\n" , ntohs(udp_header->check));
	 
	 				    		    printf("Data:\n");
	 					   			printData(buffer + sizeof(struct iphdr) + sizeof(struct udphdr) ,( len - sizeof(struct udphdr) - ip_header->ihl * 4 ));
								}
								else
									printf("Invalid UDP Packet...\n");			
						
								break;
			
			//FOR ICMP PACKET
			case IPPROTO_ICMP:	if(len >= (sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct icmphdr)))
								{
									icmph = (struct icmphdr *)(buffer + sizeof(struct ethhdr)+ip_header->ihl*4);
	 
									printf("\n---ICMP Header---\n");
									printIPHeader(buffer,len);
	    							printf("Type : %d\n",(unsigned int)(icmph->type));
	 		    
									if((unsigned int)(icmph->type) == 11)
		    						    printf("(TTL Expired)\n");
	    							else if((unsigned int)(icmph->type) == ICMP_ECHOREPLY)
		        						printf("(ICMP Echo Reply)\n");

	    							printf("Code : %d\n",(unsigned int)(icmph->code));
						    		printf("Checksum : %d\n",ntohs(icmph->checksum));
					
									printf("Data:\n");
				    			printData(buffer + sizeof(struct iphdr) + sizeof(struct icmphdr) ,( len - sizeof(struct icmphdr) - ip_header->ihl * 4 ));
								}
								else
									printf("Invalid ICMP Packet...\n");

								break;
			//FOR IGMP PACKET
			case IPPROTO_IGMP:	if(len >= (sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct igmphdr)))
								{
									igmph = (struct igmphdr *)(buffer + sizeof(struct ethhdr)+ip_header->ihl*4);
	 
									printf("\n---IGMP Header---\n");
									printIPHeader(buffer,len);
	    							printf("Type : %d\n",(unsigned int)(igmph->type));
						    		printf("Code : %d\n",(unsigned int)(igmph->code));
						    		printf("Checksum : %d\n",ntohs(igmph->csum));
									printf("Group : %d\n",inet_ntoa(igmph->group));
					
									printf("Data:\n");
					   			printData(buffer + sizeof(struct iphdr) + sizeof(struct igmphdr) ,( len - sizeof(struct igmphdr) - ip_header->ihl * 4 ));
							}
							else
								printf("Invalid IGMP Packet...\n");
				
							break;	

			default:		printf("Not an IP packet\n");

			}
			
	}
}

//function to catch all packets
void catchPackets(const int num,unsigned char* buffer,char *device,int sock)
{
	int i,length;
	struct sockaddr_ll packetinfo;
	int packetinfosize = sizeof(packetinfo);

	for(i=0;i<num;i++)
	{
		printf("\n\n");
		length = recvfrom(sock,buffer,PACKET_SIZE,0,(struct sockaddr*)&packetinfo,&packetinfosize);
		if(length==-1)
		{
			printf("CAN'T RECEIVE PACKET\n");
			return;
		}		
		else
		{
			printf("PACKET NUMBER %d\n",i+1);
			printEthernetHeader(buffer,length);
			//printIPHeader(buffer,length);
			printTCPHeader(buffer,length);
		}
	}

}


void printData (unsigned char* data , int Size)
{
	 
	    int i,j;
		for(i=0 ; i < Size ; i++)
	    {
	        if( i!=0 && i%16==0)   //if one line of hex printing is complete...
	        {
	            printf("         ");
	            for(j=i-16 ; j<i ; j++)
	            {
	                if(data[j]>=32 && data[j]<=128)
	                    printf("%c",(unsigned char)data[j]); //if its a number or alphabet
	 
	                else printf("."); //otherwise print a dot
	            }
	            printf("\n");
	        }
	 
	        if(i%16==0) printf("   ");
	            printf(" %02X",(unsigned int)data[i]);
	 
	        if( i==Size-1)  //print the last spaces
	        {
	            for(j=0;j<15-i%16;j++) printf("   "); //extra spaces
	 
	            printf("         ");
	 
	            for(j=i-i%16 ; j<=i ; j++)
	            {
	                if(data[j]>=32 && data[j]<=128) printf("%c",(unsigned char)data[j]);
	                else printf(".");
	            }
	            printf("\n");
	        }
	    }
}


int main(int argc,char *argv[])
{
	int rawsock;			
	char *device;
	unsigned char *buffer = (unsigned char*)malloc(sizeof(char)*PACKET_SIZE);;

	const int NUMBER_PACKETS = atoi(argv[2]);

	device = (char*) malloc(sizeof(argv[1])+1);
	strcpy(device,argv[1]);

	//opening device in promiscuous mode
	setpromisc(device,1);	
		
	//creating the socket 
	rawsock = createSocket();
	if(rawsock==-1)
	{
		printf("SOCKET CREATION FAILED\n");
		exit(1);		
	}

	//binding the socket to the device;	
	
	bindSocket_Device(device,rawsock,ETH_P_ALL);	//all protocols like IP,IPX or any other are caught..#define ETH_P_ALL	0x0003

	catchPackets(NUMBER_PACKETS,buffer,device,rawsock);

	//closing the promiscuous mode
	setpromisc(device,0);

	close(rawsock);
	return 0;
}

	


