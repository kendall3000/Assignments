#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MAX_PROCESS 100

struct Process {
    int id;
    int priority;
    int* bursts;// An array to store CPU and I/O burst times
    int num_bursts;
};

void enqueueProcess(struct Process process);

volatile sig_atomic_t termination_requested = 0;

pthread_mutex_t readyQueueMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t readyQueueNotEmpty = PTHREAD_COND_INITIALIZER;

struct Process readyQueue[MAX_PROCESS];
int numProcesses = 0;

void handle_termination(int signum) {
    termination_requested = 1;
}

void cleanup() {// Free dynamically allocated memory for bursts in each Process
    for (int i = 0; i < numProcesses; i++) {
        free(readyQueue[i].bursts);
    }
}

/*void readInputFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open the input file");
        exit(1);
    }

    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {// Parse the line to extract process data (modify as per your input file format)
        int id, priority, num_bursts;
        int burst_times[100];
        printf("Read line: %s", line);

        if (sscanf(line, "%d %d %d", &id, &priority, &num_bursts) == 3) {
            struct Process newProcess;
            newProcess.id = id;
            newProcess.priority = priority;
            newProcess.num_bursts = num_bursts;

            for (int i = 0; i < num_bursts; i++) {
                if (fgets(line, sizeof(line), file) != NULL) { // Parse and store burst times (CPU and I/O bursts)
                    if (sscanf(line, "%d", &burst_times[i]) != 1) {
                        perror("Error parsing burst time");
                        exit(1);
                    }
                } else {
                    perror("Error reading burst time");
                    exit(1);
                }
            }

            // Allocate memory for burst times array and copy the burst times
            newProcess.bursts = (int*)malloc(num_bursts * sizeof(int));
            if (newProcess.bursts == NULL) {
                perror("Memory allocation failed");
                exit(1);
            }
            memcpy(newProcess.bursts, burst_times, num_bursts * sizeof(int));

            // Add the new process to the ready queue (ensure proper synchronization)
            pthread_mutex_lock(&readyQueueMutex);
            enqueueProcess(newProcess);
            pthread_mutex_unlock(&readyQueueMutex);
        } else {
            perror("Error parsing process data");
            exit(1);
        }
    }

    fclose(file);
}*/

void readInputFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open the input file");
        exit(1);
    }

    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '\n' || line[0] == '\r') {
            continue;  // Skip empty lines
        }

        printf("Read line: %s", line);
        // Parse the line to extract process data
        int id, priority, num_bursts;
        int burst_times[100]; // Adjust the array size as needed

        if (sscanf(line, "proc %d %d %d", &id, &priority, &num_bursts) == 3) {
            struct Process newProcess;
            newProcess.id = id;
            newProcess.priority = priority;
            newProcess.num_bursts = num_bursts;

            for (int i = 0; i < num_bursts; i++) {
                if (fgets(line, sizeof(line), file) != NULL) {
                    if (sscanf(line, "%d", &burst_times[i]) != 1) {
                        perror("Error parsing burst time");
                        exit(1);
                    }
                } else {
                    perror("Error reading burst time");
                    exit(1);
                }
            }

            // Allocate memory for burst times array and copy the burst times
            newProcess.bursts = (int*)malloc(num_bursts * sizeof(int));
            if (newProcess.bursts == NULL) {
                perror("Memory allocation failed");
                exit(1);
            }
            memcpy(newProcess.bursts, burst_times, num_bursts * sizeof(int));

            // Add the new process to the ready queue
            pthread_mutex_lock(&readyQueueMutex);
            enqueueProcess(newProcess);
            pthread_mutex_unlock(&readyQueueMutex);
        }
    }

    fclose(file);
}


void enqueueProcess(struct Process process) {
    if (numProcesses < MAX_PROCESS) {
        readyQueue[numProcesses] = process; // Get the first process in the queue
        numProcesses++;
    } else { // Shift the remaining processes to fill the gap
        fprintf(stderr, "Ready queue is full. Cannot enqueue the process.\n");
    }
}

struct Process dequeueProcess() {
    struct Process p;

    if (numProcesses > 0) {
        p = readyQueue[0];
        numProcesses--;

        for (int i = 0; i < numProcesses; i++) {
            readyQueue[i] = readyQueue[i + 1];
        }

        memset(&readyQueue[numProcesses], 0, sizeof(struct Process)); // Reset the last slot to avoid referencing the removed process
    } else {// If the queue is empty, return a default empty process
        memset(&p, 0, sizeof(struct Process));
    }

    return p;
}

void shiftBursts(struct Process *process) {
    if (process->num_bursts > 0) { // Shift the bursts array to remove the completed burst
        for (int i = 0; i < process->num_bursts - 1; i++) {
            process->bursts[i] = process->bursts[i + 1];
        }
        process->num_bursts--; // Decrement the number of bursts
    }
}

