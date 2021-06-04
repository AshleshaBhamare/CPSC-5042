// AUTHOR:  Ashlesha Bhamare
// PROGRAM: multithread_calculateValues.c
// DATE:    05/31/2021
// PURPOSE: This program calculates various statistical values for a list of
//          numbers.
// PROCESS: This program will take a series of numbers on the command line
//          and creates three separate worker threads. One thread will
//          determine the average of the numbers, the second will determine the
//          maximum value, and the third will determine the minimum value.
// OUTPUT:  Prints the calculates values.
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

double average;
int size;
int maxValue = -100000;
int minValue = 100000;

void* averageValue_runner(void *arg) {

    int *array = (int *) arg;
    int sum = 0;

    for(int i = 0; i < size; i++){
        sum += array[i];
    }
    average = sum / (size);

    pthread_exit(0);
}
void* minimumValue_runner(void *arg)
{
    int *array = (int *) arg;
    for(int i = 0; i < size; i++)
    {
        if(i == 0)
        {
            minValue = array[i];
        }
        else if (minValue > array[i])
            minValue = array[i];
    }

    pthread_exit(0);
}
void* maximumValue_runner(void *arg)
{
    int *array = (int *) arg;
    for(int i = 0; i < size; i++)
    {
        if(i == 0)
        {
            maxValue = array[i];
        }
        else if (maxValue < array[i])
            maxValue = array[i];
    }

    pthread_exit(0);
}

int main(int argc, char *argv[] )
{
    int *nums = (int*)malloc((argc - 1)*sizeof(int));

    for(int i = 1; i < argc ; i++){
        nums[i-1] = atoi(argv[i]);
        size++;
    }

    pthread_t my_thread1;
    pthread_t my_thread2;
    pthread_t my_thread3;

    pthread_create(&my_thread1, NULL, averageValue_runner,(void*) nums);
    pthread_create(&my_thread2, NULL, minimumValue_runner, (void*) nums);
    pthread_create(&my_thread3, NULL, maximumValue_runner, (void*) nums);

    pthread_join(my_thread1, NULL);
    pthread_join(my_thread2, NULL);
    pthread_join(my_thread3, NULL);

    printf("The average value is: %f\n", average);
    printf("The minimum value is: %d\n", minValue);
    printf("The maximum value is: %d\n", maxValue);
}