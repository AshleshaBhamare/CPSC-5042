
#include <stdio.h>
#include <stdlib.h>

int main() {

    int processSizeP;
    int blockSize = 2048;
    int internalFragmentation;
    int meanValue;
    int countOfInternalFragmentation = 0;
    int totalInternalFragmentation;


    printf("10000 random numbers in the range from [1,20000]: \n");

    for (int i = 1; i <= 10000; i++)
    {
        processSizeP = rand() % 20000 + 1;
        printf("%d\n", processSizeP);

        if (processSizeP < blockSize || processSizeP == blockSize)
        {
            internalFragmentation = (blockSize - processSizeP);

            printf("Internal Fragmentation is: %d\n", internalFragmentation);

            totalInternalFragmentation += internalFragmentation;

            countOfInternalFragmentation++;

        }
    }
    meanValue = totalInternalFragmentation / countOfInternalFragmentation;
    printf("Mean value of Internal Fragmentation: %d\n", meanValue);

    return 0;
}
