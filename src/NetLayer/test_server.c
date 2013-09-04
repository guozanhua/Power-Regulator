/*
** Author: Ming Liu
** Description: Server Side Test.
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "NetLayer.h"

#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
    int listenfd = 0, connfd = 0, length = 0;
    PORT_NUM t = P2C;
    time_t ticks;
    char sendBuff[BUFFER_SIZE];

    memset(sendBuff, 0x00, sizeof(sendBuff));
    listenfd = init_socket();
    if (init_server(t, listenfd) < 0)
	exit(0);

    while (1)
    {
    	connfd = accept_request(listenfd);
    	if (connfd < 0)
	    exit(0);

	ticks = time(NULL);
	snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        length = strlen(sendBuff) + 1;

	if (write_data(connfd, &length, sizeof(length)))
	    exit(0);
	if (write_data(connfd, sendBuff, length))
	    exit(0);

        close(connfd);
	sleep(1);
    }
    
    exit(0);
}
