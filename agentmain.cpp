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
	// 清空座席队列
	for (auto pAgent : m_lAgents)
		delete pAgent;

	m_lAgents.clear();
}

bool AgentMain::FindAgent(int nID)
{
	// 获取座席
	list<Agent *>::iterator itr = GetAgent(nID);
	if (itr == m_lAgents.end()) return E_AGENT_FIND;

	return E_SUCCEED;
}

bool AgentMain::InsertAgent(int nID, SocketClient *pClient)
{
	// 获取座席
	list<Agent *>::iterator itr = GetAgent(nID);
	if (itr != m_lAgents.end()) return E_AGENT_LOGIN;

	// 插入座席
	Agent *pAgent = new Agent(nID, pClient);
	m_lAgents.push_back(pAgent);

	return E_SUCCEED;
}

bool AgentMain::DeleteAgent(int nID)
{
	// 获取座席
	list<Agent *>::iterator itr = GetAgent(nID);
	if (itr == m_lAgents.end()) return E_AGENT_LOGOUT;

	// 删除座席
	Agent *pAgent = *itr;
	m_lAgents.erase(itr);
	delete pAgent;

	return E_SUCCEED;
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

int AgentMain::SendChat(int nID, char *pMessage, int nLength)
{
	// 获取座席
	list<Agent *>::iterator itr = GetAgent(nID);
	if (itr == m_lAgents.end()) return E_AGENT_FIND;

	// 发送聊天信息
	Agent *pAgent = *itr;
	pAgent->SendChat(pMessage, nLength, SRV_AGENT_CHAT);

	return E_SUCCEED;
}

