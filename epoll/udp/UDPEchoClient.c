#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include "Practical.h"

int main(int argc, char *argv[]) {

  if (argc < 3 || argc > 4) // Test for correct number of arguments
    DieWithUserMessage("Parameter(s)",
        "<Server Address/Name> <Echo Word> [<Server Port/Service>]");

  char *server = argv[1];     // First arg: server address/name
  char *echoString = argv[2]; // Second arg: word to echo

  size_t echoStringLen = strlen(echoString);
  if (echoStringLen > MAXSTRINGLENGTH) // Check input length
    DieWithUserMessage(echoString, "string too long");

  char *servPort = (argc == 4) ? argv[3] : "echo";// Third arg (optional): server port/service

  struct addrinfo addrCriteria;                   // Criteria for address match // Tell the system what kind(s) of address info we want
  memset(&addrCriteria, 0, sizeof(addrCriteria)); // Zero out structure
  addrCriteria.ai_family = AF_UNSPEC;             // Any address family
  
  addrCriteria.ai_socktype = SOCK_DGRAM;          // Only datagram sockets// For the following fields, a zero value means "don't care"
  addrCriteria.ai_protocol = IPPROTO_UDP;         // Only UDP protocol

 
  struct addrinfo *servAddr; // List of server addresses // Get address(es)
  int rtnVal = getaddrinfo(server, servPort, &addrCriteria, &servAddr);
  if (rtnVal != 0)
    DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));

  int sock = socket(servAddr->ai_family, servAddr->ai_socktype,servAddr->ai_protocol); // Socket descriptor for client// Create a datagram/UDP socket
  if (sock < 0)
    DieWithSystemMessage("socket() failed");

  
  ssize_t numBytes = sendto(sock, echoString, echoStringLen, 0,servAddr->ai_addr, servAddr->ai_addrlen);// Send the string to the server
  if (numBytes < 0)
    DieWithSystemMessage("sendto() failed");
  else if (numBytes != echoStringLen)
    DieWithUserMessage("sendto() error", "sent unexpected number of bytes");

  struct sockaddr_storage fromAddr; // Source address of server // Receive a response
  socklen_t fromAddrLen = sizeof(fromAddr);// Set length of from address structure (in-out parameter)
  char buffer[MAXSTRINGLENGTH + 1]; // I/O buffer
  numBytes = recvfrom(sock, buffer, MAXSTRINGLENGTH, 0,
      (struct sockaddr *) &fromAddr, &fromAddrLen);
  if (numBytes < 0)
    DieWithSystemMessage("recvfrom() failed");
  else if (numBytes != echoStringLen)
    DieWithUserMessage("recvfrom() error", "received unexpected number of bytes");

  if (!SockAddrsEqual(servAddr->ai_addr, (struct sockaddr *) &fromAddr))
    DieWithUserMessage("recvfrom()", "received a packet from unknown source");// Verify reception from expected source

  freeaddrinfo(servAddr);

  buffer[echoStringLen] = '\0';     // Null-terminate received data
  printf("Received: %s\n", buffer); // Print the echoed string

  close(sock);
  exit(0);
}
