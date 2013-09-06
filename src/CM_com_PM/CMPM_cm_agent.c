/*
** Author: Ming Liu
** Description: Implementation of cluster manager side in CM_com_PM.
*/
#include <stdio.h>

#include "CMPM_cm_agent.h"
#include "NetLayer.h"

#define TRUE 1

void do_action(int action)
{
    printf("Action %d\n", action);
}

int CM2PM_server_start(PORT_NUM serv_port)
{
    int listenfd = 0, connfd = 0;
    int action_label;

    listenfd = init_socket();
    if (listenfd < 0)
	return -1;

    if (init_server(serv_port, listenfd) < 0)
	return -1;

    while (TRUE)
    {
	connfd = accept_request(listenfd);
	if (read_data(connfd, &action_label, sizeof(action_label)) < 0)
	{
	    printf("Read Data Error\n");
	    return -1;
	}
	do_action(action_label);
	close(connfd);
    }

    //Success
    return 0;
}
