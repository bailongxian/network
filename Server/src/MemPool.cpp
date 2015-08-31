#include "MemPool.h"
#include "Common.h"
#include "Message.h"

#include <assert.h>
#include <string.h>

#define MAX_ALLOC_SIZE	1024*1024*10

CBuffManage::~CBuffManage()
{
	for (size_t i = 0; i < vRead_.size(); ++i)
	{
		mempool_->Free(vRead_[i]);
	}
	vRead_.clear();

	for (size_t i = 0; i < vWrite_.size(); ++i)
	{
		mempool_->Free(vWrite_[i]);
	}
	vWrite_.clear();
}

void CBuffManage::ReduceReadNum(uint32_t num)
{
	assert(num <= nReadable_);
	nReadable_ -= num;

	std::vector<DataBuff*>::iterator it = vRead_.begin();
	for(;num && it != vRead_.end();)
	{
		uint32_t size = (*it)->len - (*it)->cur;
		if(num >= size)
		{
			num -= size;
			mempool_->Free(*it);
			vRead_.erase(it);
		}
		else 
		{
			(*it)->cur += num;
			num = 0;
			break;
		}
	}
	assert(num == 0);
}

void CBuffManage::ReduceWriteNum(uint32_t num)
{
	assert(num <= nWritable_);
	nWritable_ -= num;

	std::vector<DataBuff*>::iterator it = vWrite_.begin();
	for(; num && it != vWrite_.end();)
	{
		uint32_t size = (*it)->len - (*it)->cur;
		if (num >= size)
		{
			num -= size;
			mempool_->Free(*it);
			vWrite_.erase(it);	
		}
		else
		{
			num = 0;
			(*it)->cur += num;
			break;
		}
	}
}

void CBuffManage::IncreReadBuff(const char * buf,uint16_t len)
{

}

void CBuffManage::AddReadNum(uint32_t num)
{
	nReadable_ += num;
}

void CBuffManage::IncreWriteBuff(const char * buf,uint16_t len)
{
	int count = 0;
	while(count > len)
	{
		DataBuff *pBuff = GetWriteBuff();
		if(pBuff == NULL)
			break;
		uint16_t min = MIN(pBuff->max - pBuff->len, len);
		memcpy(pBuff->data + pBuff->len, buf + count, min);
		pBuff->len += min;
		count += min;
	}
	AddWriteNum(count);
}

int CBuffManage::ParasePacket(CMessage** Msg) // -1 parase error  0 incomplete packet 1 complete packet
{
	if(nReadable_ < PACK_HEAD_SIZE)
		return 0;
	uint16_t msg_len = 0;
	uint16_t count = PACK_LEN;
	for(size_t i = 0; i < vRead_.size(); i++)
	{
		int bufflen = vRead_[i]->len - vRead_[i]->cur;
		char* pdata = vRead_[i]->data + vRead_[i]->cur;
		if(bufflen >= count)
		{
			memcpy((char*)&msg_len+(PACK_LEN-count), pdata, count);
			break;
		}
		else
		{
			memcpy((char*)&msg_len+(PACK_LEN-count), pdata, bufflen);
			count -= bufflen;
		}
	}

	if(msg_len > nReadable_)
		return 0;
	if(msg_len == 0)
	{
		printf("invaild message lenght\n");
		return -1;
	}

	*Msg = CMessageAlloctor::AllocMSG(0, msg_len);
	count = 0;
	int total = msg_len;
	for(size_t i = 0; i < vRead_.size(); i++)
	{
		int bufflen = vRead_[i]->len - vRead_[i]->cur;
		char* pdata = vRead_[i]->data + vRead_[i]->cur;
		if(bufflen >= total)
		{
			memcpy((*Msg)->data_ + count, pdata, total);
			count += total;
			break;
		}
		else
		{
			memcpy((*Msg)->data_ + count, pdata, bufflen);
			count += bufflen;
			total -= bufflen;
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
	ReduceReadNum(count);
	return 1;
}

void CBuffManage::AddWriteNum(uint32_t num)
{
	nWritable_ += num;
}

DataBuff* CBuffManage::GetReadBuff()
{
	DataBuff* buff = NULL;
	if(vRead_.empty() || vRead_[vRead_.size()-1]->IsFull())
	{
		buff = mempool_->Alloc(0);
		vRead_.push_back(buff);
	}
	else
	{
		buff = vRead_[vRead_.size()-1];
	}
	return buff;
}

DataBuff* CBuffManage::GetWriteBuff()
{
	DataBuff* buff = NULL;
	if (vWrite_.empty() || vWrite_[vWrite_.size()-1]->IsFull())
	{
		buff = mempool_->Alloc(0);
		vRead_.push_back(buff);
	}
	else
	{
		buff = vWrite_[vWrite_.size()-1];
	}
	return buff;
}

CMemPool::CMemPool()
{  
	InitBuffList();
}

CMemPool::~CMemPool()
{  
	ReleaseBuffList();
}

void CMemPool::InitBuffList()
{  
	int BlockNum = 1024;
	for(int i = 0; i < BlockNum; i++)
	{  
		DataBuff *buff = new DataBuff(512);
		BuffList_.push_back(buff);
	}
}

void CMemPool::ReleaseBuffList()
{  
	std::list<DataBuff*>::iterator it = BuffList_.begin();
	for(; it != BuffList_.end(); ++it)
		delete *it;
	BuffList_.clear();
}

DataBuff* CMemPool::Alloc(uint32_t size)
{  
	DataBuff *buf = NULL;
	if(!BuffList_.empty())
	{  
		buf = BuffList_.front();
		BuffList_.pop_front();
	}
	else 
	{
		buf = new DataBuff(512);
//		printf("Read Mempool has no more data\n");
	}
	return buf;
}

void CMemPool::Free(DataBuff *data)
{  
	assert(data);
	data->cur = data->len = 0;
	BuffList_.push_back(data);
}
