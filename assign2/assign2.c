#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <time.h>

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

//extended from the idea https://stackoverflow.com/questions/15685181/how-to-get-the-sign-mantissa-and-exponent-of-a-floating-point-number
typedef union {
  double d;
  struct {
    uint64_t mantissa : 52;
    uint64_t exponent : 11;
    uint64_t sign : 1;
  } parts;
} double_cast;


double my_frexp(double, int *);
void sum(double, double);
void sub( double, double );
void mult( double, double );
void extract( double );

int main(){
	clock_t start, end;
    double cpu_time_used, time_taken;
	int exp, i;
	double n, op1, op2;
	char *expression;
	printf("Enter a double: ");
	scanf("%lf", &n);

	n = my_frexp(n, &exp);

	//printf("output: %.32lf\n", n);
	printf("exponent: %d\n", exp);

	printf("two numbers to add: ");
	scanf("%lf %lf" ,&op1, &op2);
	start = clock();
	sum(op1, op2);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("sum() took %f seconds to execute \n", cpu_time_used);

	printf("two numbers to subtract: ");
	scanf("%lf %lf" ,&op1, &op2);
	start = clock();
	sub(op1, op2);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("sub() took %f seconds to execute \n", cpu_time_used);


	printf("two numbers to multiply: ");
	scanf("%lf %lf" ,&op1, &op2);
	start = clock();
	mult(op1, op2);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("mult() took %f seconds to execute \n", cpu_time_used);

	printf("Enter a double: ");
	scanf("%lf", &n);
	extract(n);
	return 0;
}

void extract(double x){
	double_cast d1 = { .d = x };

	printf("sign = %x\n", d1.parts.sign);
	printf("exponent = %x\n", d1.parts.exponent);
	printf("mantisa = %x\n", d1.parts.mantissa);
}

void sum(double x, double y){
	int exp1, exp2, i, res;
	double res1, res2;
	printf("Adding \t");
	res1 = my_frexp(x, &exp1);
	printf("and...\t");
	res2 = my_frexp(y, &exp2);
	int frac1, frac2, temp1, temp2;
	char buffer1[64], buffer2[64];
	int intBuff1[64], intBuff2[64], intBuff3[64], carry=0;

	//goal is to align the two exponents, then take XOR of left side (adding them), and return that with same exponent
	for(i=0; i<abs(exp1-exp2); i++){
		if(exp1>exp2){
			res2 /= 10;	//essentially right shift
		}
		else{
			res1 /= 10;	//figure it out later
		}
	}
	//convert both res into "int", essentially remove "0." so we can XOR
	//idea to split double into two ints (fraction and integral) source: https://stackoverflow.com/questions/15387028/how-to-get-the-integer-and-fractional-part-of-a-decimal-number-as-two-integers-i
	sprintf(buffer1, "%lf", res1);
	sprintf(buffer2, "%lf", res2);
	sscanf(buffer1, "%d.%d", &temp1, &frac1);
	sscanf(buffer2, "%d.%d", &temp2, &frac2);

	//convert the fraction portion into an int array so we can take the xor of each index
	sprintf(buffer1, "%d", frac1);
	for(i=0; i<strlen(buffer1); i++){
		intBuff1[i] = buffer1[i] - '0';
	}

	sprintf(buffer2, "%d", frac2);
	for(i=0; i<strlen(buffer2); i++){
		intBuff2[i] = buffer2[i] - '0';
	}
	
	//start adding the two fractions using XOR, starting from the end and remembering carry bit
	for(i=strlen(buffer1)-1; i>=0; i--){		//leave first position open for carry bit
		intBuff3[i+1] = intBuff1[i] ^ intBuff2[i] ^ carry;
		carry = ((intBuff1[i] & intBuff2[i]) | (intBuff1[i] & carry)) | (intBuff2[i] & carry); //ab+bc+ca
	}
	intBuff3[0] = carry;

	//print out solution
	printf("0.");
	for(i=0; i<strlen(buffer1); i++){
		printf("%d", intBuff3[i]);
	}
	printf(" * 2 ^ %f\n", fmin(exp1, exp2));
}

