/*
** Author: Ming Liu
** Description: Test implementation of physical machine.
*/
#include <stdlib.h>
#include <stdio.h>
#include "NetLayer.h"
#include "PM_client.h"

int main(int argc, char **argv)
{
    PORT_NUM t = P2C;
    PM* local_pm = NULL;

    if (argc != 2)
    {
	printf("Usage:%s <ip of the server>\n", argv[0]);
	exit(0);
    }

    if ( (local_pm = PM_init()) == NULL )
    {
	printf("PM initialization error!\n");
	exit(0);
    }

    if ( PM2CM_Client_start(t, argv[1]) )
    {
	printf("PM2CM Client start error!\n");
	exit(0);
    }

    exit(0);
}
