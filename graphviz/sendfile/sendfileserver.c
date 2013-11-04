#include <sys/types.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main (int argc, char **argv)
{
	struct sockaddr_un sin1;
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	ssize_t bytes, res=0;
	ssize_t rtotal = 0;
	FILE *stream;
	int in_fd;
	struct stat buf;
	off_t off = 0;

	unlink ("server_socket");
	unlink ("src_sendfile_save");
	stream = fopen ("src_sendfile_save", "w");
	if (!stream) {
		perror ("fopen");
		exit (EXIT_FAILURE);
	}
	fclose (stream);

	if ((in_fd = open ("src", O_RDONLY)) < 0) {
		printf ("Can't open 'src' file");
		exit (EXIT_FAILURE);
	}
	if (fstat (in_fd, &buf) == -1) {
		printf ("Can't stat 'src' file\n");
		exit (EXIT_FAILURE);
	}
	printf ("Get file size are %u bytes\n", buf.st_size);

	server_sockfd = socket (AF_UNIX, SOCK_STREAM, 0);
	if (server_sockfd < 0) {
		perror ("socket");
		exit (EXIT_FAILURE);
	}
	sin1.sun_family = AF_UNIX;
	strcpy (sin1.sun_path, "server_socket");

	server_len = sizeof (sin1);
	if (bind (server_sockfd, (struct sockaddr *)&sin1, server_len) < 0) {
		perror ("bind");
		exit (EXIT_FAILURE);
	}
	if (listen (server_sockfd, 5) < 0) {
		perror ("listen");
		exit (EXIT_FAILURE);
	}

	printf ("The server is waiting for client connect...\n");

	client_sockfd = accept (server_sockfd, (struct sockaddr *)&sin1, (socklen_t *)&client_len);

	if (client_sockfd == -1 ) {
		perror ("accept");
		exit (EXIT_FAILURE);
	}
	while (off < buf.st_size) {
		if ((res = sendfile (client_sockfd, in_fd, &off, buf.st_size)) < 0 ) {
			printf ("sendfile failed\n");
			exit (EXIT_FAILURE);
		} else {
			rtotal += res;
		}
	}

	printf ("server sendfile total %u bytes\n", rtotal);
	close (client_sockfd);
	unlink ("server_socket");
	return (0);
}
