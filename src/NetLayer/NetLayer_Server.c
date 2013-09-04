/*
** Author: Ming Liu
** Description: Implement the functions of server side in NetLayer.h
*/
#include "NetLayer.h"

int init_server(PORT_NUM service, int sockfd)
{
    struct sockaddr_in serv_addr;

    memset(&serv_addr, 0x00, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(service);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
	printf("\nError: Bind socket error\n");
	return -1;
    }

    if (listen(sockfd, MAX_CONNECT) < 0)
    {
	printf("\nError: Listen socket error\n");
	return -1;
    }

    return 0;
}

int accept_request(int listenfd)
{
    int connfd;

    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

    return connfd;
}
