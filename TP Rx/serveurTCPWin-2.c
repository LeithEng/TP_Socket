#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* pour sleep */
#define PORT 5000
int main()
{
WSADATA WSAData; // variable initialis�e par WSAStartup
WSAStartup(MAKEWORD(2,0), &WSAData); // indique la version utilis�e, ici 2.0
SOCKET socketEcoute;
int iResult;
// Cr�e un socket de communication
socketEcoute = socket(AF_INET, SOCK_STREAM, 0); /* 0 indique que l�on utilisera le
protocole par d�faut associ� � SOCK_STREAM soit TCP */
if (socketEcoute == INVALID_SOCKET)
{
printf("Erreur creation socket : %d\n", WSAGetLastError()); WSACleanup();
return 1;
}
// On pr�pare l�adresse d�attachement locale
struct sockaddr_in pointDeRencontreLocal; // ou SOCKADDR_IN pointDeRencontreLocal;
// Renseigne la structure sockaddr_in avec les informations locales du serveur
pointDeRencontreLocal.sin_family = AF_INET;
pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY); // toutes les interfaces locales disponibles
// On choisit le num�ro de port d��coute du serveur
pointDeRencontreLocal.sin_port = htons(PORT); // = 5000
iResult = bind(socketEcoute, (SOCKADDR *)&pointDeRencontreLocal, sizeof(pointDeRencontreLocal));
if (iResult == SOCKET_ERROR)
{
printf("Erreur bind socket : %d\n", WSAGetLastError());
closesocket(socketEcoute);
WSACleanup();
return 1;
}
printf("Socket attach�e avec succ�s !\n");
//--- D�but de l��tape n�6 :
// On fixe la taille de la file d�attente (pour les demandes de connexion non encore trait�es)
if (listen(socketEcoute, SOMAXCONN) == SOCKET_ERROR)
{
printf("Erreur listen socket : %d\n", WSAGetLastError());
}
//--- Fin de l��tape n�6 !
printf("Socket plac�e en �coute passive ...\n");
// On ferme la ressource avant de quitter
iResult = closesocket(socketEcoute);
if (iResult == SOCKET_ERROR)
{
printf("Erreur fermeture socket : %d\n", WSAGetLastError());
WSACleanup();
return 1;
}
WSACleanup(); // termine l�utilisation
return 0;
}
