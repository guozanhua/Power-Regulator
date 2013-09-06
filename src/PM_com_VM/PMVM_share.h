/*
** Author: Ming Liu
** Description: Header file of physical and virtual machine shared data type.
*/
#ifndef _PMVM_SHARE_H
#define _PMVM_SHARE_H

#define IP_BUFFER_SIZE 64
#define STATE_LENGTH 16
#define FREQUENCY_LIST_LENGTH 16

typedef struct virtual_machine{
    int VM_ID;                              //ID of this virtual machine
    char IP[IP_BUFFER_SIZE];                //IP of this virtual machine
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

#endif

