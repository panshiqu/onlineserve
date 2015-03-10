/*
 * agentdelegate.cpp
 *
 *  Created on: 2015年2月11日
 *      Author: root
 */

#include "agentdelegate.h"

AgentDelegate::AgentDelegate()
{

}

AgentDelegate::~AgentDelegate()
{

}

void AgentDelegate::OnConnected(SocketClient *pClient)
{
	cout << "Agent OnConnected." << endl;
}

void AgentDelegate::OnDisconnected(SocketClient *pClient)
{
	cout << "Agent OnDisconnected." << endl;
}

void AgentDelegate::OnConnectFailed(SocketClient *pClient)
{
	cout << "Agent OnConnectFailed." << endl;
}

void AgentDelegate::OnMessage(char *pMessage, SocketClient *pClient)
{
	Header *pHeader = (Header *)pMessage;
	cout << "##Receive CMD: " << pHeader->nCommand << " Length: " << pHeader->nLength << " ERR: " << pHeader->nErrorCode << endl;

	switch (pHeader->nCommand)
	{
	case SRV_AGENT_CHAT:
		{
			ReqAgentChat req;
			req.ParseFromArray(&pMessage[sizeof(Header)], pHeader->nLength - sizeof(Header));

			cout << "Chat MSG: " << req.word() << endl;
		}
		break;

	case AGENT_REQUEST:
		{
			ResAgentRequest res;
			res.ParseFromArray(&pMessage[sizeof(Header)], pHeader->nLength - sizeof(Header));

			cout << "Free Agent: " << res.aid() << endl;
		}
		break;

	default:
		break;
	}
}

