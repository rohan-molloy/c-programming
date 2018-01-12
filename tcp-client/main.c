/*
Citation: API documentation from 'release 3.54 of the Linux man-pages project.
Some of the comments on the socket API contain summaries (in my own words) from man pages
This citation is for comments only.
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#define bufsize 1024

/* if it times out, we will still be cosnuming a socket 
   it will be in the SYN-ACK state. so we need to remove these stale poitners
   */
void eatZombies(int n){

  wait3(NULL,WNOHANG,NULL); // Nom Nom
}

/* Change all lower case letters in the supplied string to upper */
char *shout(char *str)
{
	int i = 0;
	if(str == NULL) return str;
	for(i = 0; i < bufsize && str[i] != '\0'; i++) {
		str[i] = toupper(str[i]);
	}
	return str;
}

int main(int argc, char *argv[])
{

  int sock, length, msgsock, status;
  struct sockaddr_in server;

  // for forking, and cleaning up zombie child state afterwards
  // You must not change this code.

  pid_t id;
  signal(SIGCHLD, &eatZombies);

  // OK, NWEN 243 code starts here.

  /**
   * We begin by first opening a socket and store its fd in sock.
   *
   * A socket is the an API abstraction of the end point in IPC,
   *
   * The System has 2^16 ports 'channels'  for TCP/UDP communication.
   * The os protocol stack reads the portno from header of incomming packets
   * But what does it do next? This is where sockets come in to play.
   *
   * Suppose I have sshd running with pid 1489. When a client connects:
   * Layer 3 IP stack reads header and passes it to the specified transport protocol stack
   *
   * The transport protocol (usually TCP or UDP) stack then reads the port number and passes it the system
   *
   * Depending on the system, it may first checks if the port is filtered (blacklisten)
   *
   * If filtered, the system will discards the packet without sending a SYN-ACK. In some
   * systems, the Layer 3 stack may inform the client of this by sending 'ICMP Destination Unreachable'
   *
   * Otherwise, the system passes it to a socket bounded to the packet's destination (address/INET_ANY and port)
   * If the socket exists, then the port is 'open', and a SYN-ACK is sent back to the client. Otherwise, the port
   * is said to be 'closed' and RST is sent to the client.
   *
   * Here we are specifying our socket is an IPv4 network socket
   */
  if( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
  	fprintf(stderr, "Failed to create socket\n");
  	exit(EXIT_FAILURE); //Terminate if fail
  }

  /* Next, create the socket addressing structure */

  /**
   * This field states the protocol the socket will communicate over
   * AF_INET means we will communicate with IPv4 addresses
   */
  server.sin_family = AF_INET;

  /**
   * This field specifies what address (or less accurately, what interface) to listen for incoming clients on
   * In short accept connections with a destination address matching this field.
   *
   * In this case, no address is set. INADDR_ANY (0.0.0.0) is the 'wildcard'
   * and tells the system to accept any incoming connections so long as the port matches.
   * If listening on 0.0.0.0 no other proccesses can listen on the port. We can also restrict
   * outside connections by assigning it INADDR_LOOPBACK
   *
   * We can assign it a dot decimal notation literal, such as a command line argument
   *
   * This parameter is important for restricting the interface of incomming clients (note it deals with addrs not ifaces)
   * For example, if we have a WAN interface, and a LAN interface (assigned ip 192.0.2.4) and we only want LAN clients
   * we would use inet_pton(AF_INET, "192.0.2.4", &(server.sin_addr));
   */
  server.sin_addr.s_addr = INADDR_ANY;

  /**
   * Assigns the port.
   * While a port number is a uint16, we cannot directly assign an int value,
   * we need to use htons() to convert it into the correct format
   */
  server.sin_port = htons(atoi(argv[1])); // this time 1st arg is port#

  /* Attempt to bind the socket to the host ip and port. Terminate if unable to bind */

  /**
   * Associates the socket with the server address by calling bind().
   *
   * socket() requests from the system an undefined Internet socket. Next comes defining it
   * We use bind() to request that the systen associates the socket with our server address structure.
   * After bind() is called, the socket is reserved, and no other processes can open sockets with the same addresss
   *
   * If bind() returns a non-positive value, then then the system refused access to that address.
   * This can occur due to premissions (port < 1024 running as non-root), another process is occupying the address, or the interface is unavailable
   */
  if(bind(sock, &server, sizeof(server)) < 0 ) {
  	fprintf(stderr, "Failed to bind socket\n");
  	exit(EXIT_FAILURE);
  }

  /**
   * Now we request the system to listen for connections matching our address and pass them to our socket.
   * If the request was successful, our port is open and will reply to incoming TCP SYN requests
   */
  if(listen(sock, 10) < 0) {
  	fprintf(stderr, "Failed to listen on port %s\n",argv[1]);
  	exit(EXIT_FAILURE);
  }

  /**
   * Now that we are listening for connecitons. We begin the server loop.
   * Client requests are handled by forked child processes to allow concurrent requests
   */
  while(1)
  {
    /* Address of client */
    struct sockaddr_in client;
    int client_size = sizeof(client);

    /* Buffer to hold client request */
    char buf[bufsize];
    bzero(buf,bufsize);

    /**
     * Now we poll the queue of requests from our socket.
     * The thread is blocking while the TCP handshake (SYN-->server | client <--SYN-AWK | AWK -->server) is negotiated
     * The client requests to opens a to open a duplux connection (SYN)
     * The server replies with SYN-AWK, acknowledging the request, and providing the parameters for the clients socket
     * The server then waits for the client to send an AWK, informing the server that the client side socket is ready to begin duplux traffic
     * If the client takes too long to send an AWK, the connection is halted and is said to have timed out.
     * Because the timeout time is usually long (to allow for the limited network speed), it's at this stage where the server is vulnerable to a DoS attack
     * This attacked is known as a SYN flood where multiple SYN requests are sent without acknowledgement overloading the server for genuine requests
     */
    msgsock = accept(sock, &client, &client_size);

    /* Create a child process to handle the client request */
    id = fork();

    /* if id>0 then loop around as we're running the parent process */
    if(id > 0) {
    	continue;
    }
    /* Error forking */
    else if(id < 0) {
    	fprintf(stderr, "Error forking\n");
    	exit(EXIT_FAILURE);
    }

    /** This is the client handling procedure for child processes */
    else if(id == 0) {
      /* Attempt to receive bytes fron client */
    	if(read(msgsock, buf, bufsize) < 0) {
    		fprintf(stderr, "Failed to read from client\n");
    	}

    	/**
       * This elif is evaluated if we got a non zero number of bytes from the client.
       * Print what we received (this is why the tautological fprintf is in the elif condition)
       * Then we call shout() to capatilsie the string and transmit it back to the client
       * The body of the elif is reached if we failed to transmit to the client.
       */
    	else if(fprintf(stderr, "client says: %s\n", buf)
    			&& write(msgsock, shout(buf), bufsize) < 0) {
    		fprintf(stderr, "Failed to write to client");
    	}
      /* Close the socket */
    	close(sock);
    	exit(0);

    }
  }
}

