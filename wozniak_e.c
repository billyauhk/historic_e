#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>

int main(int argc, char* argv[]){
  int s,n,m,i,j;
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
// Number of binary bits we want to get
  s = n*log(10)/log(2);
  s++; // Always round up to get guard bit
  printf("%d binary bits\n",s);
  s /= sizeof(uint32_t)*8;
  s++; // Always round up to get guard byte
  printf("%d integer(%lu)\n",s,sizeof(uint32_t));
// Prepare memory for the result
  efrac = (uint32_t*) malloc(sizeof(uint32_t)*(s+1));
  for(i=m;i>=2;i--){
    // Division loop
    carry = 1;
    for(j=0;j<=s;j++){
      carry <<= sizeof(uint32_t)*8;
      carry += efrac[j];
      efrac[j] = carry/i;
      carry -= efrac[j]*i;
    }
  }
// Output in hexadecimal
// Hex -> Decimal conversion could be done with dc

/*  printf("2.");
  for(i=0;i<s;i++){
    printf("%04X",efrac[i]);
  }
  putchar('\n');*/

// Output in decimal
// A rather slow approach, but not correct!?
  printf("2.");
  for(i=0;i<n;i++){
    carry = 0;
    for(j=s;j>=0;j--){
      carry += (uint64_t) efrac[j]*10;
      efrac[j] = (uint32_t) carry&0xFFFFFFFF;
      carry >>= 32;
    }
    putchar(carry+'0');
  }
  putchar('\n');
  free(efrac);
  return 0;
}
