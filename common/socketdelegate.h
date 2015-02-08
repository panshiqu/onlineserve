/*
 * socketdelegate.h
 *
 *  Created on: 2015年2月8日
 *      Author: root
 */

#ifndef SOCKETDELEGATE_H_
#define SOCKETDELEGATE_H_

#include "header.h"

class SocketClient;
class SocketDelegate {
public:
	SocketDelegate();
	virtual ~SocketDelegate();

	virtual void OnMessage(char *pBuffer, SocketClient *pClient = NULL) {}
	virtual void OnConnected(SocketClient *pClient = NULL) {}
	virtual void OnDisconnected(SocketClient *pClient = NULL) {}
};

#endif /* SOCKETDELEGATE_H_ */
