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



void init();
void clean();
SOCKET createSock();
struct sockaddr_in bindSock(unsigned long ip_address, int port, int sock);
void serverListen(int sock,struct sockaddr_in address , int max_con);
void clientConnect(int sock, struct sockaddr_in address);
int serverAccept(int sock, struct sockaddr_in*client_info);