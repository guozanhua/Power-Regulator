/*
** Author: Ming Liu
** Description: This is the header file of network layer API.
*/
#ifndef _NETLAYER_H
#define _NETLAYER_H
#include <unistd.h>

#define MAXSLEEP 128   //The maximum sleep time for exponential backoff algorithm
#define MAX_CONNECT 64 //The maximun connection number for each service

typedef enum{
    P2C = 2000,
    C2P = 2001,
    P2V = 2002,
    V2P = 2003,
    C2C = 2004
}PORT_NUM;

/* General Methods */
int init_socket();                     //Initialize one IPv4 SOCK_STREAM socket for communication
		                       //Error return -1; Success return socket descriptor
int read_data(int sockfd, void *data, size_t size);                    //Read data from socket into data pointer, portable
								       //Error return -1; Success return 0
int write_data(int sockfd, const void *data, size_t size);             //Write data from data pointer into socket, portable
								       //Error return -1, Success return 0
/* Client Methods */
int connect_server(PORT_NUM serv_port, int sockfd, char *serverIP);    //Connect to the server specified by serverIP
				                                       //This method implements exponential backoff algorithm
				                                       //Error return -1; Success return 0 
/* Server Methods */
int init_server(PORT_NUM service, int sockfd);     //Set up one server based on local address
						   //Error return -1; Success return 0
int accept_request(int listenfd);                  //Accept request from anonymous clients
						   //Error return -1; Success return socket descriptor

#endif
