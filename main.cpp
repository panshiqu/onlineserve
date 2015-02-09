/*
 * main.cpp
 *
 *  Created on: 2015年1月21日
 *      Author: root
 */


#include <thread>
#include <iostream>

#include "proto/protocol.h"
#include "base/socketserver.h"
#include "base/socketclient.h"

#include "dispatcher.h"
#include "processer.h"

using namespace std;

class MySrv
{
public:
	MySrv() {};
	virtual ~MySrv() {};

	void OnMessage(SocketClient *pClient, char *pBuffer)
	{
		cout << "Server OnMessage." << endl;

		cout << &pBuffer[sizeof(Header)] << endl;
		delete pBuffer;

//		char szBuffer[7];
//		memcpy(szBuffer, "welcome", 7);
//		pClient->Send(szBuffer, 7);
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

//	Dispatcher::GetInstance().RegisterCallback();
//	Dispatcher::GetInstance().Init(11111);
//	Dispatcher::GetInstance().Run();
}

void thr_fn2(void)
{
	cout << "thr_fn2" << endl;

	MyClt clt;
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

typedef function<void (void)> CB;

class A
{
public:
	static A &GetInstance()
	{
		static A instance;
		return instance;
	}

	void A_Func()
	{
		cout << "A_Func" << endl;
	}
};

class B
{
public:
	void Register()
	{
		cb = bind(&A::A_Func, &A::GetInstance());
	}

	void B_Func()
	{
		cb();
	}

	//A a;
	CB cb;
};

int main(void)
{
	thread t1{bind(thr_fn1)};
	sleep(1);
	thread t2{bind(thr_fn2)};

	t1.join();
	t2.join();

//	B b;
//	b.Register();
//	b.B_Func();

	return 0;
}

