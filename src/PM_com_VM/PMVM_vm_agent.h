/*
** Author: Ming Liu
** Description: Header file of virtual machine (to) physical machine agent.
*/
#ifndef _PMVM_VM_AGENT_H
#define _PMVM_VM_AGENT_H
#include "NetLayer.h"
#include "PMVM_share.h"

int pmvm_vm_init(int domID, char *ip);			//Initialize VM and send to PM	
							//Error return -1; Success return 0
int pmvm_vm_monitor();					//Monitor service and conduct related action
							//Error return -1; Success return 0

#endif
