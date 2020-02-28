#include "SocketObj.h"

SocketObj::SocketObj()
{
	_socket = 0;
	_acceptsocket = 0;
}

SocketObj::~SocketObj()
{
	CloseSocket();
}

bool SocketObj::InitSocket()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	
	if (INVALID_SOCKET == _socket)
	{
		CloseSocket();
		return false;
	}

	return true;
}

bool SocketObj::Bind()
{
	SOCKADDR_IN listenAddr;
	listenAddr.sin_family = AF_INET;
	listenAddr.sin_port = htons(9000);
	listenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = ::bind(_socket, (SOCKADDR*)&listenAddr, sizeof(listenAddr));
	if (SOCKET_ERROR == ret)
	{
		CloseSocket();
		return false;
	}

	return true;
}

bool SocketObj::Listen()
{
	int ret = listen(_socket, SOMAXCONN);
	if (SOCKET_ERROR == ret || INVALID_SOCKET == _socket)
	{
		CloseSocket();
		return false;
	}

	return true;
}

void SocketObj::CloseSocket()
{
	closesocket(_socket);
	_socket = INVALID_SOCKET;
	std::cout << "socket close." << std::endl;
	WSACleanup();
}

SOCKET SocketObj::Accept()
{
	SOCKADDR_IN acceptAddr;
	int addrsize = sizeof(acceptAddr);

	_acceptsocket = accept(_socket, (sockaddr*)&acceptAddr, &addrsize);
	if (INVALID_SOCKET == _acceptsocket)
	{
		return NULL;
	}

	return _acceptsocket;
}

