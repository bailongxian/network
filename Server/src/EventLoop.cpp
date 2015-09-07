#include "./EventLoop.h"
#include "./Connect.h"
#include "./Epoll.h"
#include "TimeList.h"
#include "MemPool.h"
#include "Main_Reactor.h"
#include "Message.h"

#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <sys/eventfd.h>
#include <string.h>
#include <errno.h>

#define		OFFSETOF(type, member) ((size_t) &((type*)0)->member)
#define		CONTAINER_OF(ptr, type, member) ({ \
	const decltype(((type*)0)->member) *_mptr = (ptr); \
	(type*)((char*)_mptr - OFFSETOF(type, member)); })

#define		MAX_CLIENT_NUM 32768

int g_total = 0;

CEventLoop::CEventLoop(CMain_Reactor* Server, int Index, ReadWriteCallBack Readcb, ReadWriteCallBack Writecb, ConnectCallBack Connctcb, CloseCallBack Closecb)
:bRun_(false),
Server_(Server),
nIndex_(Index),
Readcb_(Readcb),
Writecb_(Writecb),
Connectcb_(Connctcb),
Closecb_(Closecb),
Epoller_(new CEpoller(this)),
Timelist_(new CTimeList()),
MemPool_(new CMemPool())
{  
	int ret = pipe2(pipe, O_NONBLOCK|O_CLOEXEC);
	assert(!ret);
	Epoller_->Regist_Pipe(pipe[0]);
	evfd_ = eventfd(0, O_NONBLOCK);
	Epoller_->Regist_Pipe(evfd_);
	InitConnectPool();
	ret = pthread_mutex_init(&sendqueue_mutex_, NULL);
	assert(ret == 0);
}

CEventLoop::~CEventLoop()
{  
	delete Timelist_;
	delete MemPool_;
	close(pipe[0]);
	close(pipe[1]);
	close(evfd_);
	ReleaseConnectPool();
	delete Epoller_;
	ReleasePendingMsg();
	pthread_mutex_destroy(&sendqueue_mutex_);
	printf("total send = %d\n", g_total);
}

void* io_loop(void *arg)
{  
	CEventLoop* loop = (CEventLoop*)arg;
	loop->MainLoop(NULL);
	return NULL;
}

void CEventLoop::Start()
{  
	pthread_create(&tid_, NULL, io_loop, this);
	printf("Thread id %ld Start\n", tid_);
}

void CEventLoop::Exit()
{  
	int num = -1;
	write(pipe[1], &num, sizeof(num));
	printf("begin join\n");
	pthread_join(tid_, NULL);
	printf("end join\n");
}

void* CEventLoop::MainLoop(void* arg)
{  
	assert(!bRun_);
	bRun_ = true;
	while(bRun_)
	{  
		activeConnect_.clear();
		unsigned long time_out = 1000 * Timelist_->GetMinExpireTime();
		Epoller_->Epoll_Wait(activeConnect_, time_out);
		time(&expiretime_);
		ProcessActiveEvent();
		ProcessQueue();
		HandleTimeOut();
	}
	printf("main Loop end\n");
	return NULL;
}

void CEventLoop::ProcessActiveEvent()
{  
	for(size_t i = 0; i < activeConnect_.size(); i++)
	{  
		CConnect *pConnect = activeConnect_[i];
		pConnect->ProcessActiveEvent();
		if (pConnect->Get_State() == CON_CONNECTED)  // if state != CONNECTED, the node  has be remove in handle_close() or handletimeout
		{
			TimeNode* Node = pConnect->GetTimeNode();
			Timelist_->Remove(Node);
			Node->ExpireTime = expiretime_+100;
			Timelist_->Insert(Node);
		}
	}
}

void CEventLoop::InitConnectPool()
{
	for (int i = 0; i < MAX_CLIENT_NUM; ++i)
	{
		CConnect* connect = new CConnect(this, Readcb_, Writecb_, Connectcb_, Closecb_);
		connect->Set_State(static_cast<Conn_State>(0));
		listConnect_.push_back(connect);
	}
}

void CEventLoop::ReleaseConnectPool()
{
	size_t  size = listConnect_.size();
	for(std::list<CConnect*>::iterator it = listConnect_.begin(); it != listConnect_.end();++it)
	{
		delete *it;
	}
	listConnect_.clear();

	size_t con_size = mapConnect_.size();
	for(std::map<long, CConnect*>::iterator it = mapConnect_.begin(); it != mapConnect_.end(); ++it)
	{
		delete it->second;
	}
	mapConnect_.clear();
	
	assert(size+con_size == MAX_CLIENT_NUM);
}

