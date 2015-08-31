#include "ReadBuff.h"
#include "Message.h"

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

CReadBuff::CReadBuff():nReadable_(0)
{

}

CReadBuff:: ~CReadBuff()
{

}


CReadBuff::Buff* CReadBuff::Getbuff()
{
	if(ListBuff_.empty())
	{
		Buff* buff = new Buff();
		ListBuff_.push_back(buff);
		return buff;
	}

	Buff* buff = ListBuff_[ListBuff_.size()-1];
	if(buff->len < buff->max)
		return buff;
	else
	{
		buff = new Buff();
		ListBuff_.push_back(buff);
		return buff;
	}
}

int CReadBuff::ParaseMsg(CMessage ** Msg)
{
	if(nReadable_ < PACK_HEAD_SIZE)
		return 0;
	uint16_t msg_len = 0;
	uint16_t count = 2;
	for(size_t i = 0; i < ListBuff_.size(); i++)  // parase packet header
	{
		Buff *buff = ListBuff_[i];
		unsigned short num = buff->len - buff->cur;
		if(num >= count)
		{
			memcpy((char*)&msg_len+(PACK_LEN-count), buff->data+buff->cur, count);
			break;
		}
		else
		{
			memcpy((char*)&msg_len+(PACK_LEN-count), buff->data+buff->cur, num);
			count -= num;
		}
	}

	if(msg_len > nReadable_)
		return 0;
	
	if(msg_len == 0)
		return 0;
	*Msg = CMessageAlloctor::AllocMSG(0, msg_len);
	count = 0;
	int total = msg_len;
	for(size_t i = 0; i < ListBuff_.size(); i++) // copy data
	{
		Buff *buff = ListBuff_[i];
		unsigned short num = buff->len - buff->cur;
		char* pdata = buff->data + buff->cur;
		if(num >= total)
		{
			memcpy((*Msg)->data_ + count, pdata, total);
			count += total;
			break;
		}
		else
		{	
			memcpy((*Msg)->data_ + count, pdata, num);
			count += num;
			total -= num;
		}
	}

	if(count != msg_len)
	{
		CMessageAlloctor::FreeMSG(Msg);
		*Msg = NULL;
		printf("parase msg packet error");
		return -1;
	}
	(*Msg)->SetLen(msg_len);
	nReadable_ -= msg_len;
	ReleaseBuff(msg_len);
	return 1;
	
}

void CReadBuff::ReleaseBuff(unsigned short num)
{
	std::vector<Buff*>::iterator it = ListBuff_.begin();
	for(; num && it != ListBuff_.end();)
	{
		Buff *buff = *it;
		unsigned short len = buff->len - buff->cur;
		int min = len < num ? len : num;
		buff->cur += min;
		num -= min;
		unsigned short space = buff->max - buff->len;
		len = buff->len - buff->cur;
		if(space < 1 && len == 0)
		{
			it = ListBuff_.erase(it);
			delete buff;
		}
		else
			++it;
	}
}

void CReadBuff::PrintInfo()
{
	printf("readable = %d\n", nReadable_);
	for(size_t i = 0; i < ListBuff_.size(); i++)
	{
		int cur = ListBuff_[i]->cur;
		int len = ListBuff_[i]->cur;
		int max = ListBuff_[i]->max;
		printf("i = %d cur = %d len = %d max = %d\n", i, cur, len, max);
	}
}