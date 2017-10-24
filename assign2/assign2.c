#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>


#define F64_EXP_MAX	2048 //2^11

#define F64_EXP_MASK 0x7FF0000000000000	//exponent masked
#define F64_EXP_SHIFT	52		//shift 52 times to the right
#define F64_GET_EXP(fp)

#define F64_MANT_MASK	8388608	//2^23
#define F64_MANT_SHIFT	
#define F64_GET_MANT_HIGH(fp)
#define F64_GET_MANT_LOW(fp)

#define F64_EXP_BIAS	1023
#define F64_SET_EXP


double my_frexp(double, int *);

int main(){
	int exp, i;
	double n;
	char *expression;
	printf("Enter a double: ");
	scanf("%lf", &n);

	n = my_frexp(n, &exp);

	printf("output: %.64f\n", n);
	printf("exponent: %d\n", exp);

	return 0;
}

void sum(double x, double y){

}

void sub(double x, double y){

}

void mult(double x, double y){

}

void myDiv(double x, double y){

}

void mySqrt(double x){

}


void integralToBin(char *bin, int n){
	//unsigned long bin = 0;
	int j=0, i, flag = 0;
	for(int i = 31; i>=0; i--){
		int carry = n >> i;
		if(carry & 1){
			flag = 1;
			bin[j] = '1';
			j++;
		}
		else{
			if(flag == 1){
				bin[j] = '0';
				j++;
			}
		}
	}
}

//idea for this function from :http://www.geeksforgeeks.org/convert-decimal-fraction-binary-number/
void fractionToBin(char *bin, double n){
	int i, j=63;
	for(int i=0; i<64; i++){
		n *= 2;
		int fract_bit = n;
		if(n==0){
			break;
		}
		else if (fract_bit == 1){
			n -= fract_bit;
			bin[i] = '1';
		}
		else{
			bin[i] = '0';
		}
	}
}

double my_frexp(double n, int *exp){
	int i;
	double result;
	char *temp;
	//check edge cases
	if(n == 0){
		exp = 0;
		return 0;
	}
	else if(n == INFINITY){
		return -INFINITY;
	}
	else if(n == -INFINITY){
		return INFINITY;
	}
	else if(isnan(n)){
		return nan("");
	}

	//first convert n into binary:
	double fraction, integral;
	fraction = modf (n , &integral);	//store fraction and integral into vars

	//convert integral portion into binary stored in a cstring
	char *integralBin = malloc(sizeof(char));
	memset(integralBin, '\0', 1);
	integralToBin(integralBin, integral);

	char *fractionBin = malloc(sizeof(char)*64);
	memset(fractionBin, '\0', 64);
	fractionToBin( fractionBin, fraction );
	

	//exp is equivalent to the number of digits in the binary of integral:
	*exp = strlen(integralBin);
	//printf("Exp: %d\n", *exp);
	printf("0.");
	for(i=0; i<strlen(integralBin); i++){
		printf("%c", integralBin[i]);
	}
	for(i=0; i<strlen(fractionBin); i++){
		printf("%c", fractionBin[i]);
	}
	printf(" * 2^%d", *exp);
	printf(" = %f\n", n);

	temp = malloc(sizeof(char) * (strlen(integralBin) + strlen(fractionBin) + 3));
	memset(temp, '\0', (strlen(integralBin) + strlen(fractionBin) + 3) );
	temp[0] = '0';
	temp[1] = '.';
	for(i=2; i<strlen(integralBin)+2; i++){
		temp[i] = integralBin[i-2];
	}

	for(i=strlen(integralBin)+2; i<strlen(fractionBin)+strlen(integralBin)+2; i++){
		temp[i] = fractionBin[i-strlen(integralBin)-2];
	}

	//testing
	for(i=0; i<strlen(temp); i++){
		printf("%c", temp[i]);
	}

	printf("\n");

	return atof(temp);

}