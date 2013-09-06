/*
** Author: Ming Liu
** Description: Implementation of physical machine (to) virtual machine agent.
*/
#include <stdio.h>
#include <string.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include "PMVM_vm_agent.h"

int pmvm_vm_init(int domID, char *ip)
{
    int sockfd, fd;
    PORT_NUM service = V2P;
    char sendIP[IP_BUFFER_SIZE];
    struct ifreq ifr;
    struct sockaddr_in *sa = NULL;

    memset(sendIP, 0x00, sizeof(sendIP));
    fd = socket(AF_INET, SOCK_STREAM, 0);
    strcpy(ifr.ifr_name, "eth0");
    if (ioctl(fd, SIOCGIFADDR, &ifr) < 0)
	return -1;
    sa = (struct sockaddr_in *)(&ifr.ifr_addr);
    inet_ntop(AF_INET, &sa->sin_addr, sendIP, sizeof(sendIP));

    sockfd = init_socket();
    if (sockfd < 0)
	return -1;

    if (connect_server(service, sockfd, ip) < 0)
	return -1;

    if (write_data(sockfd, &domID, sizeof(domID)))
	return -1;

    if (write_data(sockfd, sendIP, sizeof(sendIP)))
	return -1;

    return 0;
}

int pmvm_vm_monitor()
{
    int listenfd = 0, connfd = 0, action = -1, livecheck = 0;
    PORT_NUM service = P2V;
    double perf = 0.0;

    listenfd = init_socket();
    if (listenfd < 0)
	return -1;

    if (init_server(service, listenfd) < 0)
	return -1;

    while (1)
    {
	connfd = accept_request(listenfd);
	if (connfd < 0)
	    ;           //do nothing

        if (read_data(connfd, &action, sizeof(action)))
	    ;           //do nothing

        switch(action){
	case PM_ASK_PERF:
	    /* TODO: Ask Intel Tools to get IPC */
	    /* perf = get_IPC(); */
	    perf = 0.9;
	    if ( write_data(connfd, &perf, sizeof(perf)) )
		;      //do nothing
	    break;
        case PM_CHECK_VM:
	    livecheck = 0;
	    if ( write_data(connfd, &livecheck, sizeof(livecheck)) )
		;     //do nothing
	    break;
	default:
	    printf("No action\n");
	    if ( write_data(connfd, &perf, sizeof(perf)) )
		;      //do nothing
	    break;
	}
    }

    return 0;
}
