/*
** Author: Ming Liu
** Description: Implementation of physical machine client side.
*/
#include "PM_client.h"
#include "NetLayer.h"

int PM2CM_Client_start(PORT_NUM cli_port, char *ip)
{
    int sockfd = 0, data = -1;

    sockfd = init_socket();
    if (sockfd < 0)
	return -1;
    if (connect_server(cli_port, sockfd, ip) < 0)
	return -1;
    if (write_data(sockfd, &data, sizeof(data)) < 0)
	return -1;

    return 0;
}
