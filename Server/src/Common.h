#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>

typedef void (*ReadWriteCallBack) (void*);
typedef void (*ConnectCallBack)(void*);
typedef void (*CloseCallBack)(void*);

#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define UNUSE(v) ((void*)(v))


enum PACKET_TYPE
{
	P_CONNECT = 0,
	P_READ	  = 1,
	P_WRITE   = 2,
	P_CLOSE	  = 3
};

#endif
