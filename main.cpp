/*
 * main.cpp
 *
 *  Created on: 2015年1月21日
 *      Author: root
 */


#include <thread>
#include <iostream>

#include "socketserver.h"
#include "socketclient.h"

using namespace std;

class MySrv : public SocketServer
{
public:
	MySrv() {};
	virtual ~MySrv() {};

	void OnMessage(SocketClient *pClient, char *pBuffer)
	{
		cout << "Server OnMessage." << endl;

		cout << &pBuffer[sizeof(Header)] << endl;
		delete pBuffer;

		char szBuffer[7];
		memcpy(szBuffer, "welcome", 7);
		pClient->Send(szBuffer, 7);
	}

	void OnConnected(SocketClient *pClient)
	{
		cout << "OnConnected." << endl;
	}

	void OnDisconnected(SocketClient *pClient)
	{
		cout << "OnDisconnected." << endl;
	}
};

class MyClt : public SocketClient
{
public:
	MyClt() {};
	virtual ~MyClt() {};

	void OnMessage(char *pBuffer)
	{
		cout << "Client OnMessage." << endl;

		cout << &pBuffer[sizeof(Header)] << endl;
		delete pBuffer;
	}
};

void thr_fn1(void)
{
	cout << "thr_fn1" << endl;

	MySrv srv;
	srv.Init(11111);
	srv.Run();
}

void thr_fn2(void)
{
	cout << "thr_fn2" << endl;

	MyClt clt;
	clt.Init("127.0.0.1", 11111);

	while (true) {
		char szBuffer[5];
		memcpy(szBuffer, "hello", 5);
		clt.Send(szBuffer, 5);

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

