#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
void mytest();

int main(){
	struct sigaction handler;
	handler.sa_handler=mytest;
	if(sigfillset(&handler.sa_mask)<0)
		perror("error");
	handler.sa_flags=0;
	if(sigaction(SIGINT,&handler,0)<0)
		perror("error");
	for(;;)
		pause();
	exit(0);
}
void mytest(){
	puts("hello haoning");
	exit(1);
}
