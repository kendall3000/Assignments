/*
* File: multiple_wordcount.c
* Kendall Ramos ... YOU NEED TO IMPLEMENT THE FUNCTIONS HERE....
*
* ....
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    // Check if at least one input file is provided
    if (argc < 2) {
        printf("Usage: %s <input_file1> <input_file2> ... <input_fileN>\n", argv[0]);
        return 1;
    }

    int successCount = 0;
    int failureCount = 0;

    // Loop through each input file
    for (int i = 1; i < argc; i++) {
        pid_t cpid = fork();

        if (cpid == -1) {
            perror("Fork failed");
            exit(1);
        }

        if (cpid == 0) {
            // This is the child process

            // Execute wordcount program with the current input file
            execl("./wordcount", "./wordcount", argv[i], NULL);

            // If execl() fails, print an error message
            perror("Exec failed");
            exit(2);
        }
    }

    // Wait for all child processes and check their exit codes
    for (int i = 1; i < argc; i++) {
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            int exitCode = WEXITSTATUS(status);

            if (exitCode == 0) {
                successCount++;
            } else if (exitCode == 1 || exitCode == 2) {
                failureCount++;
            }
        }
    }

    printf("%d files have been counted successfully!\n", successCount);
    printf("%d files did not exist or encountered an error!\n", failureCount);

    return 0;
}


//used this example to help build my code
/*for(i=1; i < argc; i++) {
   cpid = fork();
   if (cpid == -1) { ... }
   if (cpid == 0) {
     // this part is for child process
     // exec(...) the wordcount program with argv[i] as a parameter
     // if exec() is successful, the child process will be replaced by wordcount
     // BUT, if exec() fails, the child will continue executing statements here!
     // So, print an error message here and
     // return/exit with an exit code of 2, indicating that exec failed.
     // Otherwise (if you don't exit), what will happen?
   }
   // this part is for parent process ! But, DO NOT WAIT FOR A CHILD HERE !
}

// after the parent creates all children, it comes to this part
for( ; ; ) {
   // ! WAIT HERE FOR ALL CHILD PROCESSES and CHECK THEIR EXIT CODES !
}*/