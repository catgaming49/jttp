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
int conn = serverAccept(sock, &client_info);

printf("%s\n", inet_ntoa(client_info.sin_addr));

char buffer[BUFFER_SIZE];
size_t bytes_received = recv(conn, buffer, sizeof(buffer), 0);
if (bytes_received == -1) {
        perror("Receive failed");
} else {
    buffer[bytes_received] = '\0';
    printf("Received data from client: %s\n", buffer);
}

clean();
return 0;
}