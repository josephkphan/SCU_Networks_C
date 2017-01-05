/*************************************
 * Lab 2: Copying Data Via Sockets
 * File Name: client.c       
 * Created By:   Joseph Phan
 * Date:         10/7/16
 * Lab Section:  Fri 2:15
 ************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 500
#define FILE_NAME_SIZE 50
#define PORT_NUM 9009

int main(int argc, const char*argv[]){
	/*server structure  */
	//struct hostent *server;
	int socketfd;
	const char* hostname= argv[1]; /* localhost */
	const char* portname=argv[2];
	struct addrinfo hints;
	
	memset(&hints,0,sizeof(hints));
    bzero(&hints, sizeof(struct addrinfo)); 
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_DGRAM;
	hints.ai_protocol=0;
	hints.ai_flags=AI_ADDRCONFIG;
	struct addrinfo* res=0;
	int err=getaddrinfo(hostname,portname,&hints,&res);
	if (err!=0) {
		printf("failed to resolve remote socket address (err=%d)",err);
		exit(1);
	}
	
	/*convert server name to its IP */
//	server = gethostbyname(argv[1]); 
	
	//at school type in school linux@scudc.scu.edu
	// if client and server are on the same machine use localhost  
	
	//Creates the Client Socket
	socketfd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	if (socketfd==-1) {
    	printf("%s",strerror(errno));
		exit(1);
	}


	/*declare message size */
	char buffer[BUFFER_SIZE]; 

 
	char fileName[] = "output.txt";

    /* send name of file to be written to server	*/
	if (sendto(socketfd,fileName,sizeof(fileName),0,
		res->ai_addr,res->ai_addrlen)==-1) {
    	printf("%s",strerror(errno));
		exit(1);
	}

	/*reads a file with name given by argv */
	FILE *fp = fopen(argv[3], "r"); 

	/*gets message from file, puts it in array */
	fgets(buffer, BUFFER_SIZE, fp); 

	/*sends the array message to the server	*/
		if (sendto(socketfd,buffer,sizeof(buffer),0,
		res->ai_addr,res->ai_addrlen)==-1) {
    	printf("%s",strerror(errno));
		exit(1);
	}

	/*close the file */
	fclose(fp); 

	return 0;
}

/* Sources:
http://man7.org/linux/man-pages/man3/getaddrinfo.3.html
http://www.microhowto.info/howto/send_a_udp_datagram_in_c.html
http://beej.us/guide/bgipc/output/html/multipage/unixsock.html
https://www.cs.cmu.edu/afs/cs/academic/class/15213-f99/www/class26/udpclient.c
*/
