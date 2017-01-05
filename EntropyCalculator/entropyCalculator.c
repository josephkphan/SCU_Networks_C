#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

// Entropy Calculator

int main(int argc, char*argv[]) {
	if (argc != 2) {
		printf("error -- check arguments");
	}

	unsigned char buffer[4000000];	//can take up to 4MB
	int freq[256] = {0};
	int i,j, fd, count;
	double prob, entropy;
	count = 0;
	entropy = prob = 0;

	printf("\nFinding Entropy of File %s\n", argv[1]);

	// Read File
	fd = open(argv[1], O_RDONLY);  
	if (fd == -1) {
		fprintf (stderr, "Error- opening file: (%s)\n", strerror(errno));
	}

	while ((i = read(fd, buffer, sizeof(buffer)))) {
		if (i == -1) {
			fprintf(stderr ,"Error - read file");
			break;
		}

		// Create a frequency array from the input file
		for (j = 0; j < i; j++) {
			freq[buffer[j]]++;
			count++;
		}
	}

	close(fd);

	// Iterates through frequency array to calculate entropy
	for (i = 0; i < 256; i++) {
		if (freq[i]) {
			// Creating probability from Frequency Array 
			prob = (double)freq[i] / (double)count;
			// Shannon Entropy Formula
			entropy += (prob * (log2(1/prob)));	
		}
	}

	printf("Entropy: %f \n\n---------------------\n", entropy);
}


// Cite : http://blogs.cisco.com/security/on_information_entropy
// ^ Reference to entropy algorithm

