#ifndef _EVENTLOOP_H_
#define _EVENTLOOP_H_

#include <map>
#include <list>
#include <vector>
#include <time.h>
#include <queue>
#include <pthread.h>
#include <pthread.h>
#include "Common.h"

class CConnect;
class CEventLoop;
class CEpoller;
class CTimeList;
class CMemPool;
class CMain_Reactor;
class CMessage;
struct TimeNode;

class CEventLoop
{  
public:
	CEventLoop(CMain_Reactor* Server, int index,
		ReadWriteCallBack Readcb, ReadWriteCallBack Writecb, 
		ConnectCallBack Connectcb, CloseCallBack Closecb);
	~CEventLoop();

	void  Start();
	void  Exit();
	void* MainLoop(void*);

	CConnect* AllocNewConnect(int fd);
	void 	  FreeOldConnect(CConnect* Con);

	void      AddNewCon_or_Exit();	// fd negative is exit
	void 	  HandleTimeOut();

	int 	 GetReadPipe() const {return pipe[0];}
	int 	 GetWritePipe() const {return pipe[1];}

	int 	 WritePipe(int Confd);

	int		 GetEventfd() const {return evfd_;}

	time_t	 GetExpireTime() const {return expiretime_;}
	void 	 AddTimeNode(TimeNode *Node);
	void 	 DeleteTimeNode(TimeNode *Node);

	void 	 ModEvent(CConnect* Connect);
	void 	 DelEvent(CConnect* Connect);

	CMemPool* GetMemPool() const ;

	void 	 PushMsg(CMessage* Msg);
	
	void 	 ReadMsg();
	void 	 WriteMsg(CMessage* Msg);

	void     EnQueue(CMessage* Msg);
	void	 DeQueue(std::queue<CMessage*>& TempMsg);
	void 	 ProcessQueue();

	void 	 WakeUp();
	void	 BeWakeUp();

	int		 GetIndex() const	{return nIndex_;}

private:

	void ProcessActiveEvent();
	void InitConnectPool();
	void ReleaseConnectPool();
	void ReleasePendingMsg();

private:	
	bool 		bRun_;
	int  		pipe[2];  // 0 read 1 write
	int 		evfd_;
	pthread_t	tid_;
	time_t 		expiretime_;
	CMain_Reactor*	  Server_;
	int 		nIndex_;
	ReadWriteCallBack Readcb_;
	ReadWriteCallBack Writecb_;
	ConnectCallBack	Connectcb_;
	CloseCallBack		Closecb_;
	CEpoller* 	Epoller_;
	CTimeList* 	Timelist_;
	CMemPool*	MemPool_;
	pthread_mutex_t			   sendqueue_mutex_;
	std::vector<CConnect*>     activeConnect_;
	std::list<CConnect*>       listConnect_;
	std::map<long, CConnect*>  mapConnect_;
	std::queue<CMessage*>	   sendqueue_;
	
};

#endif
