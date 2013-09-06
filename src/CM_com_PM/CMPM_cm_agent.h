/*
** Author: Ming Liu
** Description: The header file of cluster manager side in CM_com_PM.
*/
#ifndef _CMPM_CM_AGENT_H
#define _CMPM_CM_AGENT_H
#include "NetLayer.h"

#define IP_BUFFER_SIZE 64
#define STATE_LENGTH   16

typedef struct virtual_machine{
    int VM_ID;                              //ID of this virtual machine
    double perf_state[STATE_LENGTH];        //Performance among different frequency of this virtual machine

    struct virtual_machine *next;
}VM;

typedef struct core{
    int CORE_ID;                            //ID of this physical core
    VM *active_VM;                          //Active VMs on this physical core
    int current_state;                      //Current performance state of this physical core

    struct core *next;
}PM_CORE;

typedef struct physical_machine{
    int PM_ID;                              //ID of this physical machine
    char IP[IP_BUFFER_SIZE];                //IP of this physical machine
    double idle_power;                      //Idle Power of this physical machine
    double curr_power;                      //Current Power of this physical machine
    PM_CORE *active_core;                   //Active core list of this physical machine

    struct physical_machine *next;          
}PM;

int CM2PM_server_start(PORT_NUM serv_port);       //Start cluster manager server
					       //Error return -1; Success return 0

#endif
