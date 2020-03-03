#pragma once
class GameClient
{
public:
	GameClient();
	virtual ~GameClient();

	bool Connect();
	void OnReceive();
	void DoCommand();
	void isQuit();

private:
	SOCKET _socketobj;
};

