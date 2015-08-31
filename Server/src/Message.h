#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#define	PACK_LEN		sizeof(unsigned short)
#define PACK_HEAD_SIZE 	PACK_LEN+ sizeof(int)
#define MIN_MSG_LEN		128
#define	DEFAUL_MSG_LEN 	256 - PACK_HEAD_SIZE
#define MAX_MSG_LEN		65535

class CMessage
{
public:
	CMessage(int type = 0, unsigned short size = DEFAUL_MSG_LEN);
	~CMessage();

	bool Write(char c);
	bool Write(short s);
	bool Write(int n);
	bool Write(long l);
	bool Write(long long ll);
	bool Write(void* data, unsigned short len);
	bool Write(const char* str);

	char  Readchar();
	short Readshort();
	int   Readint();
	long  Readlong();
	long long Readlonglong();
	void  ReadBulk(void* src, unsigned short len);
	char* Readstr(char* des, unsigned short len);

	int   GetFd() const {return fd_;}
	void  SetFd(int fd) {fd_ = fd;}
	int   GetLen() const {return len_;}
	void  SetLen(unsigned short len) {len_ = len;}
	void  SetSendFlag();
	void  Reset() {cur_ = 0;}

	int   GetType() const {return ((int*)(data_+sizeof(unsigned short)))[0];}

	void  PrintData();
	
	friend class CConnect;
	friend class CBuffManage;
	friend class CMessageAlloctor;
private:
	bool WriteBuff(const char* src, unsigned short len);
	void ReadBuff(char* des, unsigned short len);
	
private:
	int 		   fd_;
	unsigned short max_;
	unsigned short len_;
	unsigned short cur_;
	char*		   data_;

};


class CMessageAlloctor
{

public:
	CMessageAlloctor() {};
	~CMessageAlloctor() {};

	static CMessage* AllocMSG(int type = 0, unsigned short size = DEFAUL_MSG_LEN);
	static void	FreeMSG(CMessage **Msg);
	static CMessage* CopyMSG(CMessage *Msg);
};

#endif