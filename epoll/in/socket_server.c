#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define BUFSIZE 512
void HandleTCPClient(int client_sockfd);
int main(int argc ,char * argv[]){
	if(argc!=2){
		perror("<server port>");
		exit(1);
	}
	in_port_t servPort=atoi(argv[1]);
	int server_sockfd;
	int server_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	server_sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(servPort);
	server_len=sizeof(server_address);
	if(bind(server_sockfd,(struct sockaddr *)&server_address,server_len)<0){
		perror("bind failed");	
		exit(1);
	}
	if(listen(server_sockfd,5)<0){
		perror("listen failed");
		exit(1);
	}
	while(1){
		socklen_t client_len=sizeof(client_address);
		int client_sockfd=accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
		if(client_sockfd<0){
			perror("accept failed");
			exit(1);
		}
		char clientName[INET_ADDRSTRLEN];
		if(inet_ntop(AF_INET,&client_address.sin_addr.s_addr,clientName,sizeof(clientName))!=NULL){
			printf("handling client %s /%d \n",clientName,ntohs(client_address.sin_port));
		}else{
			puts("unable to get client address");
		}
		HandleTCPClient(client_sockfd);
	}
}
void HandleTCPClient(int client_sockfd){
	char buffer[BUFSIZE];
	ssize_t numBytesRcvd=recv(client_sockfd,buffer,BUFSIZE,0);
	if(numBytesRcvd<0){
		perror("recv() failed");
	}
	while(numBytesRcvd>0){
		ssize_t numBytesSent=send(client_sockfd,buffer,numBytesRcvd,0);
		if(numBytesSent<0){
			perror("send() failed");
		}else if(numBytesRcvd!=numBytesSent){
			perror("send(): sent unexpected number of bytes ");
		}
		numBytesRcvd=recv(client_sockfd,buffer,BUFSIZE,0);
		if(numBytesRcvd<0){
			perror("recv() failed");
		}
		close(client_sockfd);
	}
	
}

