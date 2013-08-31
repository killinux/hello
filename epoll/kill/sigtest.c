#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
static void sig_usr(int);
int main(void){
	printf("main\n");
	if(signal(SIGUSR1,sig_usr)==SIG_ERR)
		perror("error 1");
	if(signal(SIGUSR2,sig_usr)==SIG_ERR)
		perror("error 2");
	for(;;)
		pause();
}
static void sig_usr(int signo){
	if(signo==SIGUSR1)
		printf("received SIGUSR1\n");
	else if(signo==SIGUSR2)
		printf("received SIGUSR2\n");
	else
		printf("received signal %d\n",signo);
}
