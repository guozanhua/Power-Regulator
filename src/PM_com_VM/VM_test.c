/*
** Author: Ming Liu
** Description: Test VM_to_PM side implementation.
*/
#include <stdlib.h>
#include <stdio.h>
#include "PMVM_vm_agent.h"

int main(int argc, char **argv)
{
    if ( argc != 3 )
    {
	printf("Usage: %s <domain ID> <ip>\n", argv[0]);
	exit(0);
    }

    pmvm_vm_init(atoi(argv[1]), argv[2]);
    pmvm_vm_monitor();

    exit(0);
}
