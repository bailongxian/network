#include "./Epoll.h"
#include "./Connect.h"
#include "./EventLoop.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/epoll.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

CEpoller::CEpoller(CEventLoop *loop)
{  
	epollfd_ = (epoll_create1(0));
	Eventloop_ = loop;
	Event_.resize(32);
	assert(epollfd_ >= 0);
}

CEpoller::~CEpoller()
{  
	close(epollfd_);
}

void CEpoller::Epoll_Wait(std::vector<CConnect*>& ActiveConnectList, unsigned long timeout)
{  
	int nActiveNum = epoll_wait(epollfd_, &*Event_.begin(), Event_.size(), timeout);
//	printf("wait done = %d\n", nActiveNum);
	if(nActiveNum > 0)
	{  
		FillActiveEvent(nActiveNum, ActiveConnectList);
	}
	else if(nActiveNum == 0) // timeout
	{  
		Eventloop_->HandleTimeOut();
	}
	else	// error
	{  
		printf("epoll_wait %s error\n", strerror(errno));	
	}

	if(nActiveNum >= static_cast<int>(Event_.size()))
		Event_.resize(Event_.size()*2);	
}

void CEpoller::FillActiveEvent(int nActiveNum, std::vector<CConnect*>& ActiveConnectList)
{  
	ActiveConnectList.reserve(nActiveNum);
	for(int i = 0; i < nActiveNum; i++)
	{  
		CConnect *Connect = static_cast<CConnect*>(Event_[i].data.ptr);
		if((int)Connect < 0x10) // new connect or exit loop
		{  
			if(Event_[i].data.fd == Eventloop_->GetReadPipe())
				Eventloop_->AddNewCon_or_Exit();
			else
				Eventloop_->BeWakeUp();
		}
		else
		{  
			Connect->SetActiveEvent(Event_[i].events);
			ActiveConnectList.push_back(Connect);
		}
	}
}

void CEpoller::Regist_Pipe(int pipefd)
{  
	struct epoll_event event;
	bzero(&event, sizeof(event));
	event.data.ptr = NULL;
	event.data.fd = pipefd;
	event.events = EPOLLIN;
	int ret = epoll_ctl(epollfd_, EPOLL_CTL_ADD, pipefd, &event);
	printf("Event %d, operate %d  type %d ret %d\n",pipefd, EPOLL_CTL_ADD, EPOLLIN, ret);
}

void CEpoller::Update_Event(int operate, CConnect* Connect)
{  
	struct epoll_event event;
	bzero(&event, sizeof(event));
	event.data.ptr = Connect;
	event.events =  Connect->GetEvent();
	int ret = epoll_ctl(epollfd_, operate, Connect->GetFd(), &event);
//	UNUSE(ret);
	printf("Event %d, operate %d  type %d ret %d\n",Connect->GetFd(), operate, Connect->GetEvent(), ret);
}

void CEpoller::Add_Event(CConnect* Connect)
{  
	Update_Event(EPOLL_CTL_ADD, Connect);
}

void CEpoller::Mod_Event(CConnect* Connect)
{  
	Update_Event(EPOLL_CTL_MOD, Connect);
}

void CEpoller::Del_Event(CConnect* Connect)
{  
	Update_Event(EPOLL_CTL_DEL, Connect);
}
