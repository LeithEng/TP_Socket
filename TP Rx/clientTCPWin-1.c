#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
WSADATA WSAData; // variable initialisée par WSAStartup
WSAStartup(MAKEWORD(2,0), &WSAData); // indique la version utilisée, ici 2.0
//--- Début de l’étape n°1 :
SOCKET descripteurSocket;
int iResult;
// Crée un socket de communication
descripteurSocket = socket(AF_INET, SOCK_STREAM, 0); /* 0 indique que l’on utilisera le
protocole par défaut associé à SOCK_STREAM soit TCP */
if (descripteurSocket == INVALID_SOCKET)
{
printf("Erreur creation socket : %d\n", WSAGetLastError()); WSACleanup();
return 1;
}
//--Fin de l’étape n°1 !
printf("Socket créée avec succès !\n");
// On ferme la ressource avant de quitter
iResult = closesocket(descripteurSocket);
if (iResult == SOCKET_ERROR)
{
printf("Erreur fermeture socket : %d\n", WSAGetLastError()); WSACleanup();
return 1;
}
WSACleanup(); // termine l’utilisation
return 0;
}
