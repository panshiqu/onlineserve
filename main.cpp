/*
 * main.cpp
 *
 *  Created on: 2015年1月21日
 *      Author: root
 */


#include <thread>
#include <iostream>

#include "socketbase.h"
#include "socketserver.h"

using namespace std;

void thr_fn1(void)
{
	cout << "thr_fn1" << endl;

	SocketServer Srv;
	if (!Srv.Init(11111)) Srv.Release();

	Srv.Run();

//	SocketBase Srv;
//	Srv.Create();
//	Srv.Bind(11111, "127.0.0.1");
//	Srv.Listen(1);
//
//	while (true)
//	{
//		SocketBase Clt;
//		struct sockaddr_in addr;
//		socklen_t length = sizeof(struct sockaddr_in);
//		if (Srv.Accept(Clt, (struct sockaddr *)&addr, &length))
//		{
//			cout << "IP: " << inet_ntoa(addr.sin_addr) << "Port: " << addr.sin_port << endl;
//
//			char szBuf[1024];
//			Clt.Receive(szBuf, 1024);
//			cout << szBuf << endl;
//
//			Clt.Send("Hello World!", sizeof("Hello World!"));
//
//			Clt.Close();
//		}
//	}
}

void thr_fn2(void)
{
	cout << "thr_fn2" << endl;
}

int main(void)
{
	thread t1{bind(thr_fn1)};
//	thread t2{bind(thr_fn2)};

	t1.join();
//	t2.join();
	return 0;
}

