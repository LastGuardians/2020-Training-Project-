#pragma once
#include "SocketObj.h"

class BaseServer
{
public:
	BaseServer();
	virtual ~BaseServer();

	bool Open();
	void BeginThread();	

private:
	SocketObj	_socketobj;
	SOCKET		_mSocket;

	void AccpetThread();
	void WorkerThread();
};

