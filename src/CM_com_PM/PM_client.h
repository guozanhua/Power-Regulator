/*
** Author: Ming Liu
** Description: Header file of physical machine client side.
*/
#ifndef _PM_CLIENT_H
#define _PM_CLIENT_H
#include "NetLayer.h"

#define IP_BUFFER_SIZE 64
#define FREQUENCY_LIST_LENGTH 16
#define STATE_LENGTH 16

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
    int freq_list[FREQUENCY_LIST_LENGTH];   //Frequency list length of this physical machine
    PM_CORE *active_core;                   //Active core list of this physical machine
}PM;

PM* PM_init();                              		     //PM Client Side Initialization
							     //Error return NULL; Success return the pointer
int PM2CM_Client_start(PORT_NUM cli_port, char *ip);         //Start PM_TO_CM Client side service
							     //Error return -1; Success return 0
int PM_obtainVM_info(PM *p);                                 //Obtain VM information
							     //Error return -1; Success return 0
 
#endif
