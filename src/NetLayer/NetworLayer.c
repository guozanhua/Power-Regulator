/*
** Author: Ming Liu
** Description: Implement all functions of NetLayer.h
*/
#include "NetLayer.h"

int init_socket()
{
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
	printf("\n");
	return -1;
    }

    return sockfd;
}
