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
	SocketServer(SocketDelegate *pDelegate = NULL);
	virtual ~SocketServer();

	bool Init(int nPort);
	void Run(void);

private:
	SocketBase m_hSocket;
	SocketDelegate *m_pDelegate;
	vector<SocketClient *> m_vClient;
};

#endif /* SOCKETSERVER_H_ */
