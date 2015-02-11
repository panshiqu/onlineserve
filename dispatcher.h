/*
 * dispatcher.h
 *
 *  Created on: 2015年1月26日
 *      Author: root
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "base/header.h"
#include "proto/protocol.h"
#include "base/socketserver.h"
#include "base/socketdelegate.h"

typedef function<int (char *pMessage, int nLength, SocketClient *pClient)> Callback;

class Dispatcher : SocketDelegate
{
private:
	Dispatcher();
	virtual ~Dispatcher();

public:
	SINGLETON(Dispatcher)
	void Dispatch(void);

public:
	// Implementation Socket Connected
	void OnConnected(SocketClient *pClient = NULL);

	// Implementation Socket Disconnected
	void OnDisconnected(SocketClient *pClient = NULL);

	// Implementation Socket Connect Failed
	void OnConnectFailed(SocketClient *pClient = NULL);

	// Implementation Socket Receive Message
	void OnMessage(char *pMessage, SocketClient *pClient = NULL);

	// Insert Map Register Callback
	void RegisterCallback(int nCommand, const Callback &cb)	{ m_mapCallback[nCommand] = cb; }

private:
	map<int, Callback> m_mapCallback;
};

#endif /* DISPATCHER_H_ */
