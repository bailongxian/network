#include "Connect.h"
#include "CSocket.h"
#include "MemPool.h"
#include "TimeList.h"
#include "Message.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <sys/epoll.h>
#include <sys/uio.h>
#include <sys/poll.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>

const int CConnect::kNoEvent    = 0;
const int CConnect::kReadEvent  = EPOLLIN | EPOLLPRI;
const int CConnect::kWriteEvent = EPOLLOUT;

CConnect::CConnect(CEventLoop *loop, ReadWriteCallBack Readcb, ReadWriteCallBack Writecb, ConnectCallBack Connectcb, CloseCallBack Closecb)
:event_(0),
active_event_(0),
Readcb_(Readcb),
Writecb_(Writecb),
Connectcb_(Connectcb),
Closecb_(Closecb),
EventLoop_(loop)

{  
	last_stat_time_ = 0;
	total_recieve_bytes_ = 0;
	total_send_bytes_ = 0;
	pSocket_ = NULL;
	buffmanage_ = NULL;
}

CConnect::~CConnect() 
{
	if(state_ == CON_CONNECTED)
	{
/*		active_event_ = 0;
		state_ = CON_INIT;
		event_ = kNoEvent;
		FreePendingMsg();
		EventLoop_->DelEvent(this);
		EventLoop_->FreeOldConnect(this);
*/		if(pSocket_ != NULL)
			delete pSocket_;
		if(buffmanage_ != NULL)
			delete buffmanage_;
	}
		
}
void CConnect::ProcessActiveEvent()
{  
	Print_recieve_info(EventLoop_->GetExpireTime());
	if((active_event_ & EPOLLHUP) && !(active_event_&EPOLLIN))
	{  
		Handle_Close();
	}
	
	if(active_event_ & (EPOLLERR))// | EPOLLVAL))
	{  
		printf("Handle_Error\n");
	 	Handle_Error();
	}

	if(active_event_ & (EPOLLIN | EPOLLRDHUP | EPOLLPRI))
	{  
		Handle_Read();
	}

	if(active_event_ & EPOLLOUT)
	{  
		Handle_Write();
	}
}

void CConnect::Remove()
{  
	if(Closecb_)
		Closecb_(this);

	if(state_ == CON_CONNECTED)
		EventLoop_->DeleteTimeNode(&TimeNode_); // may be called in handle timeout
	
	active_event_ = 0;
	state_ = CON_INIT;
	event_ = kNoEvent;
	FreePendingMsg();
	EventLoop_->DelEvent(this);
	EventLoop_->FreeOldConnect(this);
	delete pSocket_;
	pSocket_ = NULL;
	delete buffmanage_;
	buffmanage_ = NULL;
}

void CConnect::Exit()
{
	if(state_ == CON_CONNECTED)
		EventLoop_->DeleteTimeNode(&TimeNode_); // may be called in handle timeout
	
	active_event_ = 0;
	state_ = CON_INIT;
	event_ = kNoEvent;
	FreePendingMsg();
	EventLoop_->DelEvent(this);
	EventLoop_->FreeOldConnect(this);
	delete pSocket_;
	delete buffmanage_;
}

void CConnect::Init(int fd)
{
	pSocket_ = new CSocket(fd);
	buffmanage_ = new CBuffManage(EventLoop_->GetMemPool());
	state_ = CON_CONNECTED;
	event_ |= kReadEvent;
	TimeNode_.ExpireTime = time(NULL)+100;
	EventLoop_->AddTimeNode(&TimeNode_);
	if(Connectcb_)
		Connectcb_(this);
}


int CConnect::Writev()
{  
	std::vector<DataBuff*>& vWrite = buffmanage_->GetWriteList();
	const int iov_count = vWrite.size();
	if(iov_count == 0)
	{
		if(IsWriting())
			DisWriting();
		return 0;
	}

	struct iovec iow[iov_count];
	for (int i = 0; i < iov_count; ++i)
	{
		iow[i].iov_base = vWrite[i]->data + vWrite[i]->cur;
		iow[i].iov_len  = vWrite[i]->len - vWrite[i]->cur;
	}

	ssize_t  cur_iov = 0;
	ssize_t nwritenum = 0;
	int ntotalwrite = buffmanage_->GetWritable();
	
	while(ntotalwrite > nwritenum)
	{  		
		ssize_t n = writev(pSocket_->Get_Fd(), &iow[cur_iov], iov_count - cur_iov);
		if(n > 0)
		{  
			nwritenum += n;
			while(static_cast<unsigned int>(n) >= iow[cur_iov].iov_len)
				n -= iow[cur_iov++].iov_len;
			iow[cur_iov].iov_base = (char*)iow[cur_iov].iov_base+n;
			iow[cur_iov].iov_len  -= n;
		}
		else if(n < 0)
		{  
			if(errno == EAGAIN || errno == EWOULDBLOCK)
				break;
			else if(errno == EINTR)
				continue;
			else
			{
				Handle_Error();
				break;
			}
		}
		else
		{  
			break;
		}
	}
	
	if(ntotalwrite >= nwritenum) // no data in send buff, cancal write event
		DisWriting();

	buffmanage_->ReduceWriteNum(nwritenum);
	return nwritenum;
}

