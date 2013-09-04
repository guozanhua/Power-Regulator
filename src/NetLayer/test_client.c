/*
** Author: Ming Liu
** Description: Client Side Test.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "NetLayer.h"

#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
    int sockfd = 0, n = 0, length = 0;
    char recvBuff[BUFFER_SIZE];
    PORT_NUM t = P2C;

    if (argc != 2)
    {
	printf("\nUsage: %s <ip of server>\n", argv[0]);
	exit(0);
    }

    memset(recvBuff, 0x00, sizeof(recvBuff));
    sockfd = init_socket();
    if (sockfd < 0)
	exit(0);
    if (connect_server(t, sockfd, argv[1]) < 0)
	exit(0);

    if ( read_data(sockfd, &length, sizeof(length)) )
	exit(0);
    if ( read_data(sockfd, recvBuff, length) )
	exit(0);

    printf("%s\n", recvBuff);

    exit(0);
}
