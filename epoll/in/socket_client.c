#include <stdio.h> 
#include <stdlib.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
int main(int argc,char * argv[]){
	if(argc<3||argc>4){
		perror("<Server address< <echo word> [server port]");
		exit(1);
	}
	int sockfd;
	struct sockaddr_in address;
	int len;
	int result;
	char *servIP=argv[1];
	char *echoString=argv[2];
	in_port_t servPort=(argc==4)?atoi(argv[3]):7;
	sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	memset(&address,0,sizeof(address));
	address.sin_family=AF_INET;
	int rtnVal=inet_pton(AF_INET,servIP,&address.sin_addr.s_addr);//http://learn.akae.cn/media/ch37s01.html#id2902826
 	if(rtnVal==-1){
        perror("oops:client0");
        exit(1);
    }
	address.sin_port=htons(servPort);
	len=sizeof(address);
	result=connect(sockfd,(struct sockaddr *) &address,len);
	if(result==-1){
		perror("oops:client1");
		exit(1);
	}
	size_t echoStringLen=strlen(echoString);
	ssize_t numBytes=send(sockfd,echoString,echoStringLen,0);
	if(numBytes<0){
		perror("send() failed");
        exit(1);
	}else if(numBytes!=echoStringLen){
		printf("this is a  %d",numBytes);
		perror("send() connection closed prematurely !!!!!\n");
        exit(1);
	}
	fputs("Received:",stdout);	
	unsigned int totalBytesRcv=0;
	int BUFSIZE=512;
	while(totalBytesRcv<echoStringLen){
		char buffer[BUFSIZE];
		numBytes=recv(sockfd,buffer,BUFSIZE-1,0);
		if(numBytes<0){
			perror("recv() failed");
       		 exit(1);
		}else if(numBytes==0){
			perror("recv() connection closed prematurely");
        	exit(1);
		}
		totalBytesRcv+=numBytes;
		buffer[numBytes]='\0';
		fputs(buffer,stdout);	
	}
	fputc('\n',stdout);
	close(sockfd);
	exit(0);

}

