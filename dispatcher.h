/*
 * dispatcher.h
 *
 *  Created on: 2015年1月26日
 *      Author: root
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <functional>

#include "proto/protocol.h"
#include "common/header.h"
#include "common/socketserver.h"
#include "common/socketclient.h"

typedef function<void (SocketClient *pClient, char *pBuffer)> Callback;

class Dispatcher
{
public:

	SINGLETON_DECLARATION(Dispatcher)

private:
	Dispatcher();
	virtual ~Dispatcher();

public:
	void OnMessage(SocketClient *pClient, char *pBuffer);
	void OnConnected(SocketClient *pClient);
	void OnDisconnected(SocketClient *pClient);

	void RegisterCallback(void);

private:
	map<int, Callback> m_mapCallback;
};

#endif /* DISPATCHER_H_ */
