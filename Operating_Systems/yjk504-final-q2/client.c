#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_host> <server_port>\n", argv[0]);
        exit(1);
    }

    int clientSocket, port;
    struct sockaddr_in serverAddress;
    char buffer[256];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0) {
        perror("Error opening socket");
        exit(1);
    }

    port = atoi(argv[2]);

    memset((char *)&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddress.sin_port = htons(port);

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }

    printf("Client: Connected to the server\n");

    while (1) {
        printf("Options:\n1. Get GRADE for a student\n2. Get Min, Max, Avg\n3. Stop\n");
        printf("Enter option: ");

        int option;
        scanf("%d", &option);

        if (option == 1) {
            char studentID[7];
            printf("Enter student ID: ");
            scanf("%s", studentID);

            snprintf(buffer, sizeof(buffer), "GET_GRADE %s", studentID);
        } else if (option == 2) {
            printf("Options:\n1. Get Min\n2. Get Max\n3. Get Avg\n");
            printf("Enter option: ");

            int subOption;
            scanf("%d", &subOption);

            if (subOption == 1) {
                strcpy(buffer, "GET_MIN");
            } else if (subOption == 2) {
                strcpy(buffer, "GET_MAX");
            } else if (subOption == 3) {
                strcpy(buffer, "GET_AVG");
            } else {
                fprintf(stderr, "Invalid option\n");
                continue;
            }
        } else if (option == 3) {
            strcpy(buffer, "STOP");
            write(clientSocket, buffer, strlen(buffer) + 1);
            printf("Client: Sent STOP message to the server\n");
            break;
        } else {
            fprintf(stderr, "Invalid option\n");
            continue;
        }

        write(clientSocket, buffer, strlen(buffer) + 1);
        printf("Client: Sent message to the server: %s\n", buffer);

        memset(buffer, 0, sizeof(buffer));
        read(clientSocket, buffer, sizeof(buffer) - 1);
        printf("Client: Received response from the server: %s\n", buffer);
    }

    printf("Client: Closing connection\n");

    close(clientSocket);

    return 0;
}
