#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/un.h>
int main(){
        int sockfd;
        struct sockaddr_un address;
        int len;
        int result;
        char ch='C';
        sockfd=socket(AF_UNIX,SOCK_STREAM,0);
        address.sun_family=AF_UNIX;
        strcpy(address.sun_path,"server_socket");
        len=sizeof(address);
        result=connect(sockfd,(struct sockaddr *) &address,len);
        if(result==-1){
                perror("oops:client1");
                exit(1);
        }
        write(sockfd,&ch,1);
        read(sockfd,&ch,1);
        printf("char from sever=%c\n",ch);
        close(sockfd);
        exit(0);

}