int compareByBurstTime(const void* a, const void* b) {
    return ((struct Process*)a)->bursts[0] - ((struct Process*)b)->bursts[0];
}

int compareByPriority(const void* a, const void* b) {
    return ((struct Process*)b)->priority - ((struct Process*)a)->priority;
}

void calculateAndPrintMetrics(const char* inputFileName, const char* alg, double cpuUtilization) {
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;
    int totalBurstTime = 0;
    int totalProcesses = 0;

    for (int i = 0; i < numProcesses; i++) {
        totalTurnaroundTime += totalBurstTime - readyQueue[i].bursts[0];
        totalBurstTime += readyQueue[i].bursts[0];
        totalWaitingTime += totalBurstTime;
        totalProcesses++;
    }

    double throughput = (double)totalProcesses / totalBurstTime; 
    double avgTurnaroundTime = (double)totalTurnaroundTime / totalProcesses;
    double avgWaitingTime = (double)totalWaitingTime / totalProcesses;

    printf("-------------------------------------------------------\n");
    printf("Input File Name : %s\n", inputFileName);
    printf("CPU Scheduling Alg : %s\n", alg);
    printf("CPU utilization : %.3f%%\n", cpuUtilization);
    printf("Throughput : %.3f processes / ms\n", throughput);
    printf("Avg. Turnaround time : %.1fms\n", avgTurnaroundTime);
    printf("Avg. Waiting time in R queue : %.1fms\n", avgWaitingTime);
    printf("-------------------------------------------------------\n");
}

void FIFO_scheduler(const char* inputFileName) {
    double cpuUtilization = 0;
    int totalBurstTime = 0;
    int lastCompletionTime = 0;

    while (numProcesses > 0) {
        pthread_mutex_lock(&readyQueueMutex);
        struct Process currentProcess = dequeueProcess();
        pthread_mutex_unlock(&readyQueueMutex);

        // Simulate CPU execution for the current process
        int burst_time = currentProcess.bursts[0];
        int remaining_burst_time = (lastCompletionTime + burst_time) - totalBurstTime;
        cpuUtilization += (double)burst_time / remaining_burst_time; // Assuming totalBurstTime is the total execution time
        sleep(burst_time);

        lastCompletionTime += burst_time;
        totalBurstTime += burst_time;

        shiftBursts(&currentProcess); // Shift bursts for the completed process

        if (currentProcess.num_bursts > 0) { // Check if the process has more bursts
            pthread_mutex_lock(&readyQueueMutex);
            enqueueProcess(currentProcess);
            pthread_mutex_unlock(&readyQueueMutex);
        }
    }

    calculateAndPrintMetrics(inputFileName, "FIFO", cpuUtilization * 100);
}

void SJF_scheduler(const char* inputFileName) {
    double cpuUtilization = 0;
    int totalBurstTime = 0;
    int lastCompletionTime = 0;

    while (numProcesses > 0) { // Sort processes by burst time (shortest first)
        pthread_mutex_lock(&readyQueueMutex);
        qsort(readyQueue, numProcesses, sizeof(struct Process), compareByBurstTime);
        struct Process currentProcess = dequeueProcess();
        pthread_mutex_unlock(&readyQueueMutex);

        // Simulate CPU execution for the current process
        int burst_time = currentProcess.bursts[0]; 
        int remaining_burst_time = (lastCompletionTime + burst_time) - totalBurstTime;
        cpuUtilization += (double)burst_time / remaining_burst_time;
        sleep(burst_time);

        lastCompletionTime += burst_time;
        totalBurstTime += burst_time;

        shiftBursts(&currentProcess); // Shift bursts for the completed process

        if (currentProcess.num_bursts > 0) { // Check if the process has more bursts
            pthread_mutex_lock(&readyQueueMutex);
            enqueueProcess(currentProcess);
            pthread_mutex_unlock(&readyQueueMutex);
        }
    }

    calculateAndPrintMetrics(inputFileName, "SJF", cpuUtilization * 100);
}

