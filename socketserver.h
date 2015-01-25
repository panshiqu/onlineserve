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

	bool Init(int nPort);
	void Release(void);
	void Run(void);

private:
	int m_nSocket;
	vector<SocketClient *> m_vClient;
};

#endif /* SOCKETSERVER_H_ */
