/*
 * agentmain.cpp
 *
 *  Created on: 2015年2月11日
 *      Author: root
 */

#include "agentmain.h"
#include "agent.h"

AgentMain::AgentMain()
{

}

AgentMain::~AgentMain()
{

}

bool AgentMain::InsertAgent(int nID)
{
	// 获取座席
	list<Agent *>::iterator itr = GetAgent(nID);
	if (itr != m_lAgents.end()) return false;

	// 插入座席
	Agent *pAgent = new Agent(nID);
	m_lAgents.push_back(pAgent);
	return true;
}

bool AgentMain::DeleteAgent(int nID)
{
	// 获取座席
	list<Agent *>::iterator itr = GetAgent(nID);
	if (itr == m_lAgents.end()) return false;

	// 删除座席
	Agent *pAgent = *itr;
	m_lAgents.erase(itr);
	delete pAgent;
	return true;
}

list<Agent *>::iterator AgentMain::GetAgent(int nID)
{
	// 获取指定座席
	list<Agent *>::iterator itr = m_lAgents.begin();
	for (; itr != m_lAgents.end(); itr++)
	{
		// 存在返回
		if ((*itr)->GetID() == nID)
			return itr;
	}

	// 不存在返回
	return m_lAgents.end();
}

