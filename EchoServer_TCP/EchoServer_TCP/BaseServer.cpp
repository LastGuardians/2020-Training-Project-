#include "BaseServer.h"
#include <thread>
#define MAX_BUFF 1024

using namespace std;

BaseServer::BaseServer()
{
}

BaseServer::~BaseServer()
{
}

bool BaseServer::Open()
{
	std::cout << "server start" << std::endl;
	
	if (false == _socketobj.InitSocket())
	{
		cout << "InitSocket() failed" << endl;
		return false;
	}

	if (false == _socketobj.Bind())
	{
		cout << "Bind() failed" << endl;
		return false;
	}

	if (false == _socketobj.Listen())
	{
		cout << "Listen() failed" << endl;
		return false;
	}

	BeginThread();
	
	return true;
}

void BaseServer::BeginThread()
{
	std::thread acceptthread(&BaseServer::AccpetThread, this);
	std::thread workerthread(&BaseServer::WorkerThread, this);

	acceptthread.join();
	workerthread.join();
}

void BaseServer::AccpetThread()
{
	int clientid = 0;
	while (true)
	{
		cout << "Accept wait..." << endl;
		_mSocket = _socketobj.Accept();
		if (NULL == _mSocket)
		{
			cout << "Accept failed" << endl;			
		}

		cout << "clientid : " << clientid++ << " connect success" << endl;

		/*char recvbuff[MAX_BUFF];
		int recvlen;

		if (::recv(_mSocket, recvbuff, MAX_BUFF, 0))
		{
			cout << "recv data : " << recvbuff << endl;
			int ret = send(_mSocket, recvbuff, strlen(recvbuff), 0);
		}*/
	}

	_socketobj.CloseSocket();
}

void BaseServer::WorkerThread()
{
	char recvbuff[MAX_BUFF];
	int recvlen;

	while (recvlen = ::recv(_mSocket, recvbuff, MAX_BUFF, 0))
	{		
		if (recvlen > 0)
		{
			cout << "recv data : " << recvbuff << endl;
			int ret = send(_mSocket, recvbuff, strlen(recvbuff), 0);
		}
	}
}
