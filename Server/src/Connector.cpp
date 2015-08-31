#include "Connector.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

CConnector::CConnector()
{

}

CConnector::~CConnector()
{

}


//this function should be called in alone thread, because connect may be blocked
int CConnector::Connect_Host(const char * strip,unsigned short port)
{
	int socket_fd = -1;
	struct 	sockaddr_in addr;
	if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("sock fail\n");

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(strip);

	if(connect(socket_fd, (struct sockaddr*)&addr, sizeof(addr)))
	{  
		printf("connect %s\n", strerror(errno));
		return -1;
	}
	else
		return socket_fd;
}