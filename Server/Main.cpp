#include "src/Main_Reactor.h"
#include "src/Connect.h"
#include "src/MemPool.h"
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void Connect(void *arg)
{
	CConnect *pConnect = (CConnect*)arg;
	printf("new client %d\n", pConnect->GetFd());
}

void Close(void* arg)
{
	CConnect *pConnect = (CConnect*)arg;
	printf("connect %d close\n", pConnect->GetFd());
}

void signal_handler(int signo)
{
	printf("caught signo %d\n", signo);
	exit(0);
//	mr.SetExit();
}

int main()
{  
	signal(SIGINT, signal_handler);
	CMain_Reactor mr(NULL, NULL, Connect, Close);
	mr.Start();
}
