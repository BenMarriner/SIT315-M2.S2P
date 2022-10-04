#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>


using namespace std::chrono;
using namespace std;

void randomVector(int vector[], int size)
{
    for (int i = 0; i < size; i++)
    {
        // Fill the vector with random numbers
        vector[i] = rand() % 100;
    }
}

int main2(){

    unsigned long size = 100000000;

    srand(time(0));

    int *v1, *v2, *v3;

    // Start the timer
    auto start = high_resolution_clock::now();

    // Allocate memory to vectors
    v1 = (int *) malloc(size * sizeof(int *));
    v2 = (int *) malloc(size * sizeof(int *));
    v3 = (int *) malloc(size * sizeof(int *));


    randomVector(v1, size);

    randomVector(v2, size);


    // Add vectors together
    for (int i = 0; i < size; i++)
    {
        v3[i] = v1[i] + v2[i];
    }

    auto stop = high_resolution_clock::now();

    // Calculate computing time
    auto duration = duration_cast<microseconds>(stop - start);


    cout << "Time taken by function: "
         << duration.count() << " milliseconds" << endl;

    return 0;
}