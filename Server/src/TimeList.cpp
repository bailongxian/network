#include "TimeList.h"
#include <assert.h>
#include <stdio.h>

#define	DEFAULT_TIME_OUT	60

CTimeList::CTimeList()
:len_(0),
Head_(NULL),
Tail_(NULL)
{	
} 

CTimeList::~CTimeList()
{

}

void CTimeList::Insert(TimeNode* Node)
{
	assert(Node);
	if(len_ == 0)
	{
		Head_ = Tail_ = Node;
		Head_->Pre = Tail_->Pre = Node->Pre = NULL;
		Head_->Next = Tail_->Next = Node->Next = NULL;
	}
	else
	{
		Node->Next = Tail_->Next;
		Node->Pre = Tail_;
		Tail_->Next= Node;
		Tail_ = Node;
	}
	len_++;
}

void CTimeList::Remove(TimeNode* Node)
{
	assert(len_ > 0);

	if(Node == Head_)
	{
		Head_ = Node->Next;
	}
	else
	{
		Node->Pre->Next = Node->Next;
	}

	if(Node == Tail_)
	{
		Tail_ = Node->Pre;	
	}
	else
	{
		Node->Next->Pre = Node->Pre;
	}
	len_--;
}

TimeNode* CTimeList::GetExpireNode(time_t cur)
{
	if(len_ == 0)
		return NULL;

	TimeNode *Node = Head_;
	if(Node->ExpireTime < cur)
		return Node;
	return NULL;
}

time_t CTimeList::GetMinExpireTime()
{
	if(len_ == 0)
		return DEFAULT_TIME_OUT;

	time_t cur = time(NULL);
	time_t expireTime = Head_->ExpireTime;
	if(cur >= expireTime)
	{
		return DEFAULT_TIME_OUT;
	}
	return expireTime - cur;
}