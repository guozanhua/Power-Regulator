/*
** Author: Ming Liu
** Description: Test implmenetation of Cluster Manager (CM).
*/
#include <stdlib.h>
#include <stdio.h>
#include "CMPM_cm_agent.h"
#include "NetLayer.h"

int main(int argc, char **argv)
{
    PORT_NUM t = P2C;

    CM2PM_server_start(t);

    exit(0);
}
