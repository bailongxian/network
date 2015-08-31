#ifndef _READBUFF_H_
#define _READBUFF_H_

#include <vector>
#include <string.h>
#include <stdlib.h>

class CMessage;

class CReadBuff
{

public:
	CReadBuff();
	~CReadBuff();

struct Buff
{
	int cur;
	int len;
	int max;
	char* data;

	Buff():cur(0), len(0),max(8192) 
	{
		data = (char*)malloc(max);
	}

	~Buff()
	{
		free(data);
	}
};


Buff* Getbuff();
int ParaseMsg(CMessage **Msg);
void SetReadable(int num) {nReadable_ = num;}
int  GetReadable() const {return nReadable_;}
void ReleaseBuff(unsigned short num);
void PrintInfo();

private:
	std::vector<Buff*> ListBuff_;
	int nReadable_;
	
};
#endif