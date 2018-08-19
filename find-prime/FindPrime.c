#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


//Simple recursive function to test for prime by testing against factors 
bool isPrime(int n, int primestore[], int index) {
  int i;

  for (i = 0; i < index; i++) {
    if (n % primestore[i] == 0) {
      return false;
    }
  }
  return true;
}

//recursive function to find primes between two values and returns the number of Primes found
void findPrimes(int min, int max, int primestore[], int *index) {
  int i = 0;

  if (min > max) {
    printf ("Error: Unexpected min greater than max.\n");
    return;
  }
  else if (max < 2) {
    printf("Error: unexpected max < 2.\n");
    return;
  }
  else if (max == 2) { //lowest prime
    printf("Error at max is 2.\n");
    return;
  }
  else if (max > min) { //split the array in half, doing the lower half first
    i = min + (max-min)/2;
    findPrimes(min, i, primestore, index);
    findPrimes(i+1, max, primestore, index);
  }
  else if (max == min) {
      if (primestore[i] <= 1) {
	printf ("Possible error: reached end of prime store before expected or had bad value.");
	return;
	}
      else if (isPrime(max, primestore, *index)) {
	primestore[*index] = max;
	*index = *index + 1;
      }
  }
  else {
    printf("Error: Something strange happened. Max and min have no relativistic value.\n");
  }
  return;
}
	
	
      
    
    
//tongue in cheek - this methos is much slower than a linear check, but it was fun
bool fastPrime(int n) {
  int knownprimes[256000] = {2, 0};
  int index = 1;
  int i;
  int j;
  char c;

  //do the quick checks
  if (n <= 1) {
    return false;
  }
  else if (n == 2) {
    return true;
  }
  else if (n % 2 == 0) { //get the even numbers out of the way
    return false;
  }

  j = (n / 2) + (n % 2); //carve the field in half
  findPrimes(3, j, knownprimes, &index);
  printf("Found %d Primes to halfway point.\n", index);
  printf("Do you want to see this list of Primes? (y/n): ");
  scanf(" %c", &c);
  if (c == 'y') {
    for (i = 0; i < index; i++) {
      printf("%d | ", knownprimes[i]);
    }
    printf("\n");
  }
  else if (c == 'n') {
    printf("Your loss.\n");
  }
  else {
    printf("You're fucking crazy!\n");
  }

  
  if (isPrime(n, knownprimes, index)) {
    return true;
  }
  else return false;
}
    

int main (void) {
  int j;
  bool ans;


  //Ask for the integer that we will check for prime
  printf("Enter your suggested prime between 0-%d: ", INT_MAX);
  scanf("%d", &j);  //take a number
  
  //now check against invalid numbers
  if (j <= 1) {
    printf("You've entered a value less than 2, and is therefor invalid.\n");
    return EXIT_SUCCESS;
  }
  else if (j >= INT_MAX) {
    printf("You've entered a value that is too large.\n");
    return EXIT_SUCCESS;
  }
  else {
    ans = fastPrime(j);
    if (ans) {
      printf("Your integer %d is Prime.\n", j);
    }
    else printf("Your integer %d is not Prime.\n", j);
  }


  //end program
  return EXIT_SUCCESS;
}
