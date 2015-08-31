#ifndef _MAIN_REACTOR_H_
#define _MAIN_REACTOR_H_

#include "Common.h"
#include <queue>
#include <pthread.h>

class CEventLoop;
class CAcceptor;
class CMessage;

class CMain_Reactor
{  
public:
	CMain_Reactor(ReadWriteCallBack Readcb, ReadWriteCallBack Writecb, ConnectCallBack Connectcb, CloseCallBack Closecb);
	~CMain_Reactor();

	void Start();
	void Exit();
	void BeginAccept();
	void BeginWork();
	void PushMsg(CMessage* Msg);
	bool PopMsg(CMessage* Msg);
	void PopAllMsg(std::queue<CMessage*>& queuemsg);
	void SendMsg(CMessage* Msg);
	void ProcessMsg(CMessage* Msg);
	void WritefdToLoop(int fd);

	void PushSendQueue(CMessage* Msg);

	void SetExit();
private:
	void ReleasePendingMsg();
private:
	bool					bExit_;
	const int           	nCpuNum_;
	pthread_t			  	accept_id_;
	CEventLoop**   			LoopList_;
	CAcceptor*  			Acceptor_;
	ReadWriteCallBack		Readcb_;
	ReadWriteCallBack 		Writecb_;
	ConnectCallBack			Connectcb_;
	CloseCallBack			Closecb_;
	std::queue<CMessage*> Msg_Queue_;
	pthread_mutex_t			Msg_mutex_;
	pthread_cond_t			Msg_Cont_;
	
};

#endif
