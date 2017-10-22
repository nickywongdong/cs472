#include <stdio.h>
#include <math.h>
#include <limits.h>


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
	int exp;
	double n = 4;

	my_frexp(n, &exp);

	return 0;
}

double my_frexp(double n, int *exp){
	int i;
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
	char *x = malloc(sizeof(char)*2048);
	integralToBin(x, integral);


	return n;

}

void integralToBin(char *x, double integral){
	int res;
	if (integral==0){
		return;
	}
	else{
		res = integral%2;
		integral = integral/2;
	}
}