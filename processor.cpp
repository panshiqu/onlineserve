/*
 * processor.cpp
 *
 *  Created on: 2015年2月9日
 *      Author: root
 */

#include "processor.h"
#include "dispatcher.h"
#include "agentmain.h"

Processor::Processor()
{

}

Processor::~Processor()
{

}

void Processor::RegisterCallback(void)
{
	Dispatcher::GetInstance().RegisterCallback(UNKNOWN, bind(&Processor::ProcUnknown, &Processor::GetInstance(), placeholders::_1, placeholders::_2, placeholders::_3));
	Dispatcher::GetInstance().RegisterCallback(LISTENING, bind(&Processor::ProcListening, &Processor::GetInstance(), placeholders::_1, placeholders::_2, placeholders::_3));
	Dispatcher::GetInstance().RegisterCallback(AGENT_LOGIN, bind(&Processor::ProcAgentLogin, &Processor::GetInstance(), placeholders::_1, placeholders::_2, placeholders::_3));
	Dispatcher::GetInstance().RegisterCallback(AGENT_LOGOUT, bind(&Processor::ProcAgentLogout, &Processor::GetInstance(), placeholders::_1, placeholders::_2, placeholders::_3));
}

int Processor::ProcUnknown(char *pMessage, int nLength, SocketClient *pClient)
{

}

int Processor::ProcListening(char *pMessage, int nLength, SocketClient *pClient)
{

}

int Processor::ProcAgentLogin(char *pMessage, int nLength, SocketClient *pClient)
{
	// 解析消息
	ReqLogin req;
	ResLogin res;
	req.ParseFromArray(pMessage, nLength);

	// 插入座席失败
	if (!AgentMain::GetInstance().InsertAgent(req.aid()))
		return ERROR_AGENT_LOGIN;

	cout << "InsertAgent Succeed." << endl;

	// 设置回复
	res.set_aid(req.aid());

	// 发送回复
	char szMessage[res.ByteSize()];
	res.SerializeToArray(szMessage, res.ByteSize());
	pClient->SendMessage(szMessage, res.ByteSize(), AGENT_LOGIN, 0);
	return ERROR_SUCCEED;
}

int Processor::ProcAgentLogout(char *pMessage, int nLength, SocketClient *pClient)
{
	cout << "ProcLogout: " << endl;
	return ERROR_SUCCEED;
}

