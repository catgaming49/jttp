#include<stdio.h>
#include<stdlib.h>
#include<utils.h>

#ifdef _WIN32
#include<winsock2.h>
#include <ws2tcpip.h>
#elif __linux__
#include<sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
typedef int SOCKET;
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif

int main() {
init();
int sock = createSock(); 
struct sockaddr_in address = bindSock(inet_addr("127.0.0.1"), 49572);
clientConnect(sock, address);
clientSend(sock, "Hello, world!");

clean();
return 0;
}