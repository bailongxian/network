#ifndef _CONNECTOR_H_
#define _CONNECTOR_H_

class CConnector
{
public:
	CConnector();
	~CConnector();

	static int Connect_Host(const char* strip, unsigned short port);
};

#endif
