/*
 * dispatcher.h
 *
 *  Created on: 2015年1月26日
 *      Author: root
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <functional>

#include "common/header.h"
#include "common/socketserver.h"

typedef function<int (void)> MessageCallback;

class Dispatcher : public SocketServer
{
public:

	SINGLETON_DECLARATION(Dispatcher)

	Dispatcher();
	virtual ~Dispatcher();

	void Register(int command, MessageCallback &callback);

private:
	map<int, MessageCallback> m_mapCallback;
};

#endif /* DISPATCHER_H_ */
