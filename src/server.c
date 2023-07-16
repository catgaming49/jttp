#include<stdio.h>
#include<stdlib.h>
#include<utils.h>

#ifdef _WIN32
#include<winsock2.h>
#include <ws2tcpip.h>
#elif __linux__
#include<sys/socket.h>
#include <arpa/inet.h>
#endif

#define BUFFER_SIZE 1024
#define BACKLOG_SIZE 1

int main() {
init();
int sock = createSock(); 
struct sockaddr_in address = bindSock(INADDR_ANY ,49572, sock);
serverListen(sock, address, BACKLOG_SIZE);

struct sockaddr_in client_info;

while (1) {
    int conn = serverAccept(sock, &client_info);
    char buffer[BUFFER_SIZE];
    serverRecv(conn, buffer, BUFFER_SIZE);
    serverGetConnInfo((struct sockaddr*)&client_info);
    closesocket(conn);
}

clean();
return 0;
}