void PR_scheduler(const char* inputFileName) {
    double cpuUtilization = 0;
    int totalBurstTime = 0;
    int lastCompletionTime = 0;

    while (numProcesses > 0) { // Sort processes by priority (highest priority first)
        pthread_mutex_lock(&readyQueueMutex);
        qsort(readyQueue, numProcesses, sizeof(struct Process), compareByPriority);
        struct Process currentProcess = dequeueProcess();
        pthread_mutex_unlock(&readyQueueMutex);

        int burst_time = currentProcess.bursts[0]; // Simulate CPU execution for the current process
        int remaining_burst_time = (lastCompletionTime + burst_time) - totalBurstTime;
        cpuUtilization += (double)burst_time / remaining_burst_time;
        sleep(burst_time);

        lastCompletionTime += burst_time;
        totalBurstTime += burst_time;

        shiftBursts(&currentProcess); // Shift bursts for the completed process

        if (currentProcess.num_bursts > 0) { // Check if the process has more bursts
            pthread_mutex_lock(&readyQueueMutex);
            enqueueProcess(currentProcess);
            pthread_mutex_unlock(&readyQueueMutex);
        }
    }

    calculateAndPrintMetrics(inputFileName, "PR", cpuUtilization * 100);
}

void RR_scheduler(const char* inputFileName, int quantum) {
    double cpuUtilization = 0;
    int totalBurstTime = 0;
    int lastCompletionTime = 0;

    int currentProcessIndex = 0;
    int remainingTimes[MAX_PROCESS];

    // Initialize remaining times for each process
    for (int i = 0; i < numProcesses; i++) {
        remainingTimes[i] = readyQueue[i].bursts[0];
    }

    while (numProcesses > 0) {
        pthread_mutex_lock(&readyQueueMutex);
        struct Process currentProcess = dequeueProcess();
        pthread_mutex_unlock(&readyQueueMutex);

        int burst_time = (remainingTimes[currentProcessIndex] < quantum) ? remainingTimes[currentProcessIndex] : quantum;
        int remaining_burst_time = (lastCompletionTime + burst_time) - totalBurstTime;
        cpuUtilization += (double)burst_time / remaining_burst_time;

        sleep(burst_time);
        remainingTimes[currentProcessIndex] -= burst_time;

        lastCompletionTime += burst_time;
        totalBurstTime += burst_time;

        shiftBursts(&currentProcess); // Shift bursts for the completed process

        if (currentProcess.num_bursts > 0) { // Check if the process has more bursts
            pthread_mutex_lock(&readyQueueMutex);
            enqueueProcess(currentProcess);
            pthread_mutex_unlock(&readyQueueMutex);
        }

        currentProcessIndex = (currentProcessIndex + 1) % numProcesses;
    }

    calculateAndPrintMetrics(inputFileName, "RR quantum: 10", cpuUtilization * 100);
}

int main(int argc, char* argv[]) {
    // Signal handler for termination
    signal(SIGINT, handle_termination);

    if (argc < 5) {
        printf("Usage: %s -alg [FIFO|SJF|PR|RR] [-quantum <integer(ms)>] -input <file name>\n", argv[0]);
        return 1;
    }

    // Default quantum value for RR scheduling
    int quantum = 0;
    char* schedulingAlgorithm = NULL;
    char* inputFileName = NULL;

    // Parse command-line arguments for scheduling algorithm, quantum, and input file
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-alg") == 0) {
            if (i + 1 < argc) {
                schedulingAlgorithm = argv[i + 1];
                i++;
            } else {
                printf("Missing scheduling algorithm argument.\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-quantum") == 0) {
            if (i + 1 < argc) {
                quantum = atoi(argv[i + 1]);
                i++;
            } else {
                printf("Missing quantum argument.\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-input") == 0) {
            if (i + 1 < argc) {
                inputFileName = argv[i + 1];
                i++;
            } else {
                printf("Missing input file name argument.\n");
                return 1;
            }
        }
    }

    if (schedulingAlgorithm == NULL || inputFileName == NULL) {
        printf("Missing scheduling algorithm or input file name.\n");
        return 1;
    }

    readInputFile(inputFileName); // Read process data from the input file
    
    // Create a thread for the chosen scheduling algorithm
    pthread_t schedulerThread;
    if (strcmp(schedulingAlgorithm, "FIFO") == 0) {
        pthread_create(&schedulerThread, NULL, (void* (*)(void*))FIFO_scheduler, inputFileName);
    } else if (strcmp(schedulingAlgorithm, "SJF") == 0) {
        pthread_create(&schedulerThread, NULL, (void* (*)(void*))SJF_scheduler, inputFileName);
    } else if (strcmp(schedulingAlgorithm, "PR") == 0) {
        pthread_create(&schedulerThread, NULL, (void* (*)(void*))PR_scheduler, inputFileName);
    } else if (strcmp(schedulingAlgorithm, "RR") == 0) {
        pthread_create(&schedulerThread, NULL, (void* (*)(void*))RR_scheduler, (void*)&quantum);
    } else {
        printf("Invalid scheduling algorithm.\n");
        return 1;
    }
    // Wait for the scheduler thread to finish
    pthread_join(schedulerThread, NULL);

    // Clean up allocated memory
    cleanup();

    return 0;
}

