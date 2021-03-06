/*
 * agent.h
 *
 *  Created on: 2015年2月11日
 *      Author: root
 */

#ifndef AGENT_H_
#define AGENT_H_

#include "online.h"
#include "base/header.h"
#include "proto/protocol.h"
#include "base/socketclient.h"

class Agent {
public:
	Agent(int nID, SocketClient *pClient);
	virtual ~Agent();

public:
	void SendChat(char *pMessage, int nLength, int nCommand);		// 发送聊天信息

public:
	int GetID(void)					{ return m_nID; }
	int GetType(void)					{ return m_nType; }
	int GetStatus(void)				{ return m_nStatus; }
	SocketClient *GetClient(void)	{ return m_pClient; }

	void SetID(int nID)				{ m_nID = nID; }
	void SetType(int nType)			{ m_nType = nType; }
	void SetStatus(int nStatus)	{ m_nStatus = nStatus; }

private:
	int m_nID = 0;								// 座席编号
	int m_nType = AGENT_TYPE_AGENT;		// 座席类型
	int m_nStatus = AGENT_STATUS_FREE;	// 座席状态
	SocketClient *m_pClient = NULL;		// 座席套接字
};

#endif /* AGENT_H_ */
