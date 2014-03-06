#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>

int main(int argc, char* argv[]){
  int n,m,i,j;
  int test;
  uint64_t carry;
  uint32_t* efrac;

  if(argc<2)fprintf(stderr,"Not enough argument!\n"),exit(-1);
// Number of decimal digits we want to get
  n = atoi(argv[1]);
  printf("%d decimal digits\n",n);
// Compute how many terms is enough
  m = 5;
  test = (n+1)*2.30258509;
  while(m*(log(m)-1.0)+0.5*log(6.2831852*m) <= test){m++;}
  m = n;
// Number of binary bits we want to get
  n *= log(10)/log(2);
  n++; // Always round up to get guard bit
  printf("%d binary bits\n",n);
  n /= sizeof(uint32_t)*8;
  n++; // Always round up to get guard byte
  printf("%d integer(%lu)\n",n,sizeof(uint32_t));
// Prepare memory for the result
  efrac = (uint32_t*) malloc(sizeof(uint32_t)*(n+1));
  for(i=m;i>=2;i--){
    // Division loop
    carry = 1;
    for(j=0;j<=n;j++){
      carry <<= sizeof(uint32_t)*8;
      carry += efrac[j];
      efrac[j] = carry/i;
      carry -= efrac[j]*i;
    }
  }
// Output in hexadecimal
// Hex -> Decimal conversion could be done with dc
  printf("2.");
  for(i=0;i<n;i++){
    printf("%04X",efrac[i]);
  }
  putchar('\n');
  free(efrac);
  return 0;
}
