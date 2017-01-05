#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <stdbool.h>

#define PORTNUM 9009
#define BUFFERSIZE 512
#define NAMESIZE 64
//server.c

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

typedef struct Packets {
	int seq; 						//sequence number
	char str[BUFFERSIZE]; 			//message
	int checksum; 					//checksum flag
} Packet;

//convert string to uppercase
void upper_string(char s[]) {
	int c = 0;
	while (s[c] != '\0') {
    	if (s[c] >= 'a' && s[c] <= 'z') {
        	s[c] = s[c] - 32;
        }
        c++;
    }
}

int main(int argc, const char* argv[]) {

	//create socket for server
	struct sockaddr_in si_server;
	bzero((char*)&si_server,sizeof(si_server)); 
	si_server.sin_family = AF_INET; 
	si_server.sin_addr.s_addr=INADDR_ANY;
	si_server.sin_port = htons(PORTNUM);
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);	
	if(bind(sockfd, (struct sockaddr *) &si_server, sizeof(si_server))<0){ 
		printf("bind errpr\n"); 
	}

	socklen_t tolen = sizeof(si_server); 			//size of server
	char name[NAMESIZE] = "Server"; 				//declare name size
	char clientName[NAMESIZE];						//declare other username
	char buffer[BUFFERSIZE]; 						//declare message size
	
	int sendValue,recValue,recValue2; 				//placeholder for sendto's and recvfrom's
	int checksumFlag = 17; 							//hardcoded checksum flag
	Packet *packetOther = malloc(sizeof(Packet));


	while(true) {
		/* Server receives 2 things, a name and the message
		*  Name is just for clarity (debugging purposes)
		*  Message is the packet Client sent
		*  
		*  Server will receive a packet and then send the packet back with an
		*  incremented sequence value as an acknowledgement.
		*/
		

		puts("waiting for response....");
		//receive username from client and stores it in clientName
		recValue = recvfrom(sockfd, clientName, NAMESIZE, 0, (struct sockaddr*) &si_server, &tolen); 
		
		//check if other user quit
		if(checkQuit(clientName)) { break; }
			
		recValue2 = recvfrom(sockfd, packetOther, sizeof(Packet), 0, (struct sockaddr*) &si_server, &tolen); 
		char *pos;
	
		if ((pos=strchr(clientName, '\n')) != NULL){ //remove /n from string 
		    *pos = '\0';
		}

		//if(packetOther->checksum == checksumFlag) {
			//print sequence #
			printf("Sequence Number: %i\n", packetOther->seq);
			//print checkSum Value
			printf("checksum flag: %i\n", packetOther->checksum);
			//print message length
			printf("length of string: %i\n", strlen(packetOther->str)-1);
			//print username&message
			printf("\n%s: %s", clientName, packetOther->str);
 			
			strcpy(buffer,packetOther->str);
			upper_string(buffer); 
			strcpy(packetOther->str, buffer);
			//increment sequence number
			packetOther->seq = packetOther->seq + 1; 
		
			sendValue = sendto(sockfd, name, NAMESIZE, 0, (struct sockaddr*) &si_server, tolen);
			sendValue = sendto(sockfd, packetOther, sizeof(Packet), 0, (struct sockaddr*) &si_server, tolen); //send message
			if(sendValue != -1) printf("Message sent. \n");
		//}
		//else {
		//	printf("Checksum failed\n");
		//}
		
	}
	close(sockfd);
	return 0;
}



