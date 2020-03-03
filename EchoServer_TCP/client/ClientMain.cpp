#include <iostream>
#include <WinSock2.h>
#include <thread>

#include "GameClient.h"

#pragma comment(lib, "ws2_32")

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 9000
#define MAX_BUFF	1024

using namespace std;

void CommandConsole()
{
	GameClient client;

	while (true)
	{
		client.DoCommand();

	}
}

int main()
{
	GameClient client;
	if (false == client.Connect())
	{
		return -1;
	}
	
	std::thread CommandThread(&CommandConsole);
	std::thread ReceiveThread(&GameClient::OnReceive, &client);

	CommandThread.join();
	ReceiveThread.join();

	return 0;
}