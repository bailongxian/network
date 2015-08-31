#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<errno.h>
#include<pthread.h>
#include<string.h>
#include<map>
#include<sys/uio.h>
#include<sys/epoll.h>
#include "Message.h"
#include "ReadBuff.h"

#define  TEST_NUM	0x1111
#define  THREAD_NUM	0x01

int socket_connect();
int send_msg(int fd, CMessage *Msg, int num = 1);
int recv_msg(int fd, CReadBuff* Readbuff);

std::map<int, CReadBuff*> g_readBuff;

CReadBuff* GetReadBuff(int fd)
{
	return g_readBuff[fd];
}

int num = 0;


void* read_io_loop(void* data)
{  
	int fd = (int)data;
	int count = 0;
	CReadBuff *pBuff = GetReadBuff(fd);
	while(1)
	{  
		int n = recv_msg(fd, pBuff);
		if(n < 0)
		{
			printf("read error = %s\n", strerror(errno));
			continue;
		}
		if(n == 0)
		{
			printf("server has close connect\n");
			close(fd);
			break;
		}

		while(1)
		{
			CMessage *Msg = NULL;
			int Ret = pBuff->ParaseMsg(&Msg);
			if(Ret < 1 || Msg == NULL)
				break;

			switch(Msg->GetType())
			{
				case 1:
				{
					char data[128];
					Msg->Readstr(data,sizeof(data));
					printf("msg_len = %d data=%s\n", n, data);
				}
				break;
			
				case 2:
				{
					int sum = Msg->Readint();
					count++;
					printf("fd = %d sum = %d count = %d\n",fd, sum, count);
				}
				break;
			}
			CMessageAlloctor::FreeMSG(&Msg);

		}

		if(num - 1 <= count)
		{
			printf("loop exit\n");
			break;
		}		
	}
	return NULL;
}

void Update_Event(int efd, int fd, int opt, int ev)
{
	struct epoll_event event;
	bzero(&event, sizeof(event));
	event.data.fd = fd;
	event.events = ev;
	int ret = epoll_ctl(efd, opt, fd, &event);
//	printf("epl_ctl %s\n", strerror(errno));
}

int main(int argc, char* argv[])
{  
	if(argc < 4)
		return -1;
	printf("client start\n");
	int type = atoi(argv[1]);
	num = atoi(argv[2]);
	int clientnum = atoi(argv[3]);
	printf("num = %d  clientnum = %d\n", num, clientnum);

	int efd = epoll_create1(0);
	CMessage *msg = CMessageAlloctor::AllocMSG(type);
	int n1 = 2, n2 = 6;
	msg->Write(n1);
	msg->Write(n2);
	std::map<int, int> map_count;
	for(int i = 0; i < clientnum; i++)
	{
		int fd = socket_connect();
		Update_Event(efd,fd,EPOLL_CTL_ADD, EPOLLIN|EPOLLOUT);
		map_count[fd];
		g_readBuff[fd] = new CReadBuff();
	}

	struct epoll_event evList[1024];
	while(1)
	{
		int active = epoll_wait(efd, &evList[0], 1024, 1000);
		printf("acitve = %d\n", active);
		if(active < 0)
			printf("err %s\n", strerror(errno));
		if(map_count.empty())
			break;
		for(int i = 0; i < active; i++)
		{
			int active_event = evList[i].events;
			int active_fd	 = evList[i].data.fd;
			CReadBuff *pBuff = GetReadBuff(active_fd);
			if(active_event & (EPOLLIN | EPOLLRDHUP | EPOLLPRI))
			{  
				int n =  recv_msg(active_fd,pBuff);
				
				while(1)
				{
					CMessage *Msg = NULL;
					int Ret = pBuff->ParaseMsg(&Msg);
					if(Ret < 1 || Msg == NULL)
						break;

					switch(Msg->GetType())
					{
						case 1:
						{
							char data[128];
							Msg->Readstr(data,sizeof(data));
						//	printf("msg_len = %d data=%s\n", n, data);
						}
						break;
			
						case 2:
						{
							int sum = Msg->Readint();
							map_count[active_fd]++;
							int count = map_count[active_fd];
							printf("active_fd = %d sum = %d count = %d\n",active_fd, sum, count);
							if(count == num)
							{
								Update_Event(efd,active_fd,EPOLL_CTL_DEL,0);
								close(active_fd);
								map_count.erase(active_fd);
							}
						}
						break;
					}
				}
			}
			
			if(active_event & EPOLLOUT)
			{  
				send_msg(active_fd,msg, num);
				Update_Event(efd,active_fd,EPOLL_CTL_MOD,EPOLLIN);
			}
		}
	}		

	getchar();
	int fd = socket_connect();
	CMessage *ExitMsg = CMessageAlloctor::AllocMSG(3);
	send_msg(fd,ExitMsg,1);
	CMessageAlloctor::FreeMSG(&ExitMsg);	
}

