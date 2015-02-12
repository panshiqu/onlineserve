/*
 * agent.cpp
 *
 *  Created on: 2015年2月11日
 *      Author: root
 */

#include "agent.h"

Agent::Agent(int nID, SocketClient *pClient)
	: m_nID(nID)
	, m_pClient(pClient)
{

}

Agent::~Agent()
{

}

void Agent::SendChat(char *pMessage, int nLength, int nCommand)
{
	m_pClient->SendMessage(pMessage, nLength, nCommand, 0);
}

