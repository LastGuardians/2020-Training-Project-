#include "SocketObj.h"
#include <iostream>

#define MAX_BUFF 1024

using namespace std;


int main()
{
	SocketObj* socket = new SocketObj;

	cout << "server start" << endl;

	if (false == socket->InitSocket())
	{
		cout << "InitSocket() failed" << endl;
		return -1;
	}

	if (false == socket->Bind())
	{
		cout << "Bind() failed" << endl;
		return -1;
	}

	if (false == socket->Listen())
	{
		cout << "Listen() failed" << endl;
		return -1;
	}
		
	while (true)
	{
		cout << "Accept wait..." << endl;
		SOCKET* acceptsocket = socket->Accept();
		if (nullptr == acceptsocket)
		{
			return -1;
		}

		char recvbuff[MAX_BUFF];
		int recvlen;
		
		while (recvlen = recv(*acceptsocket, recvbuff, MAX_BUFF, 0))
		{
			if (SOCKET_ERROR == recvlen)
			{
				cout << "recv data not exist." << endl;
				break;
			}
			cout << "recvbuff : " << recvbuff << endl;
			int ret = send(*acceptsocket, recvbuff, strlen(recvbuff), 0);			
		}
	}

	socket->CloseSocket();	
	return 0;
}