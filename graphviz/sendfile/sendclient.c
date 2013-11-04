#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char *argv[])
{
	int a=clock();
	printf("this is used %d\n",a);
	struct sockaddr_un address;
	int sockfd;
	int len, result;
	int i, bytes;
	struct stat buf;
	off_t off;
	ssize_t res, total = 0;
	int wfd;
	char rwbuf[4096];
	wfd = open ("src_sendfile_save", O_WRONLY);
	if (wfd < 0) {
		perror ("open");
		exit (EXIT_FAILURE);
	}

	/*..socket,AF_UNIX....,SOCK_STREAM....*/
	if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror ("socket");
		exit (EXIT_FAILURE);
	}

	address.sun_family = AF_UNIX;
	strcpy (address.sun_path, "server_socket");
	len = sizeof (address);

	/*..........*/
	result = connect (sockfd, (struct sockaddr *)&address, len);
	if (result == -1) {
		printf ("ensure the server is up\n");
		perror ("connect");
		exit (EXIT_FAILURE);
	}

	while ((res = read (sockfd, rwbuf, 4096)) > 0) {
		total += res;
		write (wfd, rwbuf, 4096);
	}
	printf ("total %u bytes received from server snedfile\n", total);
	close (sockfd);
	close (wfd);

	int b=clock();
	printf("this is used %d\n",b);
	int c=b-a;
	printf("this is used    %d\n",c);
	return (0);
}
