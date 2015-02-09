/*
 * processor.cpp
 *
 *  Created on: 2015年2月9日
 *      Author: root
 */

#include "processor.h"
#include "dispatcher.h"

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

void Processor::ProcUnknown(char *pMessage, int nLength, SocketClient *pClient)
{

}

void Processor::ProcListening(char *pMessage, int nLength, SocketClient *pClient)
{

}

void Processor::ProcAgentLogin(char *pMessage, int nLength, SocketClient *pClient)
{
	Login login;
	login.ParseFromString(pMessage);
	cout << "ProcLogin: " << login.agentid() << endl;
}

void Processor::ProcAgentLogout(char *pMessage, int nLength, SocketClient *pClient)
{
	cout << "ProcLogout: " << endl;
}

