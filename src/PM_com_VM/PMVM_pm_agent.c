/*
** Author: Ming Liu
** Description: Implementation of physical machine (to) virtual machine agent.
*/
#include <string.h>
#include <stdio.h>
#include "PMVM_pm_agent.h"

#define DEBUG

int pmvm_pm_listen()
{
    int listenfd = 0, connfd = 0, domID;
    PORT_NUM service = V2P;
    char recvIP[IP_BUFFER_SIZE];

    memset(recvIP, 0x00, sizeof(recvIP));
    listenfd = init_socket();
    if (listenfd < 0)
	return -1;
    if (init_server(service, listenfd) < 0)
	return -1;

    while (1)
    {
	if ((connfd = accept_request(listenfd)) < 0)
	    return -1;

        if (read_data(connfd, &domID, sizeof(domID)))
	    return -1;
	if (read_data(connfd, recvIP, sizeof(recvIP)))
	    return -1;

#ifdef DEBUG
	printf("*********New Comer**********\n");
	printf("Listen Thread->get ID: %d\n", domID);
	printf("Listen Thread->get IP: %s\n", recvIP);
	printf("****************************\n");
#endif

        /*TODO: Add this VM into PM's list */

	close(connfd);
    }

    return 0;
}

double pmvm_pm_perf(char *ip)
{
    int sockfd = 0;
    ACTION a = PM_ASK_PERF;
    PORT_NUM service = P2V;
    double perf = 0.0;

    sockfd = init_socket();
    if (sockfd < 0)
	return 0.0;
    if (connect_server(service, sockfd, ip) < 0)
	return 0.0;

    if ( write_data(sockfd, &a, sizeof(a)) )
	return 0.0;
    if ( read_data(sockfd, &perf, sizeof(perf)) )
	return 0.0;

    return perf;
}

int pmvm_pm_livecheck(char *ip)
{
    int sockfd = 0, ret = -1;
    ACTION a = PM_CHECK_VM;
    PORT_NUM service = P2V;

    sockfd = init_socket();
    if (sockfd < 0)
	return -1;
    if (connect_server(service, sockfd, ip) < 0)
	return -1;

    if ( write_data(sockfd, &a, sizeof(a)) )
	return -1;
    if ( read_data(sockfd, &ret, sizeof(ret)) )
	return -1;

    if ( !ret )
	return 0;
    else
    {
	/* TODO: Remove VM from PM's list */
	return -1;
    }
}
