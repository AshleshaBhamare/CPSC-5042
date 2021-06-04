// AUTHOR:  Ashlesha Bhamare
// PROGRAM: multithread_SortingProgram.c
// DATE:    05/31/2021
// PURPOSE: This program sorts the list of integers using threads
// PROCESS: A list of integers is divided into two smaller lists of equal
//          size. Two separate threads (which we will term sorting threads)
//          sort each sublist using a sorting algorithm of your choice. The
//          two sublists are then merged by a third thread—a merging thread
//          —which merges the two sublists into a single sorted list. Because
//          global data are shared across all threads, perhaps the easiest way
//          to set up the data is to create a global array. Each sorting
//          thread will work on half of this array. A second global array of
//          the same size as the unsorted integer array will also be
//          established. The merging thread will then merge the two sublists
//          into the second array.
// OUTPUT: Prints the Sorted list of integers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define SIZE 10
#define NUMBER_OF_THREADS 3

void *sorter(void *params);
void *merger(void *params);
int* list =NULL;
int result[SIZE];

typedef struct
{
    int from;
    int to;
} parameters;

int main (void)
{
    int i;
    pthread_t workers[NUMBER_OF_THREADS];
    int maxsize;

    printf("\nEnter number of elements to be sorted: ");
    scanf("%d",&maxsize);

    list = calloc(maxsize, sizeof(int));
    printf("\nEnter number of elements of the array : ");

    // taking input and storing it in an array
    for(int i = 0; i < maxsize; ++i)
    {
        scanf("%d", &list[i]);
    }

    printf("num= %d", maxsize);
    printf(", half size= %d", maxsize/2);

    printf("\n");
    printf("\nSorted array: ");

    // creates the first sorting thread
    parameters *data = (parameters *) malloc (maxsize / 2 * sizeof(parameters));
    data->from = 0;
    data->to = (maxsize/2) - 1;
    pthread_create(&workers[0], 0, sorter, data);

    //creates the second sorting thread
    data = (parameters *) malloc (maxsize/2 * sizeof(parameters));
    data->from = (maxsize/2);
    data->to = maxsize - 1;
    pthread_create(&workers[1], 0, sorter, data);

    // wait for the 2 sorting threads to finish
    for (i = 0; i < NUMBER_OF_THREADS - 1; i++)
    {
        pthread_join(workers[i], NULL);
    }

    // creates the merge thread
    data = (parameters *) malloc ( maxsize * sizeof(parameters));
    data->from = 0;
    data->to =  maxsize - 1;
    pthread_create(&workers[2], 0, merger, data);

    // wait for the merge thread to finish
    pthread_join(workers[2], NULL);

    // sorted array output
    for(i = 0; i < maxsize; i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
// Sorting thread.
void *sorter(void *params)
{
    parameters* p = (parameters *)params;

    int begin = p->from;
    int end = p->to + 1;

    int temp = 0;
    for(int i = begin; i < end; i++)
    {
        for(int j = begin; j < end - 1; j++)
        {
            if(list[j] > list[j + 1])
            {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
    pthread_exit(NULL);
}
//merging thread
void *merger(void *params)
{
    parameters* p = (parameters *)params;
    int end = p->to + 1;
    int half = end/2;
    int j, i, k;
    for(i = 0, j = half, k = 0; i < half && j < end; k++)
    {
        if(list[i] < list[j])
        {
            result[k] = list[i];
            i++;
        }else
        {
            result[k] = list[j];
            j++;
        }
    }
    while(j < end)
    {
        result[k] = list[j];
        j++; k++;
    }
    while(i < half)
    {
        result[k] = list[i];
        i++; k++;
    }
    pthread_exit(NULL);
}