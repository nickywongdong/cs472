#include <string.h>
#include <stdio.h>

int main (void)
{
 double intPart = 0, fracPart = 0, conversion;
 unsigned int i;
 char decimal[] = "3.14159";

 i = 0; /* Left to right */
 while (decimal[i] != '.') {
    intPart = intPart*10 + (decimal[i] - '0');
    i++;
   }

 i = strlen(decimal)-1; /* Right to left */
 while (decimal[i] != '.') {
    fracPart = (fracPart + (decimal[i] - '0'))/10;
    i--;
   }

 conversion = intPart + fracPart;

 printf("%d\n", conversion);
}