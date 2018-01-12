// NWEN 243, Victoria University of Wellington. Author, Kris Bubendorfer.

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#define bufsize 1024

int main(argc, argv) int argc; char *argv[];{
  int sock, rval;
  struct hostent *host;
  struct sockaddr_in server;  // not a pointer.
  char buf[bufsize];
  
  if(argc != 4){
    printf("usage:\ntcpclient hostname port string\n\n");
    return(-1);
  }
  
  // look up hostname (server) using DNS

  if ((host = gethostbyname(argv[1])) == 0) {
    fprintf(stderr, "%s: unknown host\n", argv[1]); 
    return(-1);  
  }

  // Set up fields for socket to point to host and port

  bcopy(host->h_addr, &server.sin_addr, host->h_length);
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));
for(;;)
{
  // Create socket and check if an error occured
  if( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
  	fprintf(stderr, "Failed to create socket\n");
  	return(-1);
  } else {
  	//fprintf(stderr, "Sucessfully created socket\n");
  }

  // connect (3-way handshake)
  if(connect(sock, &server, sizeof(server)) < 0) {
  	fprintf(stderr, "Failed to connect to %s:%s\n", argv[1],argv[2]);
  	return(-1); 
  } else {
  	//fprintf(stderr, "Connected to %s:%s\n",argv[1],argv[2]);
  }

  // Copy the arg into buf so we can send it to the server
  
  strncpy(buf, argv[3], bufsize);

  // Send sentence to server
    if(write(sock, buf, bufsize) < 0) {
  	fprintf(stderr, "Failed to write to socket\n");
  	return(-1);
    } 
    sleep(1);
    // read response from server
    if(read(sock, buf, bufsize) < 0) {
	  fprintf(stderr, "Failed to read from socket\n");
	  return(-1);
    }
  
    // print result to window

    fprintf(stdout,"%s\n", buf);
  //sleep(1);
  close(sock);

}

}
