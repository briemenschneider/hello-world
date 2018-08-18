#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum gradient {LOW, MEDIUM, HIGH};  //practice enum

typedef char string_t[100];  //fun with arrays

//practice with struct and arrays
typedef struct employee {
  string_t fname;
  string_t mname;
  string_t lname;
  int idnum;
  enum gradient clearance;
} employee_t;
  

//Simple recursive fucntion to test for prime - not optimized
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
  int j,k;
  bool ans;
  employee_t employee1;
  string_t c;

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

  //enter the employee information
  printf("Please enter your first name: ");
  scanf("%s", employee1.fname);
  printf("Please enter your last name: ");
  scanf("%s", employee1.lname);
  employee1.idnum = j;
  printf("Please enter clearance level (LOW %d, MED %d, HIGH %d): ", LOW, MEDIUM, HIGH);
  scanf("%d", &k);
  employee1.clearance = k;

  //now print the information back
  switch (employee1.clearance) {
  case LOW:
    strcpy(c,"LOW");
    break;
  case MEDIUM:
    strcpy(c, "MEDIUM");
    break;
  case HIGH:
    strcpy(c, "HIGH");
    break;
  default:
    strcpy(c, "TERMINATE!!!!");
  }
  
  printf("Welcome %s %s.\nEmployee number %d.\nClearance %s granted.\n", employee1.fname, employee1.lname, employee1.idnum, c);

  //end program
  return EXIT_SUCCESS;
}
