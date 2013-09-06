/*
** Author: Ming Liu
** Description: Test PM side implementation of PM_COM_VM.
*/
#include <stdlib.h>
#include <stdio.h>
#include "PMVM_pm_agent.h"

int main(int argc, char **argv)
{
    int i;

    if ( argc != 2 )
    {
	printf("Usage: %s <ip>\n", argv[0]);
	exit(0);
    }

    pmvm_pm_listen();

    for (i = 0; i < 10; i++)
    {
        printf("Performance %lf\n", pmvm_pm_perf(argv[1]));
        printf("Live %d\n", pmvm_pm_livecheck(argv[1]));
    }
    exit(0);
}
