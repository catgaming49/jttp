#include<stdio.h>
#include<stdlib.h>
#include<utils.h>
#include<string.h>

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

#define MAX_CONN 10


int curr_conn = 0;
int sockets[MAX_CONN];

void init() {
    #ifdef _WIN32
    WSADATA Data;
    if (WSAStartup(MAKEWORD(2, 2), &Data) != 0) {
        perror("WSAStartup failed");
        exit(EXIT_FAILURE);
    }
    #endif
}

void clean() {
    for (int i = 0; i < curr_conn; i++) {
#ifdef _WIN32
        closesocket(sockets[i]);
#elif __linux__
        close(sockets[i]);
#endif
    }
#ifdef _WIN32
    WSACleanup();
#endif
}


SOCKET createSock() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Failed to create socket");
        clean();
        exit(EXIT_FAILURE);
    }
    sockets[curr_conn] = sock;
    curr_conn = curr_conn + 1;
    return sock;
}

struct sockaddr_in bindSock(unsigned long ip_address, int port) {
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

int serverAccept(int sock, struct sockaddr_in*client_info) {
    socklen_t client_addr_size = sizeof(*client_info);
    int conn = accept(sock, (struct sockaddr*)client_info, &client_addr_size);
    if (conn == -1) {
        perror("Accepting connection failed");
        exit(EXIT_FAILURE);
    }
    return conn;
}

int serverRecv(int conn, char*buffer, int buffer_size) {
    int bytes_received = recv(conn, buffer, buffer_size, 0);
    if (bytes_received == -1) {
        perror("Receive failed");
        exit(EXIT_FAILURE);
    } else {
        buffer[bytes_received] = '\0';
    }
    return bytes_received;
}

void serverGetConnInfo(struct sockaddr *client_info) {
    char client_ip[INET6_ADDRSTRLEN]; // Buffer to hold the client's IP address string

    if (client_info->sa_family == AF_INET) {
        // IPv4 address
        struct sockaddr_in *ipv4_client_info = (struct sockaddr_in *)client_info;
        inet_ntop(AF_INET, &(ipv4_client_info->sin_addr), client_ip, INET6_ADDRSTRLEN);
        printf("IP Type: IPv4\n");
        printf("Client IP address: %s\n", client_ip);
        printf("Client Port number: %d\n", ntohs(ipv4_client_info->sin_port));
    } else if (client_info->sa_family == AF_INET6) {
        // IPv6 address
        struct sockaddr_in6 *ipv6_client_info = (struct sockaddr_in6 *)client_info;
        inet_ntop(AF_INET6, &(ipv6_client_info->sin6_addr), client_ip, INET6_ADDRSTRLEN);
        printf("IP Type: IPv6\n");
        printf("Client IP address: %s\n", client_ip);
        printf("Client Port number: %d\n", ntohs(ipv6_client_info->sin6_port));
    } else {
        printf("Unknown IP address type\n");
    }
}

void clientConnect(int sock, struct sockaddr_in address) {
    if (connect(sock, (struct sockaddr*)&address, sizeof(address)) == -1) {
    perror("Connection failed");
    clean(sock);
    exit(EXIT_FAILURE);
    }
}

void clientSend(int sock, char*data) {
    if (send(sock, data, strlen(data), 0) == -1) {
        perror("Send failed");
    }
}