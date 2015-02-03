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


}

void thr_fn2(void)
{
	cout << "thr_fn2" << endl;
}

void thr_fn3(void)
{
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

struct TEST {
	int nLength;
	char szTest[8];
};

int main(void)
{
//	thread t1{bind(thr_fn1)};
//	thread t2{bind(thr_fn2)};

//	t1.join();
//	t2.join();

//	TEST tt;
//	memcpy(tt.szTest, "Hello", sizeof("Hello"));
//	tt.nLength = 9;
//
//
//	int nSocket = socket(AF_INET, SOCK_STREAM, 0);
//	struct sockaddr_in addr;
//	addr.sin_family = AF_INET;
//	addr.sin_port = htons(11111);
//	inet_pton(AF_INET, "127.0.0.1", &(addr.sin_addr));
//	connect(nSocket, (struct sockaddr *)&addr, sizeof(addr));
//
//	while (true)
//	{
//		send(nSocket, (char *)&tt, tt.nLength, 0);
//
//		char szBuf[128];
//		memset(szBuf, 0, 128);
//		recv(nSocket, szBuf, 128, 0);
//		cout << szBuf <<endl;
//		sleep(1);
//	}

	SocketServer Srv;
	Srv.Init(11111);

	Srv.Run();

	return 0;
}

