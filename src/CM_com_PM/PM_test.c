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
    if (argc != 2)
    {
	printf("Usage:%s <ip of the server>\n", argv[0]);
	exit(0);
    }

    PORT_NUM t = P2C;
    PM2CM_Client_start(t, argv[1]);

    exit(0);
}
