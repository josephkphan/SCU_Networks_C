/*********************************
 * Lab 2: Copying Via Sockets
 * File Name:   server.c
 * Created By:  Joseph Phan
 * Date:        10/7/16
 * Lab Section: Fri 2:15
*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#define FILE_NAME_SIZE 50
#define BUFFER_SIZE 500
#define PORT_NUM 9100


/*  PROGRAMMING WITH UDP/IP SOCKETS
 *	1. Create the socket
 *  2. Identify the socket (name it)
 *  3. On the Server, wait for a message
 *  4. On the Client, send a message
 *  5. Send a response back to the client (optional)
 *  6. Close the Socket
 */

int main(int argc, const char*argv[]){
	/* constructs the server addr */
	struct sockaddr_in serveraddr; 
	/* client addr  */
	struct sockaddr_in clientaddr;
	
	/*clear any pre-existing information at a location with the size of server*/
	bzero((char*)&serveraddr,sizeof(serveraddr));

 	/*an address family that is used to designate the type of addresses that your 
	socket can communicate with (ipv4)*/
	serveraddr.sin_family = AF_INET; 
	serveraddr.sin_addr.s_addr=INADDR_ANY;

	 /*Specifies the port. htons - host to network short
	   short - depends on your port number big length- 
	   Little Indian - least significant bits
	   Big Indian    - most significant bits  */
	serveraddr.sin_port = htons(PORT_NUM);

	/*Create a socket, INET is for internet, sockDGram is for UDP , connectionless
	  otherwise you would write SOCK_STREAM for TCP  */
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);

	/* Binds the server to the port and make sure it is constantly listening 
	*  basically saying "Im using this port' - established a connection with	
	   that port */
	if(bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr))<0){ 

		/*Returns a value of 0 or greater of it fails*/
		printf("error on bind\n"); 
	}

	 /*Finds out what port was really assigned to the server*/
	socklen_t clientlen = sizeof(clientaddr);

	/* Declare name size */
	char name[FILE_NAME_SIZE]; 

	/*declare Message/Buffer size */
	char buffer[BUFFER_SIZE]; 

	int n;
	/*receive message from client and stores it in name */
	n=recvfrom(sockfd, name, FILE_NAME_SIZE, 0, (struct sockaddr*) &clientaddr, &clientlen); 
	if(n < 0)
		printf("ERROR\n");
	printf("File name received: %s \n", name);
	

	/*receive message from client and stores it in array */
	recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*) &clientaddr, &clientlen); 

	/* opens a file with name given by client */
	FILE *fp = fopen(name,"w");

	/* writes to giben message to client */
	fputs(buffer,fp); 

	/* Close File */
	fclose(fp); 

	
/* Sources:
 	https://www.cs.rutgers.edu/~pxk/417/notes/sockets/udp.html
	https://www.cs.cmu.edu/afs/cs/academic/class/15213-f99/www/class26/udpserver.c
*/

	return 0;
}
