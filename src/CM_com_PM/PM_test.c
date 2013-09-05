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
    PM_CORE* p;
    VM*      q;

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

    if ( PM_obtainVM_info(local_pm) )
    {
	printf("PM obtain VM information error!\n");
	exit(0);
    }

    {
	// For Test
	p = local_pm->active_core;
	while (p != NULL)
	{
	    printf("======>");
	    printf("CORE ID: %d\n", p->CORE_ID); 
	    printf("CORE STATE: %d\n", p->current_state);
	    q = p->active_VM;
	    printf("VM ID: ");
	    while (q != NULL)
	    {
		printf("%d ", q->VM_ID);
		q = q->next;
	    }
	    printf("\n");

	    p = p->next;
	}
    }


    if ( PM2CM_Client_start(t, argv[1]) )
    {
	printf("PM2CM Client start error!\n");
	exit(0);
    }

    exit(0);
}
