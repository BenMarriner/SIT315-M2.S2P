#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <thread>

#define NUM_THREADS 12

using namespace std::chrono;
using namespace std;

struct RandomTask
{
    int* v;
    int start;
    int end;
};

struct AddTask
{
    int *v1, *v2, *v3;
    int start;
    int end;
};

void randomVector(void* args)
{
    RandomTask* task = ((struct RandomTask*)args);

    for (int i = task->start; i < task->end; i++)
    {
        // Fill the vector with random numbers
        task->v[i] = rand() % 100;
    }
}

void addVector(void* args)
{
    AddTask* task = ((struct AddTask*)args);

    for (int i = task->start; i < task->end; i++)
    {
        task->v3[i] = task->v1[i] + task->v2[i];
    }
}

int main(){

    unsigned long size = 100000000;

    srand(time(0));

    int *v1, *v2, *v3;

    // Start the timer
    auto start = high_resolution_clock::now();

    //ToDo: Add Comment
    v1 = (int *) malloc(size * sizeof(int *));
    v2 = (int *) malloc(size * sizeof(int *));
    v3 = (int *) malloc(size * sizeof(int *));

    int partition_size = size / NUM_THREADS;

    thread add_threads[NUM_THREADS];
    thread random_threads[NUM_THREADS];

    for (size_t i = 0; i < NUM_THREADS; i++)
    {
        // Create random vector tasks for threads
        RandomTask* random_task = (RandomTask*)malloc(sizeof(RandomTask));
        
        // Check if pointer is valid
        if (!v1 || !v2 || !v3) return -1;
        random_task->v = v1;
        random_task->start = i * partition_size;
        random_task->end = random_task->start + partition_size - 1;

        // Initialise the threads
        random_threads[i] = thread(randomVector, random_task);
    }

    for (size_t i = 0; i < NUM_THREADS; i++)
    {
        random_threads[i].join();
    }

    for (size_t i = 0; i < NUM_THREADS; i++)
    {
        AddTask* add_task = (AddTask*)malloc(sizeof(AddTask));
        
        // Check if pointer is valid
        if (!v1 || !v2 || !v3) return -1;
        add_task->v1 = v1;
        add_task->v2 = v2;
        add_task->v3 = v3;
        add_task->start = i * partition_size;
        add_task->end = add_task->start + partition_size - 1;

        add_threads[i] = thread(addVector, add_task);
    }

    for (size_t i = 0; i < NUM_THREADS; i++)
    {
        add_threads[i].join();
    }

    // Stop the timer
    auto stop = high_resolution_clock::now();

    // Calculate computing time
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    return 0;
}