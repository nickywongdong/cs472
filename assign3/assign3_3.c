/*
Idea for strides and testing array access: http://www.it.uu.se/edu/course/homepage/avdark/ht11/slides/11_Memory_and_optimization-1.pdf
Stems from Question on SO:
https://stackoverflow.com/questions/12594208/c-program-to-determine-levels-size-of-cache
*/

#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <string.h>

#define KB 1024
#define MB 1024 * 1024
#define Max = 100000000


int main() {
    int i, j, times, dummy;
    double timeTaken, average = 0;
    clock_t start;
    int A[16];
    int Strides[] = { 
        1 * KB, 4 * KB, 8 * KB, 16 * KB, 32 * KB, 64 * KB, 128 * KB, 256 * KB,
        512 * KB, 1 * MB, 1.5 * MB, 2 * MB, 2.5 * MB, 3 * MB, 3.5 * MB, 4 * MB
    };
    memset(A, 0, 16);

    start = clock();

    for(j=0; j<sizeof(Strides)/sizeof(int); j++){
    	for(times = 0; times < Max; times++){
			for(i = 0; i < sizeof(A)/sizeof(int); i = i + Strides[j]){
				dummy = A[i];
			}
			average += (double)(clock() - start)/CLOCKS_PER_SEC;
		}

		timeTaken = average/Max;
		printf("Time for %d: %.12f \n", Strides[j]/KB, timeTaken);
	}
}
