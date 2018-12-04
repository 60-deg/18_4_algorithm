#include <stdio.h>
int gcd(int a, int b){
  if (a==0){
    return b;
  }else if (b==0){
    return a;
  }else{
    return a>=b ? gcd(b, a%b) : gcd(a, b%a);
  }
}
int main(void){
  printf("gcd(3465, 1323) = %d\n", gcd(3465, 1323));
  return 0;    
}
