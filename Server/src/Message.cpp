#include "Message.h"
#include "Common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

CMessage::CMessage(int type,unsigned short  size)
:fd_(-1),
max_(size + PACK_HEAD_SIZE),
len_(PACK_HEAD_SIZE),
cur_(PACK_HEAD_SIZE)
{
	data_ = (char*)malloc(size + PACK_HEAD_SIZE);
	memcpy(data_ + sizeof(unsigned short), &type, sizeof(type));
}

CMessage::~ CMessage()
{
	if(max_)
		free(data_);
}

bool CMessage::WriteBuff(const char * src,unsigned short len)
{
	if(len == 0) return false;
	
	bool expand = false;
	while(len_ + len > max_)
	{
		max_ <<= 1;
		expand = true;
	}
	if(expand)
	{
		void* ptr = realloc(data_, max_);
		data_ = (char*)ptr;
	}

	memcpy(data_ + len_, src, len);
	len_ += len;
	return true;
}

void CMessage::ReadBuff(char * des,unsigned short len)
{
	if(len + cur_ <= len_)
	{
		memcpy(des, data_ +cur_, len);
		cur_ += len;
	}
}

bool CMessage::Write(char c)
{
	return WriteBuff((char*)&c, sizeof(c));
}

bool CMessage::Write(short s)
{
	return WriteBuff((char*)&s, sizeof(s));
}

bool CMessage::Write(int n)
{
	return WriteBuff((char*)&n, sizeof(n));
}

bool CMessage::Write(long l)
{
	return WriteBuff((char*)&l, sizeof(l));
}

bool CMessage::Write(long long ll)
{
	return WriteBuff((char*)&ll, sizeof(ll));
}

bool CMessage::Write(void * data,unsigned short len)
{
	return WriteBuff((char*)data_, len);
}

bool CMessage::Write(const char* str)
{
	short str_len = strlen(str);
	Write(str_len);
	return WriteBuff(str, str_len);
}

char CMessage::Readchar()
{
	char c;
	ReadBuff((char*)&c, sizeof(c));
	return c;
}

short CMessage::Readshort()
{
	short s;
	ReadBuff((char*)&s, sizeof(s));
	return s;
}

int  CMessage::Readint()
{
	int n;
	ReadBuff((char*)&n, sizeof(n));
	return n;
}

long CMessage::Readlong()
{
	long l;
	ReadBuff((char*)&l, sizeof(l));
	return l;
}

long long CMessage::Readlonglong()
{
	long long ll;
	ReadBuff((char*)&ll, sizeof(ll));
	return ll;
}

void CMessage::ReadBulk(void * des,unsigned short len)
{
	ReadBuff((char*)des,len);
}

char* CMessage::Readstr(char* des, unsigned short len)
{
	int strlen = Readshort();
	int min = MIN(strlen, len-1);
	ReadBuff(des, min);
	printf("min=%d\n", min);
	des[min] = '\0';
	return des;
}

void CMessage::SetSendFlag()
{
	memcpy(data_, &len_, sizeof(len_));
	cur_ = 0;
}


void CMessage::PrintData()
{
	int cur = cur_, len = len_, max = max_;
	printf("cur = %d len = %d max = %d\n", cur, len, max);
	for(unsigned short i = 0; i < len_; i++)
	{
		char c = data_[i];
		printf("%d\t", c);
	}
	printf("\n");
}

CMessage* CMessageAlloctor::AllocMSG(int type,unsigned short size)
{
	return new CMessage(type,size);
}

void CMessageAlloctor::FreeMSG(CMessage ** Msg)
{
	delete *Msg;
}

CMessage* CMessageAlloctor::CopyMSG(CMessage * Msg)
{
	CMessage *NewMsg = AllocMSG(Msg->GetType(), Msg->GetLen());
	memcpy(NewMsg->data_, Msg->data_, Msg->GetLen());
	NewMsg->len_ = Msg->GetLen();
	return NewMsg;	
}


