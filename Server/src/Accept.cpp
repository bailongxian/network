#include "Accept.h"
#include "Main_Reactor.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define handle_err(msg) \
	do{perror(msg); exit(EXIT_FAILURE);}while(0);

	
CAcceptor::CAcceptor(const char* host, uint16_t port)
	:strHost_(host), nport_(port)
{  

}

CAcceptor::~CAcceptor()
{  
	close(listenfd_);
}

int CAcceptor::Init_Accept()
{
	listenfd_ = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd_ < 0)
		handle_err("socket");
	printf("listenfd_ %d\n", listenfd_);
	const int opt = 1;
	setsockopt(listenfd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(nport_);
	int ret = bind(listenfd_, (struct sockaddr*)&addr, sizeof(addr));
	if(ret < 0)
	{  
		close(listenfd_);
		handle_err("bind");
	}
	ret = listen(listenfd_, SOMAXCONN);
	if (ret < 0)
	{
		close(listenfd_);
		handle_err("listen");
	}
	return 0;
}

int CAcceptor::Start_Accept()
{  
	struct sockaddr_in cli;
	socklen_t cli_len = sizeof(cli);
	bzero(&cli, sizeof(cli));
	int confd = accept4(listenfd_, (struct sockaddr*)&cli, &cli_len, SOCK_NONBLOCK|SOCK_CLOEXEC);
	if(confd < 0)
	{  
		// error handle 
		printf("accept4 fail %d,  %s\n", cli_len, strerror(errno));
	}
	return confd;		
}

int CAcceptor::Exit_Accept()
{  
	return 0;
}




