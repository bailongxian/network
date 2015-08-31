#include "CSocket.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>


CSocket::CSocket(int fd):fd_(fd)
{
	Set_Nodelay();
	Set_Linger();
	Set_KeepAlive();
}


CSocket::~CSocket()
{  
	close(fd_);
}

void CSocket::Shutdown()
{  
	shutdown(fd_, SHUT_WR);
}

inline void CSocket::Set_Nodelay()
{  
	const int on = 1;
	setsockopt(fd_, SOL_TCP, TCP_NODELAY, &on, sizeof(int));
}

inline void CSocket::Set_Linger()
{  
	struct linger linger = {1, 1};
	setsockopt(fd_, SOL_SOCKET, SO_LINGER, (const char*)&linger, sizeof(linger));
}

inline void CSocket::Set_KeepAlive()
{
	const int on = 1;
	setsockopt(fd_, SOL_SOCKET, SO_KEEPALIVE, &on, sizeof(int));
}