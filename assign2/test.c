#include <stdio.h>
#include <stdint.h>


//extended from the idea https://stackoverflow.com/questions/15685181/how-to-get-the-sign-mantissa-and-exponent-of-a-floating-point-number
typedef union {
  double d;
  struct {
    uint64_t mantissa : 52;
    uint64_t exponent : 11;
    uint64_t sign : 1;
  } parts;
} double_cast;

int main(void) {
  double_cast d1 = { .d = 0.55 };
  double_cast d2 = { .d = 0.45 };

  printf("sign = %x\n", d1.parts.sign);
  printf("exponent = %x\n", d1.parts.exponent);
  printf("mantisa = %x\n", d1.parts.mantissa);

  printf("sign = %x\n", d2.parts.sign);
  printf("exponent = %x\n", d2.parts.exponent);
  printf("mantisa = %x\n", d2.parts.mantissa);

  printf("multiply: %x\n", d2.parts.mantissa * d1.parts.mantissa);
}