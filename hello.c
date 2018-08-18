#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPrime(int n) {
  int i;

  for (i = 2; i < n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

int main (void) {
  int j;
  bool ans;

  //standard greeting plus question
  printf("hello world.\n");
  printf("Enter your suggested prime: ");
  scanf("%d", &j);  //take a number, any number
  
  //now check against invalid numbers
  if (j <= 1) {
    printf("You've entered a value less than 2, and is therefor invalid.\n");
    return EXIT_SUCCESS;
  }
  else {
    ans = isPrime(j);
    if (ans) {
      printf("Your integer %d is Prime.\n", j);
    }
    else printf("Your integer %d is not Prime.\n", j);
  }
  
  return EXIT_SUCCESS;
}
