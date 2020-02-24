#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32")

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 9000
#define MAX_BUFF	1024

using namespace std;

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET socketobj = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == socketobj)
	{
		return -1;
	}

	SOCKADDR_IN listenAddr;
	listenAddr.sin_family = AF_INET;
	listenAddr.sin_port = htons(SERVER_PORT);
	listenAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	int ret = connect(socketobj, (SOCKADDR*)&listenAddr, sizeof(listenAddr));
	if (SOCKET_ERROR == ret)
	{
		cout << "connect() failed" << endl;
		return -1;
	}

	cout << "connect success!" << endl;

	while (true)
	{
		char sendbuff[MAX_BUFF];

		cout << "보낼 메세지 입력 : ";
		cin >> sendbuff;

		int sendbyte = send(socketobj, sendbuff, sizeof(sendbuff), 0);
		if (SOCKET_ERROR == sendbyte)
		{
			cout << "send data not exist." << endl;
			break;
		}

		int recvlen;
		if (recvlen = recv(socketobj, sendbuff, sizeof(sendbuff), 0))
		{
			if (SOCKET_ERROR == recvlen || 0 == recvlen)
			{
				cout << "recv data not exist." << endl;
				continue;
			}
			cout << "받은 메세지 : " << sendbuff << endl;
		}
	}

	closesocket(socketobj);
	WSACleanup();

	return 0;
}