int CConnect::Write(const char* data, int len)
{  
	ssize_t size = write(pSocket_->Get_Fd(), data, len);
	if(size < 0)
	{  
		if(errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
		{
			size = 0;
			goto done;
		}
		else
			goto err;
	}
	else if(size < len) // add to out buff
	{  
		goto done;
	}
	return size;

err:
	Handle_Error();
	return size;
done:
	buffmanage_->IncreWriteBuff(data+size,static_cast<uint16_t>(len));
	SetWriting();
	return size;
	
}

int CConnect::Readv()
{  
	int nReadNum = 0;
	while(1)
	{  
		DataBuff *buff = buffmanage_->GetReadBuff();
		assert(buff);

		char tempbuf[65535];
		struct iovec iovec[2];
		int bufflen = buff->max - buff->len;
		iovec[0].iov_base = buff->data + buff->len;
		iovec[0].iov_len  = bufflen;
		iovec[1].iov_base = tempbuf;
		iovec[1].iov_len  = sizeof(tempbuf);

		ssize_t n = readv(pSocket_->Get_Fd(), &iovec[0], 2);
		
		if(n > 0)
		{  
			nReadNum += n;
			if (n <= bufflen)
			{
				buff->len += n;
			}
			else 
			{
				buff->len += bufflen;
				int size = n - bufflen;
				int ncout = 0;
				while(ncout < size)  // read num greater than bufflen
				{  
					buff = buffmanage_->GetReadBuff();
					int min = MIN((buff->max-buff->len), size - ncout);
					memcpy(buff->data+buff->len, tempbuf+ncout, min);
					ncout += min;
					buff->len += min;
				}
			}

			if(static_cast<unsigned int>(n) < bufflen + sizeof(tempbuf))
				break;
		}
		else if( n == 0)
		{  
			Handle_Close();
			return n;
		}
		else
		{
			if(errno == EAGAIN || errno == EWOULDBLOCK)
				break;
			else if(errno == EINTR)
				continue;
			else
			{
				Handle_Error();
				return n;
			}
		}
	}
	buffmanage_->AddReadNum(nReadNum);
	State_recieve_info(nReadNum);
	while(1)
	{
		CMessage *Msg = NULL;
		int nParase = buffmanage_->ParasePacket(&Msg);
		if(nParase > 0 && Msg) 
		{
			Msg->fd_ = GetFd();
			EventLoop_->PushMsg(Msg);
		}
		else if(nParase == 0)	
		{
			break;
		}
		else
		{
			Handle_Close();
			return -1;
		}
	}	
	
	return nReadNum;
}

int CConnect::Read()
{  
	char buff[256];
	ssize_t n =  read(pSocket_->Get_Fd(), buff, sizeof(buff));
	if(n > 0) 
	{
		buff[n] = '\0';
		printf("%s\n", buff);
	}
	else if(n == 0)
	{
		Handle_Close();
	}
	else if(n < 0)
	{
		perror("Read");
	}
	return n;
}

void CConnect::Handle_Read()
{ 
	Readv();

}

void CConnect::Handle_Write()
{ 
	SendAllMsg();
}

void CConnect::Handle_Error()
{   
	printf("info : %s\n", strerror(errno));
	if(state_ != CON_INIT)
		Handle_Close();
}

void CConnect::Handle_Close()
{  
	CMessage *Msg = CMessageAlloctor::AllocMSG(0);
	Msg->fd_ = GetFd();
	EventLoop_->PushMsg(Msg);
	Remove();
}

void CConnect::ShutDown()
{
	state_ = DIS_CONNECTING;
	pSocket_->Shutdown();
}

void CConnect::Send(char* data, int len)
{  
	int nwritable  = buffmanage_->GetWritable();
	if(nwritable > 0)
	{  
		buffmanage_->IncreWriteBuff(data,static_cast<uint16_t>(len));
		SetWriting();
	}
	else 
	{  
		// direct Send
		Write(data, len);
	}
}

void CConnect::SendMsg(CMessage* Msg)
{
	if(state_  != CON_CONNECTED)
	{
		CMessageAlloctor::FreeMSG(&Msg);
		return;
	}

//	Msg->PrintData();
	
	if(MsgList_.empty())
	{	
		int msglen = Msg->len_ - Msg->cur_;
		ssize_t size = write(pSocket_->Get_Fd(), Msg->data_+Msg->cur_, msglen);
		if(size >= msglen)
		{
			CMessageAlloctor::FreeMSG(&Msg);
			State_send_info(size);
			return;
		}
		else if(size >= 0)
		{
			Msg->cur_ += size;
			MsgList_.push_back(Msg);
			State_send_info(size);
			if(!IsWriting())
				SetWriting();
		}
		else
		{
			if(errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR)
				Handle_Error();
		}
	}
	else
	{
		MsgList_.push_back(Msg);
		if(!IsWriting())
			SetWriting();
	}
}

void CConnect::SendAllMsg()
{
	if(state_ != CON_CONNECTED)
		return;

	if(MsgList_.empty())
	{
		if(IsWriting())
			DisWriting();
	}
	else
	{
		int msgnum = MsgList_.size();
		const int iov_count = MIN(msgnum, (IOV_MAX));
	
		struct iovec iow[iov_count];
		std::list<CMessage*>::iterator it = MsgList_.begin();
		int i = 0;
		int ntotalwrite = 0;
		for(; it != MsgList_.end(); ++it)
		{
			CMessage *Msg = *it;
			int msglen = Msg->len_ - Msg->cur_;
			iow[i].iov_base = Msg->data_ + Msg->cur_;
			iow[i].iov_len  = msglen;
			ntotalwrite += msglen;
			i++;
			if(i >= iov_count)
				break;
		}
		
		ssize_t  cur_iov = 0;
		ssize_t nwritenum = 0;	
		while(ntotalwrite > nwritenum)
		{  		
			ssize_t n = writev(pSocket_->Get_Fd(), &iow[cur_iov], iov_count - cur_iov);
		//	printf("total = %d  writenum = %d  n = %d\n", ntotalwrite, nwritenum, n);
			if(n > 0)
			{  
				nwritenum += n;
				while(static_cast<unsigned int>(n) >= iow[cur_iov].iov_len)
				{
					n -= iow[cur_iov++].iov_len;
					it = MsgList_.begin();
					CMessageAlloctor::FreeMSG(&(*it));
					MsgList_.erase(it);
				}
				if(n > 0)
				{
					iow[cur_iov].iov_base = (char*)iow[cur_iov].iov_base+n;
					iow[cur_iov].iov_len  -= n;
					it = MsgList_.begin();
					(*it)->cur_ += n;
				}

				if(MsgList_.empty() && IsWriting())
					DisWriting();
			}
			else if(n < 0)
			{  
				if(errno == EAGAIN || errno == EWOULDBLOCK)
					break;
				else if(errno == EINTR)
					continue;
				else
				{
					Handle_Error();
					break;
				}
			}
			else
			{  
				break;
			}
		}
		
		State_send_info(nwritenum);
		// all pending msg has beeb send
/*		if(static_cast<unsigned int>(iov_count) >= MsgList_.size() && ntotalwrite >= nwritenum)
		{
			it = MsgList_.begin();
			for(; it != MsgList_.end(); ++it)
				CMessageAlloctor::FreeMSG(&(*it));
			MsgList_.clear();
			if(IsWriting())
				DisWriting();
		}
		else
		{
			for(it = MsgList_.begin(); it != MsgList_.end()&& ntotalwrite>0; )
			{
				CMessage *msg = *it;
				int msglen = msg->len_ - msg->cur_;
				if(msglen <= ntotalwrite)
				{
					CMessageAlloctor::FreeMSG(&msg);
					it = MsgList_.erase(it);
					ntotalwrite -= msglen;
				}
				else
				{
					msg->cur_ += ntotalwrite;
					ntotalwrite = 0;
				}
			}
			if(!IsWriting())
				SetWriting();
		}
*/	}
}

void CConnect::FreePendingMsg()
{
	std::list<CMessage*>::iterator it = MsgList_.begin();
	for(; it != MsgList_.end(); ++it)
	{
		CMessage* Msg = *it;
		CMessageAlloctor::FreeMSG(&Msg);
	}
	MsgList_.clear();
}

int CConnect::GetFd()
{
	return pSocket_->Get_Fd();
}

inline void CConnect::State_recieve_info(unsigned int recieve_bytes)
{
	total_recieve_bytes_ += recieve_bytes;
}

inline void CConnect::State_send_info(unsigned int send_bytes)
{
	total_send_bytes_ += send_bytes;
}

void CConnect::Print_recieve_info(time_t cur)
{
	if(last_stat_time_ < cur && (total_recieve_bytes_ > 0 || total_send_bytes_ > 0))
	{
		printf("recieve %d bytes send % d bytes per second\n", total_recieve_bytes_, total_send_bytes_);
		total_recieve_bytes_ = 0;
		total_send_bytes_ = 0;
		last_stat_time_ = cur;
	}
}
