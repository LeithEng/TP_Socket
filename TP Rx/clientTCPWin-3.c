#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#define PORT 5000
#define LG_MESSAGE 256

int main() {
    WSADATA WSAData;
    int iResult = WSAStartup(MAKEWORD(2, 0), &WSAData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    SOCKET descripteurSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (descripteurSocket == INVALID_SOCKET) {
        printf("Error creating socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    struct sockaddr_in pointDeRencontreDistant;
    pointDeRencontreDistant.sin_family = AF_INET;
    pointDeRencontreDistant.sin_addr.s_addr = inet_addr("192.168.0.176");
    pointDeRencontreDistant.sin_port = htons(PORT);

    iResult = connect(descripteurSocket, (SOCKADDR *)&pointDeRencontreDistant, sizeof(pointDeRencontreDistant));
    if (iResult == SOCKET_ERROR) {
        printf("Connection failed: %d\n", WSAGetLastError());
        closesocket(descripteurSocket);
        WSACleanup();
        return 1;
    }

    printf("Connection successful!\n");
    char messageEnvoi[LG_MESSAGE] = "Hello world!\n";
    int ecrits = send(descripteurSocket, messageEnvoi, strlen(messageEnvoi), 0);
    if (ecrits == SOCKET_ERROR) {
        printf("Error sending message: %d\n", WSAGetLastError());
        closesocket(descripteurSocket);
        WSACleanup();
        return 1;
    }

    printf("Message sent successfully (%d bytes)\n\n", ecrits);
    char messageRecu[LG_MESSAGE];
    int lus = recv(descripteurSocket, messageRecu, sizeof(messageRecu), 0);
    if (lus > 0) {
        printf("Message received from server: %s (%d bytes)\n\n", messageRecu, lus);
    } else if (lus == 0) {
        printf("The server has closed the connection!\n");
    } else {
        printf("Error receiving data: %d\n", WSAGetLastError());
    }

    closesocket(descripteurSocket);
    WSACleanup();
    return 0;
}
