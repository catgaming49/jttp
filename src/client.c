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

int main() {
init();
int sock = createSock(); 
struct sockaddr_in address = bindSock(inet_addr("127.0.0.1"), 49572, sock);
clientConnect(sock, address);

char message[] = "Hello, world!";
if (send(sock, message, sizeof(message), 0) == -1) {
    perror("Send failed");
}

clean();
return 0;
}