/*
 * agentmain.h
 *
 *  Created on: 2015年2月11日
 *      Author: root
 */

#ifndef AGENTMAIN_H_
#define AGENTMAIN_H_

#include "online.h"
#include "base/header.h"
#include "proto/protocol.h"
#include "base/socketclient.h"

class Agent;
class AgentMain
{
private:
	AgentMain();
	virtual ~AgentMain();

public:
	SINGLETON(AgentMain)

	bool OnDisconnected(SocketClient *pClient);			// 连接断开

	// 座席操作相关
	bool FindAgent(int nID);									// 查找座席
	bool DeleteAgent(int nID);									// 删除座席
	list<Agent *>::iterator GetAgent(int nID);			// 获取座席
	Agent *InsertAgent(int nID, SocketClient *pClient);// 增加座席
	Agent *AllocAgent(void);									// 分配座席

	int SendChat(int nID, char *pMessage, int nLength);// 发送聊天信息

public:
	int GetMaxID(void)	{ return ++m_nMaxID; }

private:
	int m_nMaxID = 10000;		// 客户编号
	list<Agent *> m_lAgents;	// 座席列表
};

#endif /* AGENTMAIN_H_ */