CConnect* CEventLoop::AllocNewConnect(int fd)
{  
	if(listConnect_.empty())
		return NULL;
	CConnect *pNewConnect = listConnect_.front();
	listConnect_.pop_front();
	mapConnect_[fd] = pNewConnect;
	return pNewConnect;
}

void CEventLoop::FreeOldConnect(CConnect* pConnect)
{  
	assert(pConnect);
	assert(pConnect->Get_State() == CON_INIT);
	assert(mapConnect_.find(pConnect->GetFd()) != mapConnect_.end());

	mapConnect_.erase(pConnect->GetFd());
	listConnect_.push_back(pConnect);
}

void CEventLoop::AddNewCon_or_Exit()
{  
	int fd;
	ssize_t n = read(pipe[0], &fd, sizeof(fd));
	assert(n == sizeof(fd));
	if(fd < 0)
	{  
		bRun_ = false;
//		printf("Thread id %ld Exit\n", tid_);
	}
	else
	{  
		CConnect* pNewConnect = AllocNewConnect(fd);
		if(pNewConnect == NULL) // achive limit
		{  
			close(fd);
			printf("no more connect alloc\n");
		}
		else
		{  
			pNewConnect->Init(fd);
			Epoller_->Add_Event(pNewConnect);
		}
	}
}

void CEventLoop::HandleTimeOut()
{  
	while(true)
	{  
		TimeNode *Node = Timelist_->GetExpireNode(expiretime_);
		if(Node == NULL)
			break;

		CConnect *pConnect = CONTAINER_OF(Node, CConnect, TimeNode_);
		assert(pConnect);
		printf("Connect %d TimeOut\n", pConnect->GetFd());
		pConnect->ShutDown();
		Timelist_->Remove(Node);
	}
} 

void CEventLoop::AddTimeNode(TimeNode *Node)
{
	Timelist_->Insert(Node);
}

void CEventLoop::DeleteTimeNode(TimeNode* Node)
{
	Timelist_->Remove(Node);
}

int CEventLoop::WritePipe(int Confd)
{  
	ssize_t n = write(pipe[1], &Confd, sizeof(Confd));
	if(n != sizeof(Confd))
	{  
		// write log
		return -1;
	}
	return 0;
}

void CEventLoop::ModEvent(CConnect *Connect)
{ 	
	Epoller_->Mod_Event(Connect);
}

void CEventLoop::DelEvent(CConnect *Connect)
{
	Epoller_->Del_Event(Connect);
}

CMemPool* CEventLoop::GetMemPool() const
{
	return MemPool_;
}

void CEventLoop::PushMsg(CMessage* Msg)
{
	Server_->PushMsg(Msg);
}

void CEventLoop::WakeUp()
{
	long long value = 1;
	ssize_t n = write(evfd_, &value, sizeof(value));
	if(n != sizeof(value))
	{
		printf("wakeup error\n");
	}
//	else
//		printf("wakeup success %d\n", evfd_);
}

void CEventLoop::BeWakeUp()
{
//	printf("raise\n");
	long long value;
	ssize_t n = read(evfd_, &value, sizeof(value));
	if(n != sizeof(value))
	{
		printf("bewakeup error\n");
	}
	
}

void CEventLoop::EnQueue(CMessage * Msg)
{
	pthread_mutex_lock(&sendqueue_mutex_);
	sendqueue_.push(Msg);
//	int size = sendqueue_.size();
//	printf("queue size = %d\n", size);
	pthread_mutex_unlock(&sendqueue_mutex_);
	WakeUp();
}

void CEventLoop::DeQueue(std::queue<CMessage*>& TempMsg)
{
	pthread_mutex_lock(&sendqueue_mutex_);
	TempMsg = std::move(sendqueue_);
	pthread_mutex_unlock(&sendqueue_mutex_);
}

void CEventLoop::ProcessQueue()
{
	std::queue<CMessage*> temMsg;
	DeQueue(temMsg);
	int size = temMsg.size();
	g_total += size;
	while(!temMsg.empty())
	{
		CMessage *Msg = temMsg.front();
		temMsg.pop();
		std::map<long, CConnect*>::iterator it = mapConnect_.find(Msg->GetFd());
		if(it == mapConnect_.end())
		{
			printf("client_fd = %d no find\n",Msg->GetFd());
			CMessageAlloctor::FreeMSG(&Msg);
		}
		else
			it->second->SendMsg(Msg);
	}
}

void CEventLoop::ReleasePendingMsg()
{
	while(!sendqueue_.empty())
	{
		CMessage *Msg = sendqueue_.front();
		sendqueue_.pop();
		CMessageAlloctor::FreeMSG(&Msg);
	}
}