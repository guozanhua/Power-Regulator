/*
** Author: Ming Liu
** Description: Implementation of physical machine client side of CM_COM_PM.
*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include "CMPM_pm_agent.h"
#include "NetLayer.h"

#define BUFFER_SIZE 512
#define SMALL_BUFFER_SIZE 16
#define DEBUG

int PM2CM_Client_start(PORT_NUM cli_port, char *ip)
{
    int sockfd = 0, data = -1;

    sockfd = init_socket();
    if (sockfd < 0)
	return -1;
    if (connect_server(cli_port, sockfd, ip) < 0)
	return -1;
    if (write_data(sockfd, &data, sizeof(data)) < 0)
	return -1;

    return 0;
}

void PM_set_ip(PM* p)
{
    int fd;
    struct ifreq ifr;
    struct sockaddr_in *sa = NULL;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    strcpy(ifr.ifr_name, "eth0");
    if ( ioctl(fd, SIOCGIFADDR, &ifr) < 0 )
    {
	printf("PM_set_ip ioctl error!\n");
	return;
    }
    sa = (struct sockaddr_in *)(&ifr.ifr_addr);

    inet_ntop(AF_INET, &sa->sin_addr, p->IP, sizeof(p->IP));
}

void PM_set_frequency(PM* p)
{
    FILE *in;
    char buff[BUFFER_SIZE];
    char small_buff[SMALL_BUFFER_SIZE];

    int i = 0, j = 0, k = 0;

    memset(buff, 0x00, sizeof(buff));
    memset(small_buff, 0x00, sizeof(small_buff));
    in = popen("xenpm get-cpufreq-para 0","r");

    while (i < 8)
    {
	if (fgets(buff, BUFFER_SIZE, in) == NULL)
        {
	    printf("xenpm get-cpufreq-para isn't available!\n");
	    return;
        }
	i++;
    }

    fgets(buff, BUFFER_SIZE, in);

    for (i = 0; buff[i] != '\0'; i++)
    {
	if( !isdigit(buff[i]) )
	    buff[i] = ' ';
    }

    for (i = 0, j = 0, k = 0; buff[j] != '\n'; j++)
    {
	if ( isdigit(buff[j]) )
        {
	    while ( isdigit(buff[j]) )
	    {
	        small_buff[k++] = buff[j++];
	    }
	    small_buff[k] = '\0';
	    p->freq_list[i++] = atoi(small_buff);
	    k = 0;
	}
    }

    pclose(in);
}

void PM_set_Power(double *pow)
{
    FILE *in;
    char buff[BUFFER_SIZE];

    memset(buff, 0x00, sizeof(buff));
    in = popen("./wattsup -c 1 ttyUSB0 watts", "r");

    fgets(buff, BUFFER_SIZE, in);

    if ( !isdigit(buff[0]) )
    {
	printf("Wattsup Utility through ttyUSB0 isn't available!\n");
	*pow = 0.0;
	return;
    }
    sscanf(buff, "%lf", pow);

    pclose(in);
}

PM* PM_init()
{
    PM* server = NULL;

    server = (PM*)malloc(sizeof(PM));
    memset(server, 0x00, sizeof(PM));
    system("xenpm set-scaling-governor userspace");

    server->PM_ID = -1;                       //This will be reassigned via coordinator.
    server->active_core = NULL;
    PM_set_Power(&(server->idle_power));
    PM_set_Power(&(server->curr_power));
    PM_set_ip(server);
    PM_set_frequency(server);

#ifdef DEBUG
    {
	int i;

        printf("****************PM initialization*****************\n");
        printf("PM ID: %d\n", server->PM_ID);
        printf("PM IP: %s\n", server->IP);
        printf("PM Idle Power: %lf\n", server->idle_power);
        printf("PM Current Power: %lf\n", server->curr_power);

	for (i = 0; i < FREQUENCY_LIST_LENGTH; i++)
	{
	    if (server->freq_list[i] != 0)
		printf("%d ", server->freq_list[i]);
	}
	printf("\n");
        printf("**************Initialization OVER***************\n");
    }
#endif

    return server;
}

int PM_get_CORE_STATE(int core, PM *phymach)
{
    FILE *in;
    char buff[BUFFER_SIZE];
    char cmd[BUFFER_SIZE];
    char small_buff[BUFFER_SIZE];
    int i = 0, freq;

    memset(buff, 0x00, sizeof(buff));
    memset(cmd, 0x00, sizeof(cmd));
    memset(small_buff, 0x00, sizeof(small_buff));

    sprintf(small_buff, "%d", core);
    strcpy(cmd, "xenpm get-cpufreq-para ");
    strcat(cmd, small_buff); 

    in = popen(cmd, "r");

    while (i < 7)
    {
	if (fgets(buff, BUFFER_SIZE, in) == NULL)
        {
	    printf("xenpm get-cpufreq-para isn't available!\n");
	    return 0;
        }
	i++;
    }

    fgets(buff, BUFFER_SIZE, in);
    for (i = 0; buff[i] != '\0'; i++)
    {
	if( !isdigit(buff[i]) )
	    buff[i] = ' ';
    }

    sscanf(buff, "%d", &freq);

    for (i = 0; i < FREQUENCY_LIST_LENGTH; i++)
    {
	if (phymach->freq_list[i] == freq)
	    return i;
    }

    pclose(in);

    return 0;
}

void PM_add_VM(PM* phymach, int vm_id, int core_id)
{
    PM_CORE *p, *t , *q = NULL;
    VM *du, *dq, *dt;

    p = t = phymach->active_core;
    while (p != NULL)
    {
	t = p;
	if (p->CORE_ID == core_id)
	    break;
	p = p->next;
    }

    if (p == NULL)
    {
	du = (VM *)malloc(sizeof(VM));
	memset(du, 0x00, sizeof(VM));
	du->VM_ID = vm_id;
	du->next = NULL;

	q = (PM_CORE *)malloc(sizeof(PM_CORE));
	memset(q, 0x00, sizeof(PM_CORE));
	q->CORE_ID = core_id;
	q->active_VM = du;
	q->current_state = PM_get_CORE_STATE(core_id, phymach);
	q->next = NULL;

	if (phymach->active_core == NULL)
	    phymach->active_core = q;
	else
	    t->next = q;
    }
    else
    {
	dq = du = p->active_VM;

	while (du != NULL)
	{
	    dq = du;
	    if (du->VM_ID == vm_id)
		break;
	    du = du->next;
	}

	if (du == NULL)
	{
	    dt = (VM *)malloc(sizeof(VM));
	    memset(dt, 0x00, sizeof(VM));
	    dt->VM_ID = vm_id;
	    dt->next = NULL;

	    dq->next = dt;
	}
    }
}

int PM_obtainVM_info(PM* p)
{
    FILE *in;
    char buff[BUFFER_SIZE];
    char small_buff[SMALL_BUFFER_SIZE];
    int id, vcpu, cpu;
   
    memset(buff, 0x00, sizeof(buff)); 
    in = popen("xm vcpu-list", "r");

    fgets(buff, BUFFER_SIZE, in);

    while (fgets(buff, BUFFER_SIZE,in) != NULL)
    {
	sscanf(buff, "%s %d %d %d", small_buff, &id, &vcpu, &cpu);
	if (id == 0)
	    continue;
	PM_add_VM(p, id, cpu);
    }

    pclose(in);
    return 0;
}
