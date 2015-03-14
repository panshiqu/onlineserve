/*
 * socketdelegate.h
 *
 *  Created on: 2015年2月8日
 *      Author: root
 */

#ifndef SOCKETDELEGATE_H_
#define SOCKETDELEGATE_H_

#include <iostream>

class SocketClient;
class SocketDelegate {
public:
	SocketDelegate();
	virtual ~SocketDelegate();

	// Socket Connected
	virtual void OnConnected(SocketClient *pClient = NULL) {}

	// Socket Disconnected
	virtual void OnDisconnected(SocketClient *pClient = NULL) {}

	// Socket Connect Failed
	virtual void OnConnectFailed(SocketClient *pClient = NULL) {}

	// Socket Receive Message
	virtual void OnMessage(char *pMessage, SocketClient *pClient = NULL) {}
};

#endif /* SOCKETDELEGATE_H_ */
