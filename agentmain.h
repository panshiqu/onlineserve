/*
 * agentmain.h
 *
 *  Created on: 2015年2月11日
 *      Author: root
 */

#ifndef AGENTMAIN_H_
#define AGENTMAIN_H_

#include "online.h"

class Agent;
class AgentMain
{
private:
	AgentMain();
	virtual ~AgentMain();

public:
	SINGLETON(AgentMain)

	bool InsertAgent(int nID);		// 增加座席
	bool DeleteAgent(int nID);		// 删除座席
	list<Agent *>::iterator GetAgent(int nID);	// 获取指定座席

private:
	list<Agent *> m_lAgents;	// 座席列表
};

#endif /* AGENTMAIN_H_ */
