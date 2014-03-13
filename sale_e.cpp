#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>

#define dpl  6   // Digit per loop
#define base 1000000  // 10^dpl

int main(int argc, char* argv[]){
  int n = atoi(argv[1]);
  uint32_t* d = (uint32_t*) malloc(sizeof(uint32_t)*(n/dpl+2));
  int m;
  double test;

// Compute how many terms is enough
  m = 5;
  test = (n+1)*2.30258509;

  while(m*(log(m)-1.0)+0.5*log(6.2831852*m) <= test){
    m += 1;
  }

  int i, j, k;
  uint64_t carry, temp;
  uint32_t* coef = (uint32_t*) malloc(sizeof(uint32_t)*(m+1));

// Initialize the digits
  for(j=2;j<=m;j++)coef[j]=1;
  d[0] = 2;
  printf("2.");

// We can extract at most 9 digits each time as 10^9 < 2^32
// But in real computation we only could do 6...why?
// Have to reason why it might overflow
  for(i=1;i<=n/dpl+1;i++){
    carry = 0;
    for(j=m;j>=2;j--){
      temp = coef[j] * base + carry;
      carry = temp / j;
      coef[j] = temp - carry * j;
    }
    d[i] = carry;
    if(i!=n/dpl+1){
      printf("%0.*d",dpl,d[i]);
    }else{
      for(k=0;k<dpl-(n%dpl);k++){d[i]/=10;}
      printf("%0.*d",n%dpl,d[i]);
    }
  }
  free(coef);free(d);
  putchar('\n');
  return 0;
}
