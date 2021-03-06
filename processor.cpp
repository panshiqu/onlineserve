/*
 * processor.cpp
 *
 *  Created on: 2015年2月9日
 *      Author: root
 */

#include "processor.h"
#include "dispatcher.h"
#include "agentmain.h"
#include "agent.h"

Processor::Processor()
{

}

Processor::~Processor()
{

}

void Processor::RegisterCallback(void)
{
	// 注册消息处理回调函数
	Dispatcher::GetInstance().RegisterCallback(UNKNOWN, bind(&Processor::ProcUnknown, &Processor::GetInstance(), placeholders::_1, placeholders::_2, placeholders::_3));
	Dispatcher::GetInstance().RegisterCallback(LISTENING, bind(&Processor::ProcListening, &Processor::GetInstance(), placeholders::_1, placeholders::_2, placeholders::_3));
	Dispatcher::GetInstance().RegisterCallback(AGENT_LOGIN, bind(&Processor::ProcAgentLogin, &Processor::GetInstance(), placeholders::_1, placeholders::_2, placeholders::_3));
	Dispatcher::GetInstance().RegisterCallback(AGENT_LOGOUT, bind(&Processor::ProcAgentLogout, &Processor::GetInstance(), placeholders::_1, placeholders::_2, placeholders::_3));
	Dispatcher::GetInstance().RegisterCallback(AGENT_CHAT, bind(&Processor::ProcAgentChat, &Processor::GetInstance(), placeholders::_1, placeholders::_2, placeholders::_3));
	Dispatcher::GetInstance().RegisterCallback(AGENT_REQUEST, bind(&Processor::ProcAgentRequest, &Processor::GetInstance(), placeholders::_1, placeholders::_2, placeholders::_3));
}

void Processor::SendMessage(SocketClient *pClient,
		google::protobuf::Message &Proto,
		int nCommand, int nErrorCode)
{
	// 发送消息
	char szMessage[Proto.ByteSize()];
	Proto.SerializeToArray(szMessage, Proto.ByteSize());
	cout << "##Send CMD: " << nCommand << " Length: " << Proto.ByteSize() << " ERR: " << nErrorCode << endl;
	pClient->SendMessage(szMessage, Proto.ByteSize(), nCommand, nErrorCode);
}

int Processor::ProcUnknown(char *pMessage, int nLength, SocketClient *pClient)
{
	cout << "Unknown Message." << endl;
	return E_SUCCEED;
}

int Processor::ProcListening(char *pMessage, int nLength, SocketClient *pClient)
{
	cout << "Listening Message." << endl;
	return E_SUCCEED;
}

int Processor::ProcAgentLogin(char *pMessage, int nLength, SocketClient *pClient)
{
	// 解析消息
	ReqAgentLogin req;
	ResAgentLogin res;
	req.ParseFromArray(pMessage, nLength);

	// 是否已存在
	int nRes = AgentMain::GetInstance().FindAgent(req.aid());
	if (nRes == E_SUCCEED) return E_AGENT_LOGIN;

	// 插入座席
	Agent *pAgent = AgentMain::GetInstance().InsertAgent(req.aid(), pClient);
	if (pAgent != NULL)
	{
		res.set_aid(pAgent->GetID());
	}

	// 发送回复
	SendMessage(pClient, res, AGENT_LOGIN, 0);
	return E_SUCCEED;
}

int Processor::ProcAgentLogout(char *pMessage, int nLength, SocketClient *pClient)
{
	// 解析消息
	ReqAgentLogout req;
	ResAgentLogout res;
	req.ParseFromArray(pMessage, nLength);

	// 删除座席
	int nRes = AgentMain::GetInstance().DeleteAgent(req.aid());
	if (nRes != E_SUCCEED) return nRes;

	// 发送回复
	SendMessage(pClient, res, AGENT_LOGOUT, 0);
	return E_SUCCEED;
}

int Processor::ProcAgentChat(char *pMessage, int nLength, SocketClient *pClient)
{
	// 解析消息
	ReqAgentChat req;
	ResAgentChat res;
	req.ParseFromArray(pMessage, nLength);

	// 转发消息
	int nRes = AgentMain::GetInstance().SendChat(req.ato(), pMessage, nLength);
	if (nRes != E_SUCCEED) return nRes;

	// 发送回复
	SendMessage(pClient, res, AGENT_CHAT, 0);
	return E_SUCCEED;
}

int Processor::ProcAgentRequest(char *pMessage, int nLength, SocketClient *pClient)
{
	// 解析消息
	ReqAgentRequest req;
	ResAgentRequest res;
	req.ParseFromArray(pMessage, nLength);

	// 分配座席
	Agent *pAgent = AgentMain::GetInstance().AllocAgent();
	if (pAgent != NULL)
	{
		res.set_aid(pAgent->GetID());
	}

	// 发送回复
	SendMessage(pClient, res, AGENT_REQUEST, 0);
	return E_SUCCEED;
}

