/*
** Author: Ming Liu
** Description: Implement the functions of client side in NetLayer.h
*/
#include "NetLayer.h"

int connect_server(PORT_NUM serv_port, int sockfd, char *serverIP)
{
    int nsec;
    struct sockaddr_in serv_addr;
    
    memset(&serv_addr, 0x00, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(serv_port);

    if (inet_pton(AF_INET, serverIP, &serv_addr.sin_addr) <= 0)
    {
	printf("\nError: inet_pton error occured\n");
	return -1;
    }

    /*
    ** Try to connect with exponential backoff algorithm
    */
    for (nsec = 1; nsec < MAXSLEEP; nsec <<=1)
    {
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0)
	    return 0;
        
        if (nsec <= MAXSLEEP/2)
	    sleep(nsec);
    }

    return -1;
}