void thead_num()
{
	/*	
		int clientfd[THREAD_NUM];
		pthread_t thid[THREAD_NUM];
		for(int i = 0; i < THREAD_NUM; i++)
		{	
			clientfd[i] = socket_connect();
			g_readBuff[clientfd[i]] = new CReadBuff();
		}
		for(int i = 0; i < THREAD_NUM; i++)
			pthread_create(&thid[i], NULL, read_io_loop, (void*)clientfd[i]);
	
		if(type != 1 && type != 2 && type != 3)
		{
		//	g_buff.PrintInfo();
			printf("type error\n");
			exit(0);
		}	
	
		CMessage *msg = CMessageAlloctor::AllocMSG(type);
		if(type == 1)
		{
			char buf[128] = {};
			scanf("%s", buf);							
			msg->Write(buf);
		}
		else if(type == 2)
		{
			int n1 = 2, n2 = 6;
				//	scanf("%d %d", &n1, &n2);
			msg->Write(n1);
			msg->Write(n2);
		}
		for(int i = 0; i < num; i++)
		{
			for(int j = 0; j < THREAD_NUM; j++)
				send_msg(clientfd[j],msg,1);
		}
	
		CMessageAlloctor::FreeMSG(&msg);
	
		for(int i = 0; i < THREAD_NUM; i++)
		{
			pthread_join(thid[i], NULL);
			close(clientfd[i]);
			printf("thread exit\n");
		}
	*/

}

int socket_connect()
{  
	int socket_fd = -1;
	struct 	sockaddr_in addr;
	if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("sock fail\n");

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8999);
	addr.sin_addr.s_addr = inet_addr("192.168.115.128");

	if(connect(socket_fd, (struct sockaddr*)&addr, sizeof(addr)))
	{  
		printf("connect %s\n", strerror(errno));
		return -1;
	}
	else
		return socket_fd;
}

int send_msg(int fd, CMessage* Msg, int num)
{  
	Msg->SetSendFlag();
//	Msg->PrintData();
	int i;
	for(i = 0; i < num; i++)
	{
		send(fd, Msg->GetData(), Msg->GetLen(), 0);
	}
	return 0;
}

int recv_msg(int fd, CReadBuff* Readbuff)
{  
	CReadBuff::Buff *buff = Readbuff->Getbuff();
	unsigned int len = buff->max - buff->len;
	char* data = buff->data + buff->len;
	int nreadable = Readbuff->GetReadable();
	int ntotal = 0;
	char tempbuf[65535];
	struct iovec iovec[2];
	iovec[0].iov_base = data;
	iovec[0].iov_len  = len;
	iovec[1].iov_base = tempbuf;
	iovec[1].iov_len  = sizeof(tempbuf);
	ssize_t n = readv(fd, &iovec[0], 2);
	if(n < 0)
		goto err;
	else if(n > len)
	{
		ntotal = n;
		buff->len += len;
		ntotal -= len;
		int count = 0;
		while(ntotal)
		{
			buff = Readbuff->Getbuff();
			len = buff->max - buff->len;
			int min = len < ntotal? len : ntotal;
			memcpy(buff->data+buff->len, tempbuf + count, min);
			count += min;
			ntotal -= min;
			buff->len += min;
		}
	}
	else
	{
		buff->len += n;
	}
	Readbuff->SetReadable(n+nreadable);
	return n;
err:
	return n;
}
