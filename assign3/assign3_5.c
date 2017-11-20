#include <stdio.h>
#include <stdbool.h>


/*
Source: https://stackoverflow.com/questions/4239993/determining-endianness-at-compile-time

Create an integer, and read its first byte (least significant byte). 
If that byte is 1, then the system is little endian, otherwise it's big endian.
*/
bool isLittleEndian()
{
    short int number = 0x1;
    char *numPtr = (char*)&number;
    return (numPtr[0] == 1);
}

int main(int argc, char **argv)
{
	short val;
	char *p_val;
	p_val = (char *) &val;
	/*
	  The following two lines assume big-endian
	  Architecture to initialize the variable Val
	  to 0x1234.
	*/

	p_val[0] = 0x12;
	p_val[1] = 0x34;

	//Byte swap if Little Endian, otherwise do not
	if(isLittleEndian()){
		//mask bottom byte,
		//mask top byte,
		//logical OR of both to "swap"
		printf("%x\n", ( ((val << 8) & 0xff00) | (( val >> 8 ) & 0x00ff)));
	}
	//Big Endian
	else{
		printf("%x\n", val);
	}
	
	return 0;
}