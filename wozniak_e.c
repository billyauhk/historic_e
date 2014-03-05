#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char* argv[]){
  int n,m,i,j;
  long carry;
  unsigned char* efrac;

  if(argc<2)fprintf(stderr,"Not enough argument!\n"),exit(-1);
// Number of decimal digits we want to get
  n = atoi(argv[1]);
  printf("%d decimal digits\n",n);
// Compute the last term we need, should use Stirling approximation later */
  m = n;
// Number of binary bits we want to get
  n *= log(10)/log(2);
  n++; // Always round up to get guard bit
  printf("%d binary bits\n",n);
  n /= 8;
  n++; // Always round up to get guard byte
  printf("%d integer(%lu)\n",n,sizeof(unsigned char));
// Prepare memory for the result
  efrac = (unsigned char*) malloc(sizeof(unsigned char)*(n+1));
  for(i=m;i>=2;i--){
    // Division loop
    carry = 1;
    for(j=0;j<=n;j++){
      carry <<= 8;
      carry += efrac[j];
      efrac[j] = carry/i;
      carry -= efrac[j]*i;
    }
  }
// Output in hexadecimal
// Hex -> Decimal conversion could be done with dc
  printf("2.");
  for(i=0;i<n;i++){
    printf("%02X",efrac[i]);
  }
  putchar('\n');
  free(efrac);
  return 0;
}
