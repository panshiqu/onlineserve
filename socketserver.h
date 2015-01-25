/*
 * socketserver.h
 *
 *  Created on: 2015年1月24日
 *      Author: root
 */

#ifndef SOCKETSERVER_H_
#define SOCKETSERVER_H_

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <vector>
#include <iostream>
using namespace std;

class SocketClient;
class SocketServer {
public:
	SocketServer();
	virtual ~SocketServer();

	virtual void OnMessage(SocketClient *pClient, char *pBuffer);
	virtual void OnConnected(SocketClient *pClient);
	virtual void OnDisconnected(SocketClient *pClient);

	bool Init(int nPort);
	void Run(void);

	void Register(SocketClient *pClient);
	void UnRegister(SocketClient *pClient);

private:
	bool SetNonblock(int nSocket);
	void Close(int nSocket);

private:
	int m_nSocket;
	vector<SocketClient *> m_vClient;
};

#endif /* SOCKETSERVER_H_ */
