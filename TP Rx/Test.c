#include <winsock2.h>
// pour Visual Studio sinon ajouter -lws2_32
#pragma comment(lib, "ws2_32.lib")
int main()
{
WSADATA WSAData; // variable initialis�e par WSAStartup
WSAStartup(MAKEWORD(2,0), &WSAData); // indique la version utilis�e, ici 2.0
/* ... */
WSACleanup(); // termine l�utilisation
return 0;
}
