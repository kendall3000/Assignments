#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_SIZE 10000

// Structure to pass data to sorting threads
struct ThreadData {
    double *array;
    int start;
    int end;
};

// Function to perform insertion sort
void insertionSort(double *array, int size) {
    int i, j;
    double key;

    for (i = 1; i < size; i++) {
        key = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

// Function to merge two sorted subarrays
void mergeArrays(double *left, double *right, int leftSize, int rightSize, double *result) {
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            result[k++] = left[i++];
        } else {
            result[k++] = right[j++];
        }
    }

    while (i < leftSize) {
        result[k++] = left[i++];
    }

    while (j < rightSize) {
        result[k++] = right[j++];
    }
}

// Function for sorting and computing average
void *sortingThread(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;
    int start = data->start;
    int end = data->end;
    double *array = data->array;

    insertionSort(array + start, end - start + 1);

    // Calculate the average
    double sum = 0.0;
    for (int i = start; i <= end; i++) {
        sum += array[i];
    }
    double avg = sum / (end - start + 1);

    // Store the average at the beginning of the sorted subarray
    array[start] = avg;

    pthread_exit(NULL);
}

// Function for merging sorted subarrays
void *mergingThread(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;
    int start = data->start;
    int end = data->end;
    double *array = data->array;

    // Calculate the middle index to split the array
    int middle = (start + end) / 2;

    // Create temporary arrays to hold the left and right subarrays
    double left[MAX_SIZE];
    double right[MAX_SIZE];

    // Copy data to temporary arrays left[] and right[]
    for (int i = start; i <= middle; i++) {
        left[i - start] = array[i];
    }
    for (int i = middle + 1; i <= end; i++) {
        right[i - middle - 1] = array[i];
    }

    // Merge the temporary arrays back into array[l..r]
    mergeArrays(left, right, middle - start + 1, end - middle, array + start);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // Check for correct number of command-line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <array_size>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Get the size of the array from command-line argument
    int n = atoi(argv[1]);
    if (n % 2 != 0) {
        fprintf(stderr, "Array size must be even.\n");
        exit(EXIT_FAILURE);
    }

    if (n > MAX_SIZE) {
        fprintf(stderr, "Array size exceeds the maximum limit.\n");
        exit(EXIT_FAILURE);
    }

    // Seed the random number generator
    srand(time(NULL));

    // Create and initialize the array with random values
    double array[MAX_SIZE];
    for (int i = 0; i < n; i++) {
        array[i] = (double)(rand() % 1000) + 1.0;
    }

    // Split the array into two equal-sized subarrays
    int middle = n / 2;

    // Create thread data structures
    struct ThreadData data1 = {array, 0, middle - 1};
    struct ThreadData data2 = {array, middle, n - 1};

    // Initialize pthread variables
    pthread_t thread1, thread2, mergeThread;

    clock_t start_time, end_time;

    // Measure time for one thread
    start_time = clock();

    // Create threads for sorting
    pthread_create(&thread1, NULL, sortingThread, (void *)&data1);
    pthread_create(&thread2, NULL, sortingThread, (void *)&data2);

    // Wait for sorting threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Create thread data for merging
    struct ThreadData mergeData = {array, 0, n - 1};

    // Create a thread for merging
    pthread_create(&mergeThread, NULL, mergingThread, (void *)&mergeData);

    // Wait for the merging thread to finish
    pthread_join(mergeThread, NULL);

    end_time = clock();
    double execution_time_one_thread = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000.0;

    // Measure time for two threads
    start_time = clock();

    // Split the array again for two threads
    middle = n / 2;

    // Create thread data structures
    struct ThreadData data3 = {array, 0, middle - 1};
    struct ThreadData data4 = {array, middle, n - 1};

    // Create threads for sorting
    pthread_create(&thread1, NULL, sortingThread, (void *)&data3);
    pthread_create(&thread2, NULL, sortingThread, (void *)&data4);

    // Wait for sorting threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Create thread data for merging
    struct ThreadData mergeData2 = {array, 0, n - 1};

    // Create a thread for merging
    pthread_create(&mergeThread, NULL, mergingThread, (void *)&mergeData2);

    // Wait for the merging thread to finish
    pthread_join(mergeThread, NULL);

    end_time = clock();
    double execution_time_two_threads = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000.0;

    // Print execution time for one and two threads
    printf("Sorting is done in %.1fms when one thread is used\n", execution_time_one_thread);
    printf("Sorting is done in %.1fms when two threads are used\n", execution_time_two_threads);

    return 0;
}
