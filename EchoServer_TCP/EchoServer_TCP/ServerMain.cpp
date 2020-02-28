#include "SocketObj.h"
#include "BaseServer.h"
#include <iostream>
#include <thread>

int main()
{
	BaseServer server;
	if (false == server.Open())
	{
		return -1;
	}

	return 1;
}