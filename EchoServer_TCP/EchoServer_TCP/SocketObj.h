#pragma once
#pragma comment(lib, "ws2_32")

#include <iostream>
#include <WinSock2.h>

class SocketObj
{
public:
	SocketObj();
	virtual ~SocketObj();

	bool InitSocket();
	bool Bind();
	bool Listen();
	void CloseSocket();
	SOCKET* Accept();

private:
	SOCKET _socket;
	SOCKET _acceptsocket;
};