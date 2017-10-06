	#include <stdio.h>
	#include <string.h>

	int main(int argc, char **argv)
	{

		//unsigned int eax;
		unsigned int ebx;
		unsigned int ecx;
		unsigned int edx;

		char vendor[13];
		
		/*eax = 0x00;

		__asm__ __volatile__(
			"cpuid;"
			: "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
			: "a"(eax)
			);


		memcpy(vendor, (char*)&ebx, 4);
		memcpy(vendor + 4, (char*)&edx, 4);
		memcpy(vendor + 8, (char*)&ecx, 4);
		vendor[12] = 0;

		printf("%s\n", vendor);*/
		unsigned int eax[16] = {[0 ... 15] = 0x20};
		int i;
		for(i=0; i<16; i++){
			__asm__ __volatile__(
			"cpuid;"
			: "=a"(eax[i]), "=b"(ebx), "=c"(ecx), "=d"(edx)
			: "a"(eax[i])
			);


		memcpy(vendor, (char*)&ebx, 4);
		memcpy(vendor + 4, (char*)&edx, 4);
		memcpy(vendor + 8, (char*)&ecx, 4);
		vendor[12] = 0;

		printf("%s\n", vendor);
		}
		
		return 0;
	}