#ifndef _TIMELIST_H_
#define _TIMELIST_H_

#include <time.h>

struct TimeNode
{
	time_t		ExpireTime;
	TimeNode* 	Pre;
	TimeNode* 	Next;
};

class CTimeList
{
public:
	CTimeList();
	~CTimeList();

	void Insert(TimeNode* Node);
	void Remove(TimeNode* Node);

	TimeNode* GetExpireNode(time_t cur);
	time_t GetMinExpireTime();
	/* data */
private:
	int  	  len_;
	TimeNode* Head_;
	TimeNode* Tail_;
};

#endif 