void sub(double x, double y){
//simply use add with x, and two's complement of y

	int exp1, exp2, i, res, frac1, frac2, temp1, temp2;
	double res1, res2;
	char buffer1[64], buffer2[64];
	int intBuff1[64], intBuff2[64], intBuff3[64], intBuff4[64], carry=0;
	int *twos;

	printf("Subtracting \t");
	res1 = my_frexp(x, &exp1);
	printf("and...\t");
	res2 = my_frexp(y, &exp2);

	//shift until both align
	for(i=0; i<abs(exp1-exp2); i++){
		if(exp1>exp2){
			res2 /= 10;	//essentially right shift
		}
		else{
			res1 /= 10;	//figure it out later
		}
	}

	//extract the fraction part and store as char array
	sprintf(buffer1, "%lf", res1);
	sprintf(buffer2, "%lf", res2);
	sscanf(buffer1, "%d.%d", &temp1, &frac1);
	sscanf(buffer2, "%d.%d", &temp2, &frac2);

	//convert char array into int array
	sprintf(buffer1, "%d", frac1);
	for(i=0; i<strlen(buffer1); i++){
		intBuff1[i] = buffer1[i] - '0';
	}

	sprintf(buffer2, "%d", frac2);
	for(i=0; i<strlen(buffer2); i++){
		intBuff2[i] = buffer2[i] - '0';
	}

	twos = malloc(strlen(buffer2) * sizeof(int));
	memset(twos, 0, strlen(buffer2));
	twos[strlen(buffer2)-1] = 1;

	//convert y's fraction into one's copmlement
	for(i=0; i<strlen(buffer2); i++){
		if(intBuff2[i] == 1){
			intBuff2[i] = 0;
		}
		else{
			intBuff2[i] = 1;
		}
	}

	//add 1 to one's complement to make two's complement:

	for(i=strlen(buffer1)-1; i>=0; i--){		//leave first position open for carry bit
		intBuff3[i+1] = intBuff2[i] ^ twos[i] ^ carry;
		carry = ((intBuff2[i] & twos[i]) | (intBuff2[i] & carry)) | (twos[i] & carry); //ab+bc+ca
	}
	intBuff3[0] = carry;

	for(i=0; i<strlen(buffer2); i++){
		printf("%d", intBuff3[i]);
	}
	printf("\n");
	//add the two fractions
	carry=0;
	for(i=strlen(buffer1)-1; i>=0; i--){		//leave first position open for carry bit
		intBuff4[i+1] = intBuff1[i] ^ intBuff3[i] ^ carry;
		carry = ((intBuff1[i] & intBuff3[i]) | (intBuff1[i] & carry)) | (intBuff3[i] & carry); //ab+bc+ca
	}
	intBuff4[0] = carry;

	//print out solution
	printf("0.");
	for(i=0; i<strlen(buffer1); i++){
		printf("%d", intBuff4[i]);
	}
	printf(" * 2 ^ %f\n", fmin(exp1, exp2));

}

void mult(double x, double y){
	int **buffer;
	int exp1, exp2, res, frac1, frac2, temp1, temp2, i, j, n, shift;
	double res1, res2;
	char buffer1[64], buffer2[64];
	int intBuff1[64], intBuff2[64], intBuff3[64], intBuff4[64], carry=0;


	printf("multiplying \t");
	res1 = my_frexp(x, &exp1);
	printf("and...\t");
	res2 = my_frexp(y, &exp2);

	//shift until both align
	for(i=0; i<abs(exp1-exp2); i++){
		if(exp1>exp2){
			res2 /= 10;	//essentially right shift
		}
		else{
			res1 /= 10;	//figure it out later
		}
	}

	//extract the fraction part and store as char array
	sprintf(buffer1, "%lf", res1);
	sprintf(buffer2, "%lf", res2);
	sscanf(buffer1, "%d.%d", &temp1, &frac1);
	sscanf(buffer2, "%d.%d", &temp2, &frac2);

	//convert char array into int array
	sprintf(buffer1, "%d", frac1);
	for(i=0; i<strlen(buffer1); i++){
		intBuff1[i] = buffer1[i] - '0';
		printf("%d", intBuff1[i]);
	}
	printf("\n");

	sprintf(buffer2, "%d", frac2);
	for(i=0; i<strlen(buffer2); i++){
		intBuff2[i] = buffer2[i] - '0';
	}


	//allocate memory for 2D array to store multiplication shifting
	n=strlen(buffer1)+strlen(buffer2) - 1;	//how long the shifting array should be

	//testing
	/*for(i=0; i<strlen(buffer1); i++){
		printf("%c", buffer1[i]);
	}*/

	buffer = malloc(sizeof(int *) * strlen(buffer2) );
	for(i=0; i<strlen(buffer2); i++){
		buffer[i] = malloc(sizeof(int) * n );
		memset(buffer[i], 0, n);
	}

	//testing
	/*printf("before multiplying..\n");
	for(i=0; i<strlen(buffer2); i++){
		for(j=0; j<n; j++){
			printf("%x", buffer[i][j]);
		}
		printf("\n");
	}*/

	shift=0;
	//multiply by shifting algorithm
	for(i=strlen(buffer1)-1; i>=0; i--){
		for(j=strlen(buffer2)-1; j>=0; j--){
			buffer[i][j+shift] = intBuff1[j] * intBuff2[i];
		}
	}

	//testing
	/*printf("after multiplying...\n");
	for(i=0; i<strlen(buffer2); i++){
		for(j=0; j<n; j++){
			printf("%x", buffer[i][j]);
		}
		printf("\n");
	}*/

	//sum all rows to find the result
}

void myDiv(double x, double y){
}

void mySqrt(double x){

}


void integralToBin(char *bin, int n){
	//unsigned long bin = 0;
	int j=0, i, flag = 0;
	for(i = 31; i>=0; i--){
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
	for(i=0; i<64; i++){
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
	/*printf("testing: \n");
	for(i=0; i<strlen(temp); i++){
		printf("%c", temp[i]);
	}
	printf("\n");*/

	return atof(temp);

}