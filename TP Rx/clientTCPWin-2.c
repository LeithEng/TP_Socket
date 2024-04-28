#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#define PORT 5000
int main()
{
WSADATA WSAData; // variable initialis�e par WSAStartup
WSAStartup(MAKEWORD(2,0), &WSAData); // indique la version utilis�e, ici 2.0
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
//--- D�but de l��tape n�2 :
struct sockaddr_in pointDeRencontreDistant; // ou SOCKADDR_IN pointDeRencontreDistant;
// Renseigne la structure sockaddr_in avec les informations du serveur distant
pointDeRencontreDistant.sin_family = AF_INET;
// On choisit l�adresse IPv4 du serveur
pointDeRencontreDistant.sin_addr.s_addr = inet_addr("192.168.0.176"); // � modifier selon ses
//besoins
// On choisit le num�ro de port d��coute du serveur
pointDeRencontreDistant.sin_port = htons(PORT); // = 5000
// D�bute la connexion vers le processus serveur distant
iResult = connect(descripteurSocket, (SOCKADDR *)&pointDeRencontreDistant, sizeof(
pointDeRencontreDistant));
if (iResult == SOCKET_ERROR)
{
printf("Erreur connexion socket : %d\n", WSAGetLastError());
iResult = closesocket(descripteurSocket); // On ferme la ressource avant de quitter
if (iResult == SOCKET_ERROR)
{
printf("Erreur fermeture socket : %d\n", WSAGetLastError());
}
WSACleanup();
return 1; // On sort en indiquant un code erreur
}
//--- Fin de l��tape n�2 !
printf("Connexion au serveur r�ussie avec succ�s !\n");
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
