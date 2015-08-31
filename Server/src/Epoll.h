#ifndef _EPOLLER_H_
#define _EPOLLER_H_

#include <vector>
#include <sys/epoll.h>

class CConnect;
class CEventLoop;

class CEpoller
{  
public:

	CEpoller(CEventLoop *);
	~CEpoller();

	void Epoll_Wait(std::vector<CConnect*>& ActiveConnectList, unsigned long timeout);
	
	void Regist_Pipe(int pipefd);
	void Add_Event(CConnect* Connect);
	void Mod_Event(CConnect* Connect);
	void Del_Event(CConnect* Connect);

	void FillActiveEvent(int num, std::vector<CConnect*>& ActiveConnectList);
private:
	
	void Update_Event(int operate, CConnect* Connect);

	int epollfd_;
	CEventLoop* Eventloop_;
	typedef std::vector<struct epoll_event> EventList;
	EventList Event_;
};

#endif
