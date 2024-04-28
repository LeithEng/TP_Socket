#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
WSADATA WSAData; // variable initialis�e par WSAStartup
WSAStartup(MAKEWORD(2,0), &WSAData); // indique la version utilis�e, ici 2.0
//--- D�but de l��tape n�1 :
SOCKET descripteurSocket;
int iResult;
// Cr�e un socket de communication
descripteurSocket = socket(AF_INET, SOCK_STREAM, 0); /* 0 indique que l�on utilisera le
protocole par d�faut associ� � SOCK_STREAM soit TCP */
if (descripteurSocket == INVALID_SOCKET)
{
printf("Erreur creation socket : %d\n", WSAGetLastError()); WSACleanup();
return 1;
}
//--Fin de l��tape n�1 !
printf("Socket cr��e avec succ�s !\n");
// On ferme la ressource avant de quitter
iResult = closesocket(descripteurSocket);
if (iResult == SOCKET_ERROR)
{
printf("Erreur fermeture socket : %d\n", WSAGetLastError()); WSACleanup();
return 1;
}
WSACleanup(); // termine l�utilisation
return 0;
}
