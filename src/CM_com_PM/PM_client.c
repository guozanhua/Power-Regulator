/*
** Author: Ming Liu
** Description: Implementation of physical machine client side.
*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include "PM_client.h"
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

    server->PM_ID = -1;                       //This will be reassigned via coordinator.
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
    }
#endif

    return server;
}
