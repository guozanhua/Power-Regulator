/*
** Author: Ming Liu
** Description: Header file of physical machine (to) virtual machine agent. 
*/
#ifndef _PMVM_PM_AGENT_H
#define _PMVM_PM_AGENT_H
#include "NetLayer.h"
#include "PMVM_share.h"

int pmvm_pm_listen();        		     //Listen on the port to get new comer(VM)
					     //Error Return -1; Success Return 0
double pmvm_pm_perf(char *ip);               //Obtain performance via ip address
					     //Return performance 
int pmvm_pm_livecheck(char *ip);             //Check VM is live or not
					     //Error Return -1; Success Return 0
#endif
