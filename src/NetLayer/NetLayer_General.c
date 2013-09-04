/*
** Author: Ming Liu
** Description: Implement the functions of general methods in NetLayer.h
*/
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include "NetLayer.h"

int init_socket()
{
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
	printf("\nError: Could not create socket\n");
	return -1;
    }

    return sockfd;
}

int read_data(int sockfd, void *data, size_t size)
{
    size_t offset = 0;
    ssize_t len;

    while (offset < size)
    {
	len = read(sockfd, (char *)data + offset, size-offset);
	if ((len == -1) && (errno == EINTR))
	    continue;
	if (len == 0)
	    errno = 0;
        if (len <= 0)
	    return -1;
	offset += len;
    }

    return 0;
}

int write_data(int sockfd, const void *data, size_t size)
{
    size_t offset = 0;
    ssize_t len;

    while (offset < size)
    {
	len = write(sockfd, (const char *)data + offset, size - offset);
        if ( (len == -1) && (errno == EINTR) )
	    continue;
        if (len <= 0)
	    return -1;

	offset += len;
    }

    return 0;
}
