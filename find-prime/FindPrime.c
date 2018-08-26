#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define DEFAULT_PATH "./primestore.txt"

enum options {
  SOLVEPRIME,
  FINDPRIME,
  BRUTEPRIME,
  QUITPRIME
};

//function declarations because they call each other
void findPrimes (int number, int **primestore, size_t *sz);
bool solvePrime (int number, int **primestore, size_t *sz);


 
/* argCheckerFP takes the command line arguements, and a file pointer and checks against the expected format of the command line inputs.
 It will then open a file of the name provided, if the file doesn't exist it will create one of that name.  If no name is provided, it will open a file with the default name. */
bool argCheckerFP(int argc, char**argv, FILE **f) {
  const char *defaultpath = DEFAULT_PATH;
  
  switch(argc) {
  case 0:
    fprintf(stderr, "Error: did not expect 0 arguments.\n");
    return false;
  case 1:
    printf("Opening Default Prime Number Store: %s\nIf this file does not exist, it will be created.\n", defaultpath);
    *f = fopen(defaultpath, "a+");
    return true;
  case 2:
    printf("Opening Prime Number Store: %s\nIf this file does not exist, it will be created.\n", argv[1]);
    *f = fopen(argv[1], "a+");
    return true;
  default:
    fprintf(stderr, "Error: Too many arguements entered.\nProper syntax is ./FindPrime <filename>\n");
    return false;
  }
}

//getUserInputFP takes an integer pointer that will be the numbered input and returns the option
int getUserInputFP(int *useri) {
  int n;
  int i = 0;
  bool valid = false;

  //Ask the options 0 find if a number is prime, 1 find all primes up to a number, 2 verify (brute force) a prime, 3 quit
  do {
    printf("What would you like to do?\n");
    printf("Enter 0 if you'd like to check if a number is a prime.\n");
    printf("Enter 1 if you'd like to find all primes up to and including a number of your choice.\n");
    printf("Enter 2 if you'd like to verify a prime using the brute force technique.\n");
    printf("Enter 3 to quit the program.\n");
    printf("Input: ");
    if (scanf(" %d", &n) != 1) {
      printf("Please enter a valid input.\n");
      valid = false;
      continue; //restart loop, input is not a number
    }
    
    PROMPT2: switch (n) { //switch to output the appropriate prompt, or exit on a quit selection
    case SOLVEPRIME:
      printf("Enter your suggested prime between 2-%d: ", INT_MAX);
      break;
    case FINDPRIME:
      printf("Enter a value between 2-%d to find primes less than or equal to: ", INT_MAX);
      break;
    case BRUTEPRIME:
      printf("Enter the prime you would like to test between 2-%d: ", INT_MAX);
      break;
    case QUITPRIME:
      printf("Quitting...\n");
      return QUITPRIME;
    default:
      valid = false;
      printf("Please enter a valid input.\n");
      continue;  //restart loop, input is out of bounds
    }

    if (scanf(" %d", &i) != 1) {
      printf("You have entered an invalid input.\n");
      valid = false;
      goto PROMPT2;
    }
    //now check against invalid numbers
    else if (i <= 1 || i >= INT_MAX) {
      printf("You have entered a value less than 2 or that is too large and is therefor invalid.\n");
      valid = false;
      goto PROMPT2;
    }
    else { //assign the values
      *useri = i;
      valid = true;
    }
  } while (!valid);

  return n;  
}

/*
The brutePrime function returns whether a number is Prime by using the modulus operator.
Check against 2 and checks against all odd numbers up to the number. 
Assumes valid input > 1.
*/
bool brutePrime (int number) {
  int i;

  //first check if even
  if (number % 2 == 0) {
    return false;
  }
  else {
    for (i = 3; i < number; i += 2) {
      if (number % i == 0) {
	return false;
      }
    }
  }
  return true;
}

/*
The findPrimes function finds all primes up to and including number.
It saves what it finds in the primestore and updates the size (sz) of the primestore appropriately.
If the primestore already has the answer, it does nothing. 
Assumes valid input > 1. 
*/
void findPrimes (int number, int **primestore, size_t *sz) {
  int candidate;
  
  if (*sz <= 1 && *primestore[0] != 2) { //then we have to build the primestore
    *primestore = realloc(*primestore, 2*(sizeof(number)));
    (*primestore)[0] = 2;
    (*primestore)[1] = 3; //initialize
    *sz = 2;
  }
  else if (number == 2 && *sz > 0) {
    return;
  }
  else if (number == 2 && *sz == 1) {
    (*primestore)[*sz-1] = 2;
    return;
  }
  else {
    //Now load the primes up to number into the primestore
    candidate = (*primestore)[*sz-1];
    candidate++;
    while (candidate <= number) {
      if (solvePrime(candidate, primestore, sz)) {
	*sz = *sz + 1;
	*primestore = realloc(*primestore, *sz*sizeof(candidate));
	(*primestore)[*sz-1] = candidate;
	candidate++;
      }
      else {
	candidate++;
      }
    }
  }
  return;
}
  
