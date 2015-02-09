/*
 * main.cpp
 *
 *  Created on: 2015年1月21日
 *      Author: root
 */


#include <thread>
#include <iostream>

#include "dispatcher.h"
#include "base/socketclient.h"
#include "proto/protocol.h"

using namespace std;

class MyClt : public SocketDelegate
{
public:
	MyClt() {};
	virtual ~MyClt() {};

	void OnMessage(char *pMessage, SocketClient *pClient)
	{
		cout << "Client OnMessage." << endl;
	}

	void OnConnected(SocketClient *pClient)
	{
		cout << "Client OnConnected." << endl;
	}

	virtual void OnDisconnected(SocketClient *pClient)
	{
		cout << "Client OnDisconnected." << endl;
	}

	virtual void OnConnectFailed(SocketClient *pClient = NULL)
	{
		cout << "Client OnConnectFailed." << endl;
	}
};

void thr_fn1(void)
{
	cout << "thr_fn1" << endl;
	Dispatcher::GetInstance().Dispatch();
}

void thr_fn2(void)
{
	cout << "thr_fn2" << endl;

	MyClt delegate;
	SocketClient clt(&delegate);
	clt.Init("127.0.0.1", 11111);

	while (true) {
		Login login;
		login.set_agentid(1001);

		string str;
		login.SerializeToString(&str);

		clt.SendMessage(str.c_str(), str.length(), 2);

		clt.Run();
		sleep(5);
	}
}

int main(void)
{
	thread t1{bind(thr_fn1)};
	sleep(1);
	thread t2{bind(thr_fn2)};

	t1.join();
	t2.join();

	return 0;
}

