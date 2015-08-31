#ifndef _MEMPOOL_H_
#define _MEMPOOL_H_

#include "Common.h"
#include <stdint.h>
#include <list>
#include <stdlib.h>
#include <vector>

class CMemPool;
class CMessage;

struct DataBuff
{  
	char   *data;
	uint16_t max;
	uint16_t len;
	uint16_t cur;

	DataBuff(uint16_t size):data((char*)malloc(size)),
	max(size),
	len(0),
	cur(0)
	{  
	
	}

	~DataBuff()
	{  
		free(data);
	}

	bool IsFull() const {return len >= max;}
};

class CBuffManage
{
public:
	CBuffManage(CMemPool* pool):nReadable_(0), nWritable_(0), mempool_(pool)
	{}
	~CBuffManage();

	inline uint32_t GetReadable() const {return nReadable_;}
	inline uint32_t GetWritable() const {return nWritable_;}
	void     ReduceReadNum(uint32_t num);
	void 	 ReduceWriteNum(uint32_t num);
	void 	 IncreReadBuff(const char* buf, uint16_t len);
	void 	 AddReadNum(uint32_t num);
	void	 IncreWriteBuff(const char* buf, uint16_t len);

	DataBuff* GetReadBuff();
	std::vector<DataBuff*>& GetReadList() {return vRead_;}
	DataBuff* GetWriteBuff();
	std::vector<DataBuff*>& GetWriteList() {return vWrite_;}

	int ParasePacket(CMessage **Msg);

private:

	void 	 AddWriteNum(uint32_t num);
private:
	uint32_t nReadable_;
	uint32_t nWritable_;
	CMemPool* mempool_;
	std::vector<DataBuff*> vRead_;
	std::vector<DataBuff*> vWrite_;		
};

class CMemPool
{  
public:
	CMemPool() ;
	~CMemPool();

	DataBuff* Alloc(uint32_t size);
	void Free(DataBuff* Data);

private:

	void InitBuffList();
	void ReleaseBuffList();

	std::list<DataBuff*> BuffList_;
};

#endif
