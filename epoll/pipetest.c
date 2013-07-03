#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int pipe_test[2];  

int main()
{
    pid_t pid;
    char buffer[32];

    memset(buffer, 0, 32);
    if(pipe(pipe_test) < 0)
    {
        printf("Failed to create pipe!\n");
        return 0;
    }

    if(0 == (pid = fork()))
    {
        close(pipe_test[1]);
        sleep(3);
        if(read(pipe_test[0], buffer, 32) > 0)
        {
            printf("Receive data from server, %s!\n", buffer);
        }
        close(pipe_test[0]);
    }
    else
    {
        close(pipe_test[0]);
        if(-1 != write(pipe_test[1], "haoning", strlen("haoning")))
        {
            printf("Send data to client, hello!\n");
        }
        close(pipe_test[1]);
        waitpid(pid, NULL, 0);
    }

    return 1;
}

