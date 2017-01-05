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
#include<string.h>
#include<stdbool.h>
#include <ctype.h>
#define BUFFER_SIZE 500
#define FILE_NAME_SIZE 50
#define PORT_NUM 9009

bool checkQuit(char buffer[]){
	int len, i;
	char tmp[5];
	len =strlen(buffer);
	if(len>=4){
		strncpy(tmp,buffer, 4);
		tmp[4]='\0';

		for(i = 0; i<strlen(tmp); i++){
			tmp[i] = tolower(tmp[i]);
		}
		if(strcmp(tmp,"quit")==0)
			return true;			
	}
	return false;
}

int main(int argc, const char*argv[]){
	/*server structure  */
	int socketfd;
	char buffer[BUFFER_SIZE]; 
	const char* hostname= argv[1]; /* localhost */
	const char* portname=argv[2];
	struct addrinfo hints;
	
	//creating connection info
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

	//Creates the Client Socket
	socketfd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	if (socketfd==-1) {
    	printf("%s",strerror(errno));
		exit(1);
	}
 
	//Sending out the messages
	while (true){
	/*sends the array message to the server	*/
		gets(buffer);	
		if (sendto(socketfd,buffer,sizeof(buffer),0,
		res->ai_addr,res->ai_addrlen)==-1) {
			printf("%s",strerror(errno));
			exit(1);
		}
		if (checkQuit(buffer)){
			break;
		}
	}
	return 0;
}
