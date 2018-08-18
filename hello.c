#include <stdio.h>
#include <stdlib.h>

boolean isPrime(int n) {
  int i;
  for (i = 2; i < n; i++) {
    if (n mod i == 0) {
      return false;
    }
    else i++;
  }
  return true;
}

int main (void) {
  int j;
  boolean ans;
  
  printf("hello world.\n");
  printf("Enter your suggested prime: ");
  scanf("%d", &j);
  ans = isPrime(j);
  if (ans) {
    printf("Your integer %d is Prime.\n", j);
  }
  else printf("Your integer %d is not Prime.\n", j);
  
  return EXIT_SUCCESS;
}
