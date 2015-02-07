/*
 * dispatcher.cpp
 *
 *  Created on: 2015年1月26日
 *      Author: root
 */

#include "dispatcher.h"
#include "processer.h"

SINGLETON_IMPLEMENTATION(Dispatcher)

Dispatcher::Dispatcher()
{

}

Dispatcher::~Dispatcher()
{

}

void Dispatcher::OnMessage(SocketClient *pClient, char *pBuffer)
{
	Header *pHeader = (Header *)pBuffer;
	map<int, Callback>::iterator itr = m_mapCallback.find(pHeader->nCommand);
	if (itr == m_mapCallback.end()) pHeader->nCommand = UNKNOWN;

	char *pMessage = &pBuffer[sizeof(Header)];
	m_mapCallback[pHeader->nCommand](pClient, pMessage);
}

void Dispatcher::OnConnected(SocketClient *pClient)
{
	cout << "OnConnected." << endl;
}

void Dispatcher::OnDisconnected(SocketClient *pClient)
{
	cout << "OnDisconnected." << endl;
}

void Dispatcher::RegisterCallback(void)
{
	m_mapCallback[AGENT_LOGIN] = bind(&Processer::ProcLogin, &Processer::GetInstance(), placeholders::_1, placeholders::_2);
	m_mapCallback[AGENT_LOGOUT] = bind(&Processer::ProcLogout, &Processer::GetInstance(), placeholders::_1, placeholders::_2);
}

