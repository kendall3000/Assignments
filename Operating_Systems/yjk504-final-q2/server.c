#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct student_info {
    char ID[7];
    char name[20];
    double grade;
};

struct student_info DB[10] = {{"yjk504", "Kendall", 93.9}, /* Add more student data as needed */};

void handle_client(int connectionSocket) {
    char buffer[256];
    int n;

    printf("Server: Connection established with client\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        n = read(connectionSocket, buffer, sizeof(buffer) - 1);

        if (n <= 0) {
            perror("Error reading from socket");
            break;
        }

        printf("Server: Received message from client: %s\n", buffer);

        if (strcmp(buffer, "STOP") == 0) {
            printf("Server: Received STOP message. Closing connection.\n");
            break;
        } else if (strncmp(buffer, "GET_GRADE", 9) == 0) {
            char studentID[7];
            sscanf(buffer, "GET_GRADE %s", studentID);
            int found = 0;

            for (int i = 0; i < 10; ++i) {
                if (strcmp(DB[i].ID, studentID) == 0) {
                    char reply[256];
                    snprintf(reply, sizeof(reply), "Student: %s, Grade: %.2f", DB[i].name, DB[i].grade);
                    write(connectionSocket, reply, strlen(reply));
                    printf("Server: Sent reply to client: %s\n", reply);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                char errorMsg[] = "Error: Student not found";
                write(connectionSocket, errorMsg, strlen(errorMsg));
                printf("Server: Sent error message to client: %s\n", errorMsg);
            }
        } else if (strcmp(buffer, "GET_MAX") == 0) {
            double max_grade = DB[0].grade;

            for (int i = 1; i < 10; ++i) {
                if (DB[i].grade > max_grade) {
                    max_grade = DB[i].grade;
                }
            }

            char reply[256];
            snprintf(reply, sizeof(reply), "Max Grade: %.2f", max_grade);
            write(connectionSocket, reply, strlen(reply));
            printf("Server: Sent reply to client: %s\n", reply);
        } else if (strcmp(buffer, "GET_MIN") == 0) {
            double min_grade = DB[0].grade;

            for (int i = 1; i < 10; ++i) {
                if (DB[i].grade < min_grade) {
                    min_grade = DB[i].grade;
                }
            }

            char reply[256];
            snprintf(reply, sizeof(reply), "Min Grade: %.2f", min_grade);
            write(connectionSocket, reply, strlen(reply));
            printf("Server: Sent reply to client: %s\n", reply);
        } else if (strcmp(buffer, "GET_AVG") == 0) {
            double total = 0.0;

            for (int i = 0; i < 10; ++i) {
                total += DB[i].grade;
            }

            double avg_grade = total / 10;

            char reply[256];
            snprintf(reply, sizeof(reply), "Avg Grade: %.2f", avg_grade);
            write(connectionSocket, reply, strlen(reply));
            printf("Server: Sent reply to client: %s\n", reply);
        } else {
            char errorMsg[] = "Error: Invalid request";
            write(connectionSocket, errorMsg, strlen(errorMsg));
            printf("Server: Sent error message to client: %s\n", errorMsg);
        }
    }

    printf("Server: Closing connection with client\n");
    close(connectionSocket);
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int welcomeSocket, connectionSocket, port;
    socklen_t clientLength;
    struct sockaddr_in serverAddress, clientAddress;

    welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (welcomeSocket < 0) {
        perror("Error opening socket");
        exit(1);
    }

    port = atoi(argv[1]);

    memset((char *)&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(welcomeSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Error on binding");
        exit(1);
    }

    listen(welcomeSocket, 5);
    clientLength = sizeof(clientAddress);

    printf("Server: Waiting for incoming connections...\n");

    while (1) {
        connectionSocket = accept(welcomeSocket, (struct sockaddr *)&clientAddress, &clientLength);

        if (connectionSocket < 0) {
            perror("Error on accept");
            exit(1);
        }

        printf("Server: Accepted connection from client\n");

        if (fork() == 0) {
            close(welcomeSocket); // Child process doesn't need the welcome socket
            handle_client(connectionSocket);
        } else {
            close(connectionSocket); // Parent process doesn't need the connection socket
        }
    }

    return 0;
}
