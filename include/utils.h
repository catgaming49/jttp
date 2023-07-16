#pragma once
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


/**
 * @brief Initialise socket handling
 * 
 */
void init();

/**
 * @brief Clean up sockets
 * 
 */
void clean();


/**
 * @brief Create a Socket
 * 
 * @return SOCKET 
 */
SOCKET createSock();

/**
 * @brief Binds the socket to the given values
 * 
 * @param ip_address 
 * @param port 
 * @param sock 
 * @return struct sockaddr_in 
 */
struct sockaddr_in bindSock(unsigned long ip_address, int port, int sock);

void clientConnect(int sock, struct sockaddr_in address);

void clientSend(int sock, char*data);

void serverListen(int sock,struct sockaddr_in address , int max_con);

int serverAccept(int sock, struct sockaddr_in*client_info);

size_t serverRecv(int conn, char*buffer, int buffer_size);

void serverGetConnInfo(struct sockaddr *client_info);

