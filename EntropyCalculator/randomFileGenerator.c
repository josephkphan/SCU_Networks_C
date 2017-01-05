#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, const char* argv[]) {
	
	int num_bytes = strtol(argv[1], NULL, 10); 		
	//input # of bytes -- strol -- change string to long
	char stream[num_bytes]; 						
	// array will store the random message
	int i;

	// loop to create random characters into array
	for(i = 0; i < num_bytes; i++) { 
		stream[i] = rand() % 256;
		// random character from ASCII Table
	}

	//open file from input
	FILE *fp = fopen(argv[2],"w"); 
	
	// write array into file
	for( i = 0; i < num_bytes; i++) { 
		fputc(stream[i],fp);
	}
	fclose(fp);

	return 0;

}



