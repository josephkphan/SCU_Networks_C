#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Diffie-Hellman Key Exchange Algorithm

int main() {
	
	// Variables
	unsigned int primeNum, root, private_key1, private_key2;
	unsigned long long public_key1, public_key2;
	unsigned long long calc1, calc2;
	
	// Prompt User for a Prime Number and store input in p
	// Doesnt not error check for prime 
	printf("Please enter a prime number: \n");
	scanf("%d", &primeNum);

	// Prompt user for a primitive root of p and store the input in r
	// Error checking for primitive root is not available.
	printf("Please enter a primitive root of the prime number: \n");
	scanf("%d", &root);	

	// Prompt user for first private key and store the input in a
	printf ("Please enter first private key: \n");
	scanf("%d", &private_key1);
		
	// Prompt user for second private key and store the input in b
	printf ("Please enter second Private Key: \n");
	scanf("%d", &private_key2);


	// Calculate public keys
	public_key1 = (unsigned long long)pow(root, private_key1) % primeNum;		 
	public_key2 = (unsigned long long)pow(root, private_key2) % primeNum;

	printf ("Public Key1: %d \n", public_key1);
	printf ("Public Key2: %d \n\n", public_key2);	

	
	// Calculate shared private keys 
	calc1 = (unsigned long long)pow(public_key2, private_key1) % primeNum;
	calc2 = (unsigned long long)pow(public_key1, private_key2) % primeNum;	


	// Are both values of k equal?
	printf ("Calculated Value1: %d \n", calc1);
	printf ("Calculated Value2: %d \n\n", calc2);

	return 0;
}




