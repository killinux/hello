/*a simple of pipe
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int pipetest[2];
int main()
{
	int pid;
	char buffer[32];
	memset(buffer,0,32);
	if(pipe(pipetest)<0){
		printf("error");
	}
	if(0==(pid=fork())){
		close(pipetest[1]);
		sleep(3);
		if(read(pipetest[0],buffer,32)>0){
			printf("read,%s!\n",buffer);
		}
		close(pipetest[0]);
	}else{
		close(pipetest[0]);
		//if(-1!=write(pipetest[1],"haohao",strlen("haohao"))){
		if(write(pipetest[1],"haohao",strlen("haohao"))!=-1){
			printf("will write haohao\n");
		}
		close(pipetest[1]);
		waitpid(pid,NULL,0); 
	} 
	return 1;
	
}
