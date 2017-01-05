/*********************************
 * Lab 2: Copying Via Sockets
 * File Name:   server.c
 * Created By:  Joseph Phan
 * Date:        10/7/16
 * Lab Section: Fri 2:15
*********************************/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#define BUFFER_SIZE 500
#define PORT_NUM 9100


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
	struct sockaddr_in serveraddr; 
	struct sockaddr_in clientaddr;
	char buffer[BUFFER_SIZE]; 

	bzero((char*)&serveraddr,sizeof(serveraddr));

	serveraddr.sin_family = AF_INET; 
	serveraddr.sin_addr.s_addr=INADDR_ANY;
	serveraddr.sin_port = htons(PORT_NUM);

	int sockfd = socket(AF_INET,SOCK_DGRAM,0);

	if(bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr))<0){ 
		printf("error on bind\n"); 
	}

	socklen_t clientlen = sizeof(clientaddr);

	while(true){

		/*receive message from client and stores it in array */
		recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*) &clientaddr, &clientlen); 
		printf("%s\n", buffer);
		if (checkQuit(buffer)){
			break;
		}			
		
	}

	return 0;
}

bool hasQuit(char buffer[]){



	return false;
}
