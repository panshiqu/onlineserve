/*
 * agentdelegate.h
 *
 *  Created on: 2015年2月11日
 *      Author: root
 */

#ifndef DEMO_AGENT_AGENTDELEGATE_H_
#define DEMO_AGENT_AGENTDELEGATE_H_

#include "../../base/header.h"
#include "../../proto/protocol.h"
#include "../../base/socketclient.h"
#include "../../base/socketdelegate.h"

class AgentDelegate : public SocketDelegate
{
public:
	AgentDelegate();
	virtual ~AgentDelegate();

	// Implementation Socket Connected
	void OnConnected(SocketClient *pClient = NULL);

	// Implementation Socket Disconnected
	void OnDisconnected(SocketClient *pClient = NULL);

	// Implementation Socket Connect Failed
	void OnConnectFailed(SocketClient *pClient = NULL);

	// Implementation Socket Receive Message
	void OnMessage(char *pMessage, SocketClient *pClient = NULL);
};

#endif /* DEMO_AGENT_AGENTDELEGATE_H_ */
