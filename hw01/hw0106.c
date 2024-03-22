// #include <stdio.h>
// #include <stdint.h>
// typedef unsigned _BitInt(256) u256;
// typedef /*signed*/ _BitInt(256) i256;

// // works with clang 16
// // but not GCC yet (as of April 2023)

// int lt0(i256 a){
//     return a < 0;  // just the sign bit in the top limb
// }

// // -march=broadwell allows mulx which clang uses, and adox/adcx which it doesn't
// u256 mul256(u256 a, u256 b){
//     return a*b;
// }
// int main(){


//     return 0;
// }

#include <stdio.h>
int main(int argc, char **argv) {
  _ExtInt(4096) x = 5;
  printf("VALUE %d\n", (int)x);
  printf("SIZE  %u\n", (unsigned)sizeof(x));
  return 0;
}