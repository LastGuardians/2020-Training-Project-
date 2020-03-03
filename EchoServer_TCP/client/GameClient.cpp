#include <iostream>
#include <WinSock2.h>
#include "GameClient.h"

#pragma comment(lib, "ws2_32")

#define MAX_BUFF	1024
#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 9000

using namespace std;

GameClient::GameClient() : _socketobj(-1)
{	
}

GameClient::~GameClient()
{
	_socketobj = -1;
	closesocket(_socketobj);
	WSACleanup();
}

bool GameClient::Connect()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	_socketobj = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == _socketobj)
	{
		return false;
	}

	SOCKADDR_IN listenAddr;
	listenAddr.sin_family = AF_INET;
	listenAddr.sin_port = htons(SERVER_PORT);
	listenAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	int ret = connect(_socketobj, (SOCKADDR*)& listenAddr, sizeof(listenAddr));
	if (SOCKET_ERROR == ret)
	{
		cout << "connect() failed" << endl;
		return false;
	}

	cout << "connect success!" << endl;

	return true;
}

void GameClient::OnReceive()
{
	while (true)
	{
		char sendbuff[MAX_BUFF];

		if (recv(_socketobj, sendbuff, sizeof(sendbuff), 0))
		{	
			cout << "받은 메세지 : " << sendbuff << endl;
		}
	}
}

void GameClient::DoCommand()
{
	char sendbuff[MAX_BUFF];

	cout << "보낼 메세지 입력 : ";
	cin >> sendbuff;

	::send(_socketobj, sendbuff, sizeof(sendbuff), 0);
}
