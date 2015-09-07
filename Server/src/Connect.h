#ifndef _CONNECT_H_
#define _CONNECT_H_

#include <vector>
#include <stdint.h>
#include "TimeList.h"
#include "Common.h"
#include "EventLoop.h"
#include "MemPool.h"

enum Conn_State
{  
	CON_INIT 			= 0,
	CON_CONNECTING 		= 1 << 0,
	CON_CONNECTED		= 1 << 1,
	DIS_CONNECTING 	    = 1 << 2,
	DIS_CONNECTED		= 1 << 3,
	CON_READING			= 1 << 4,	//reading a message packet
	CON_WRITING			= 1 << 5	//writig a message packet
};

// msg head(16)+data = size

class CSocket;
class CMessage;
struct DataBuff;

class CConnect
{
public:	
	CConnect(CEventLoop *loop, ReadWriteCallBack Readcb,
		ReadWriteCallBack Writecb,  ConnectCallBack Connectcb, CloseCallBack Closecb);
	~CConnect();

	void ProcessActiveEvent();
	void Init(int fd);

	Conn_State Get_State() const {return state_;}
	void Set_State(Conn_State state) {state_ = state;}

	void SetWriting() {event_ |= kWriteEvent; EventLoop_->ModEvent(this);}
	void SetReading() {event_ |= kReadEvent;EventLoop_->ModEvent(this);}
	void DisWriting() {event_ &= ~kWriteEvent;EventLoop_->ModEvent(this);}
	void DisReading() {event_ &= ~kReadEvent;EventLoop_->ModEvent(this);}
	bool IsReading()	  {return event_ & kReadEvent;}
	bool IsWriting()  {return event_ & kWriteEvent;}
	void DisAll()	  {event_ = kNoEvent;EventLoop_->ModEvent(this);}
	int GetEvent() const {return event_;}
	int  GetFd();
	void SetFd(int fd);
	

	void SetActiveEvent(int event) {active_event_= event;}
	void ResetActiveEvent() {active_event_ = 0;}

	void Handle_Read();
	void Handle_Write();
	void Handle_Error();
	void Handle_Close();
	void Handle_Connect();
	void ShutDown();

	void Send(char* data, int len);
	void SendMsg(CMessage* Msg);
	void SendAllMsg();

	TimeNode* GetTimeNode() {return &TimeNode_;}
	CBuffManage* GetBuffManage() {return buffmanage_;}

private:
	void Remove();
	void Exit();
	int Writev();
	int Write(const char* data, int len);
	int Readv();
	int Read();
	void FreePendingMsg();

	void State_recieve_info(unsigned int recieve_bytes);
	void State_send_info(unsigned int send_bytes);
	void Print_recieve_info(time_t cur);

public:
		TimeNode TimeNode_;  //
private:
	int 		event_;
	int 		active_event_;
	Conn_State  state_;

	
	static const int 	kNoEvent;
	static const int 	kReadEvent;
	static const int	kWriteEvent;
	ReadWriteCallBack 	Readcb_;
	ReadWriteCallBack 	Writecb_;
	ConnectCallBack 	Connectcb_;
	CloseCallBack		Closecb_;

	time_t			last_stat_time_;
	unsigned int	total_recieve_bytes_;
	unsigned int	total_send_bytes_;

	CSocket 	*pSocket_;
	CEventLoop 	*EventLoop_;
	CBuffManage	*buffmanage_;
	std::list<CMessage*> MsgList_;
};

#endif
