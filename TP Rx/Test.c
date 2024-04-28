#include <winsock2.h>
// pour Visual Studio sinon ajouter -lws2_32
#pragma comment(lib, "ws2_32.lib")
int main()
{
WSADATA WSAData; // variable initialisée par WSAStartup
WSAStartup(MAKEWORD(2,0), &WSAData); // indique la version utilisée, ici 2.0
/* ... */
WSACleanup(); // termine l’utilisation
return 0;
}
