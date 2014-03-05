#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char* argv[]){
  int n = atoi(argv[1]);
  int* d = (int*) malloc(sizeof(int)*(n+1));
  int m;
  double test;

// Compute how many terms is enough
  m = 5;
  test = (n+1)*2.30258509;

  while(m*(log(m)-1.0)+0.5*log(6.2831852*m) <= test){
    m += 1;
  }

  int i, j, carry, temp;
  int* coef = (int*) malloc(sizeof(int)*(m+1));

// Initialize the digits
  for(j=2;j<=m;j++)coef[j]=1;
  d[0] = 2;
  printf("2.");

// Compute the remaining digits one by one
  for(i=1;i<=n;i++){
    carry = 0;
     for(j=m;j>=2;j--){
       temp = coef[j] * 10 + carry;
       carry = temp / j;
       coef[j] = temp - carry * j;
     }
     d[i] = carry;
     putchar(d[i]+'0');
  }
  free(coef);free(d);
  putchar('\n');
  return 0;
}
