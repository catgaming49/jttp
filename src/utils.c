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

#define MAX_CONN 10


int curr_conn = 0;
int sockets[MAX_CONN];

void init() {
    WSADATA Data;
    if (WSAStartup(MAKEWORD(2, 2), &Data) != 0) {
        perror("WSAStartup failed");
        exit(EXIT_FAILURE);
    }
}

void clean() {
    for (int i = 0;i < curr_conn;i++) {
        closesocket(sockets[i]);
    }
    WSACleanup();
}

SOCKET createSock() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Failed to create socket");
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    sockets[curr_conn] = sock;
    curr_conn = curr_conn + 1;
    return sock;
}

struct sockaddr_in bindSock(unsigned long ip_address, int port, int sock) {
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = ip_address;
    address.sin_port = htons(port);
    return address;
}

void serverListen(int sock,struct sockaddr_in address , int max_con) {
    
    if (bind(sock, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
    perror("Binding failed");
    exit(EXIT_FAILURE);
    }
    if (listen(sock, max_con) == -1) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }
}

void clientConnect(int sock, struct sockaddr_in address) {
    if (connect(sock, (struct sockaddr*)&address, sizeof(address)) == -1) {
    perror("Connection failed");
    clean(sock);
    exit(EXIT_FAILURE);
    }
}

int serverAccept(int sock, struct sockaddr_in*client_info) {
    socklen_t client_addr_size = sizeof(*client_info);
    int conn = accept(sock, (struct sockaddr*)client_info, &client_addr_size);
    if (conn == -1) {
        perror("Accepting connection failed");
        exit(EXIT_FAILURE);
    }
    return conn;
}