/* 
The solvePrime function checks the number against the values in the primestore up to the halfway point.  
If the primestore isn't big enough to hold all those values, it updates the primestore. 
Assumes valid input > 1. 
*/
bool solvePrime (int number, int **primestore, size_t *sz) {
  size_t i;

  if (*sz == 0) { //then we have to build the primestore
    findPrimes((number/2)+1, primestore, sz);
    return solvePrime(number, primestore, sz);
  }
  //Now we check to see if the prime store has primes up until the halfway point of number and test against them
  else if ((number/2) > (*primestore)[*sz-1]) {//Can't do this check if *sz is 0, so we keep the redundant code
    findPrimes((number/2)+1, primestore, sz);
    return solvePrime(number, primestore, sz);
  }
  else {
    for (i = 0; i < *sz; i++) { //the primestore has all numbers we need, so only check against it
      if (number % (*primestore)[i] == 0) {
	return false;
      }
    }
    return true;
  }
}
    

/*
Loads the primestore from the file it is passed and returns the size of primestore.
Prints an error if the file pointer is NULL but returns 0.
*/
size_t loadPrimesFromFile (FILE *f, int **primestore) {
  size_t sz = 0;
  
  if (f == NULL) {
    fprintf(stderr, "Error: file pointer is null on load from file.\n");
    return 0;
  }
  else {
    rewind(f); //Move to the beginning of the file and read the first size_t, which is the size of the primestore
    fread(&sz, sizeof(sz), 1, f);
    *primestore = malloc(sz); //add the size of the primestore to the heap to load up
    fread(*primestore, sizeof(**primestore), sz, f);
  }
  if (feof(f)) {
    return sz;
  }
  else {
    fprintf(stderr, "Error: when we read from the file, we didn't hit the end of file.\n");
    return sz;
  }
}

/*
Updates the file it is passed with the primestore.  Checks against the existing length of the file vs primestore.
Updates as appropriate.
*/
int updatePrimesFile(FILE *f, int *primestore, size_t sz) {
  size_t value = 0;
  
  rewind(f);
  value = fwrite(&sz, sizeof(sz), 1, f); //write the size of the prime store first
  value = fwrite(primestore, sizeof(*primestore), sz, f); //should write all values from the primestore to the file
  return value;
}

/*
Prints the primestore to the output or to a file.
*/
void printPrimes (int *primestore, size_t sz) {
  char c;
  const char *outfilename = "./primesoutput.txt";
  FILE *f;
  size_t i;

  printf("Do you want to print the primes to an output file (no will print to screen)? (y/n) ");
  scanf(" %c", &c);

  if (c == 'y') {
    f = fopen(outfilename, "w");
    for (i = 0; i < sz; i++) {
      fprintf(f, "%d | ", primestore[i]);
    }
    fclose(f);
  }
  else {
    for (i = 0; i < sz; i++) {
      printf("%d | ", primestore[i]);
    }
  }
}
 
int main (int argc, char **argv) {
  int number;
  enum options opt;
  size_t sz = 0;
  FILE *f = NULL;
  int *primestore;

  //Standard arguement conditions check
  if (!argCheckerFP(argc, argv, &f)) {
    return EXIT_FAILURE;
  }

  //Standard Error Check on File Opening
  if (f == NULL) {
    fprintf(stderr, "Error: file failed to open.\n");
    return EXIT_FAILURE;
  }

  //Load the primes from the supplied file to the primestore
  sz = loadPrimesFromFile(f, &primestore);
  
  //Ask for the user inputs
  do {
    opt = getUserInputFP(&number);

    switch (opt) {
    case SOLVEPRIME:
      if (solvePrime(number, &primestore, &sz)) {
	printf("Your number %d, is prime.\n", number);
      }
      else {
	printf("Your number %d, is not prime.\n", number);
      }
      break;
    case FINDPRIME:
      findPrimes(number, &primestore, &sz);
      printPrimes(primestore, sz);
      break;
    case BRUTEPRIME:
      if (brutePrime(number)) { //Brute force calculation does not update the prime store
	printf("Your number %d, is prime.\n", number);
      }
      else {
	printf("Your number %d, is not prime.\n", number);
      }
      break;
    case QUITPRIME:
      if (updatePrimesFile(f, primestore, sz) == 0) {
	fprintf(stderr, "Error: Failed to update the file.\n");
      }
      break;
    default:
      fprintf(stderr, "Error: Something went wrong with the options.\n");
      break;
    }
  } while (opt != QUITPRIME);

  //clean up the primestore
  free(primestore);
  
  //cleanup the file
  if (fclose(f) != EOF) {
    //end program
    return EXIT_SUCCESS;
  }
  else {
    fprintf(stderr, "Error on exit: file failed to close properly.\n");
    return EXIT_FAILURE;
  } 
  
}
