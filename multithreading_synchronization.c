// AUTHOR:  Ashlesha Bhamare
// PROGRAM: multithread_synchronization.c
// DATE:    05/31/2021
// PURPOSE: This program explores synchronization challenges
// PROCESS: Assume that we have a shared variable allowed_ID.
//          This variable is initialized to 1 at the beginning. Now create
//          three threads in your program and assign ID 1,2,3 to them,
//          respectively. Pass the ID as a parameter when you create the
//          threads. Each of the threads will try to access the variable
//          “allowed_ID.” Whenever a thread reads this variable, it checks
//          whether the allowed_ID is equal to its ID or not. If, for example,
//          thread 2 reads allowed_ID and sees that this variable is not 2,
//          it prints “Not thread 2’s turn” and releases the variable.
//          Otherwise, thread 2 prints “Thread 2’s turn!” and increases
//          the allowed_ID by 1, and releases the variable. However, after
//          increasing allowed_ID by 1, if it is 4, the thread will reset
//          the variable to 1 before releasing the variable.
// OUTPUT: The program executes until each thread prints “Thread i’s
//         turn!” two times. Once a thread prints this message twice, it
//         terminates

#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3
int allowed_ID;
int thread_count[3];
int thread_repeat_count[3];

static pthread_mutex_t cs_mutex;

void printTurn(long tid)
{
    while (thread_count[tid] < 2)
    {
        pthread_mutex_lock(&cs_mutex);

        if (allowed_ID == tid)
        {
            printf("Thread %d's Turn!\n", tid);
            thread_count[tid]++;
            allowed_ID++;

            if (allowed_ID == NUM_THREADS + 1)
            {
                allowed_ID = 1;
            }
        }
        else if(thread_repeat_count[tid] < 2)
        {
            thread_repeat_count[tid]++;
            printf("Not thread %d's Turn!\n", tid);
        }

        pthread_mutex_unlock(&cs_mutex);

    }
    printf("Thread %d is complete\n", tid);
}

int main()
{
    pthread_t threads[NUM_THREADS];

    allowed_ID = 1;

    pthread_create(&threads[1], NULL, printTurn, (void *) 1);
    pthread_create(&threads[2], NULL, printTurn, (void *) 2);
    pthread_create(&threads[3], NULL, printTurn, (void *) 3);

    pthread_exit(NULL);
}