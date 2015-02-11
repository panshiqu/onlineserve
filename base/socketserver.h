/*
 * socketserver.h
 *
 *  Created on: 2015年1月24日
 *      Author: root
 */

#ifndef SOCKETSERVER_H_
#define SOCKETSERVER_H_

#include "socketbase.h"

class SocketClient;
class SocketDelegate;
class SocketServer {
public:
	SocketServer(SocketDelegate *pDelegate);
	virtual ~SocketServer();

	bool Init(int nPort);
	void Run(void);

private:
	SocketBase m_hSocket;						// 套接字句柄
	vector<SocketClient *> m_vClients;		// 收发套接字
	SocketDelegate *m_pDelegate = NULL;		// 套接字代理
};

#endif /* SOCKETSERVER_H_ */
