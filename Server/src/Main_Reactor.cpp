#include "Main_Reactor.h"
#include "EventLoop.h"
#include "Accept.h"
#include "Message.h"
#include "Connector.h"

#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <time.h>

void* Accept_thread(void * arg);
void* Connect_Thread(void* arg);
int g_count = 0;
unsigned long long  g_tick = 2;

unsigned long long TimeGetTime()
{
	unsigned long long time = 0;
	struct timespec on;
	if((clock_gettime(CLOCK_MONOTONIC, &on)) != -1)
		time = on.tv_sec * 1000 + on.tv_nsec / 1000;
	return time;
}



CMain_Reactor::CMain_Reactor(ReadWriteCallBack Readcb, ReadWriteCallBack Writecb, ConnectCallBack connectcb, CloseCallBack closecb)
:nCpuNum_(sysconf(_SC_NPROCESSORS_CONF)),
	Acceptor_(new CAcceptor(NULL, 8999)),
	Readcb_(Readcb),
	Writecb_(Writecb),
	Connectcb_(connectcb),
	Closecb_(closecb)
	
{ 
	assert(nCpuNum_);
	printf("CPU NUM %d\n", nCpuNum_);
	signal(SIGPIPE, SIG_IGN);
	LoopList_ = (CEventLoop**)malloc(sizeof(CEventLoop*) * nCpuNum_);
	int ret = pthread_cond_init(&Msg_Cont_, NULL);
	assert(ret == 0);
	ret = pthread_mutex_init(&Msg_mutex_, NULL);
	assert(ret == 0);
}

CMain_Reactor::~CMain_Reactor()
{  
	pthread_cancel(accept_id_);
	delete Acceptor_;
	for(int i = 0; i < 1; i++)
	{  
		CEventLoop *loop = LoopList_[i];
		loop->Exit();
		delete loop;
		loop = NULL;
	}
	printf("total msg = %d\n", g_count);
	printf("Main_Reactor Exit\n");
	free(LoopList_);
	ReleasePendingMsg();
	pthread_cond_destroy(&Msg_Cont_);
	pthread_mutex_destroy(&Msg_mutex_);
}

void CMain_Reactor::Start()
{  
	if(Acceptor_->Init_Accept() < 0)
		exit(0);

	printf("Accept init success\n");
	for(int i = 0; i < 1; i++)
	{  
		CEventLoop* loop = new CEventLoop(this,Readcb_, Writecb_, Connectcb_, Closecb_);
		loop->Start();
		LoopList_[i] = loop;
	}
	
	pthread_create(&accept_id_, NULL, Accept_thread, this);
	BeginWork();
}

void CMain_Reactor::BeginWork()
{
	bExit_ = false;
	while(!bExit_)
	{
		std::queue<CMessage*> qmsg;
		PopAllMsg(qmsg);
		while(!qmsg.empty())
		{
			CMessage* Msg = qmsg.front();
			qmsg.pop();
			ProcessMsg(Msg);
		}
	}
}

void CMain_Reactor::Exit()
{  
	for(int i = 0; i < 1; i++)
	{  
		CEventLoop *loop = LoopList_[i];
		loop->Exit();
		delete loop;
		loop = NULL;
	}
	printf("total msg = %d\n", g_count);
	printf("Main_Reactor Exit\n");
	free(LoopList_);
}

void CMain_Reactor::SetExit()
{
	bExit_ = true;
	pthread_cond_signal(&Msg_Cont_);
}

void CMain_Reactor::BeginAccept()
{  
	int nRobin = 0;
	UNUSE(nRobin);
	while(1)
	{  
		int confd = Acceptor_->Start_Accept();
		if(confd >= 0)
		{  
			WritefdToLoop(confd);
		}
	}
}

void CMain_Reactor::PushMsg(CMessage * Msg)
{
	pthread_mutex_lock(&Msg_mutex_);
	bool empty = Msg_Queue_.empty();
	Msg_Queue_.push(Msg);
	if(empty)
		pthread_cond_signal(&Msg_Cont_);
	pthread_mutex_unlock(&Msg_mutex_);
}

bool CMain_Reactor::PopMsg(CMessage * Msg)
{
	pthread_mutex_lock(&Msg_mutex_);
	if(Msg_Queue_.empty())
	{
		pthread_mutex_unlock(&Msg_mutex_);
		return false;
	}

	Msg = Msg_Queue_.front();
	Msg_Queue_.pop();
	pthread_mutex_unlock(&Msg_mutex_);
	return true;
}

void CMain_Reactor::PopAllMsg(std::queue<CMessage*>& queuemsg)
{
	pthread_mutex_lock(&Msg_mutex_);
	while(Msg_Queue_.empty())
		pthread_cond_wait(&Msg_Cont_, &Msg_mutex_);
	queuemsg = std::move(Msg_Queue_);
	pthread_mutex_unlock(&Msg_mutex_);
}

void CMain_Reactor::ProcessMsg(CMessage * Msg)
{
	switch(Msg->GetType())
	{
	case 0://con exit
		CMessageAlloctor::FreeMSG(&Msg);
		break;
	case 1: // echo
		{
			char data[128];
			Msg->Readstr(data, sizeof(data));
			printf("client data = %s len = %d\n", data, strlen(data));
			PushSendQueue(Msg);
		}
		break;

	case 2:
		{
			int n1 = Msg->Readint();
			int n2 = Msg->Readint();
			int sum = n1 + n2;
		//	printf("n1 = %d n2 = %d sum = %d\n", n1, n2, sum);

			CMessage *ReMsg = CMessageAlloctor::AllocMSG(2);
			ReMsg->Write(sum);
			ReMsg->SetFd(Msg->GetFd());
			PushSendQueue(ReMsg);
			CMessageAlloctor::FreeMSG(&Msg);
		}
		break;

	case 3:
		{
			bExit_ = true;
			printf("main exit\n");
			CMessageAlloctor::FreeMSG(&Msg);
		}
		break;
	
	}
}


void CMain_Reactor::PushSendQueue(CMessage * Msg)
{
	Msg->SetSendFlag();
	g_count++;
	LoopList_[0]->EnQueue(Msg);
}

void CMain_Reactor::WritefdToLoop(int fd)
{
	LoopList_[0]->WritePipe(fd);
}

void CMain_Reactor::ReleasePendingMsg()
{
	while(!Msg_Queue_.empty())
	{
		CMessage *Msg = Msg_Queue_.front();
		Msg_Queue_.pop();
		CMessageAlloctor::FreeMSG(&Msg);
	}
}

void* Accept_thread(void *arg)
{
	CMain_Reactor* server = (CMain_Reactor*)arg;
	assert(server);
	server->BeginAccept();
	return NULL;
}

void* Connect_Thread(void * arg)
{
	CMain_Reactor* Reactor = (CMain_Reactor*)arg;
	const char* strip = "";
	unsigned short port = 0;
	int con_fd = CConnector::Connect_Host(strip, port);
	if(con_fd > 0)
	{
		Reactor->WritefdToLoop(con_fd);
	}
	return NULL;
}

