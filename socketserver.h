/*
 * socketserver.h
 *
 *  Created on: 2015年1月24日
 *      Author: root
 */

#ifndef SOCKETSERVER_H_
#define SOCKETSERVER_H_

#include <vector>
#include <iostream>
using namespace std;

#include "socketbase.h"

class SocketClient;
class SocketServer : public SocketBase
{
public:
	SocketServer();
	virtual ~SocketServer();

	virtual void OnMessage(SocketClient *pClient, char *pBuffer);
	virtual void OnConnected(SocketClient *pClient);
	virtual void OnDisconnected(SocketClient *pClient);

	bool Init(int nPort);
	void Run(void);

private:
	vector<SocketClient *> m_vClient;
};

#endif /* SOCKETSERVER_H_ */
