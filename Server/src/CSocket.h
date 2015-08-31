#ifndef _CSOCKET_H
#define _CSOCKET_H

class CSocket
{  
public:

	CSocket(int fd);
	~CSocket();

	int Get_Fd() const {return fd_;}

	void Shutdown();

	inline void Set_Nodelay();
	inline void Set_Linger();
	inline void Set_KeepAlive();
private:
	int fd_;

};

#endif
