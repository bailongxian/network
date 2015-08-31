#ifndef _ACCEPT__H_
#define	_ACCEPT__H_

#include <stdint.h>

class CAcceptor
{  
public:
	CAcceptor(const char* host, uint16_t port);
	~CAcceptor();

	int Init_Accept();
	int Start_Accept();
	int Exit_Accept();
private:
	int 		listenfd_;
	const char* strHost_;
	uint16_t 	nport_;

};

#endif
