/*
 * socketserver.cpp
 *
 *  Created on: 2015年1月24日
 *      Author: root
 */

#include "socketserver.h"
#include "socketclient.h"

SocketServer::SocketServer()
{

}

SocketServer::~SocketServer()
{
	// 清空收发套接字
	for (auto pClient : m_vClient)
	{
		pClient->Close();
		delete pClient;
	}

	m_vClient.clear();
}

bool SocketServer::Init(int nPort)
{
	// 创建套接字
	if (!Create()) return false;

	// 设置可重用属性
	if (!SetReuseaddr()) return false;

	// 设置非阻塞属性
	if (!SetNonblock()) return false;

	// 绑定端口
	if (!Bind(nPort)) return false;

	// 监听端口
	if (!Listen(10)) return false;

	return true;
}

void SocketServer::Run(void)
{
	int nMaxFD = 0;
	char *pMessage = NULL;
	fd_set readSet, writeSet;

	while (true)
	{
		nMaxFD = m_nSocket;

		FD_ZERO(&readSet);
		FD_ZERO(&writeSet);

		FD_SET(m_nSocket, &readSet);

		for (size_t i = 0; i < m_vClient.size(); i++)
		{
			SocketClient *pClient = m_vClient[i];
			int nSocket = pClient->GetSocket();

			if (nSocket > nMaxFD) nMaxFD = nSocket;

			if (pClient->GetSendSize())
				FD_SET(nSocket, &writeSet);

			FD_SET(nSocket, &readSet);
		}

		if (select(nMaxFD+1, &readSet, &writeSet, NULL, NULL) < 0)
		{
			cout << "select error." << endl;
			return ;
		}

		if (FD_ISSET(m_nSocket, &readSet))
		{
			struct sockaddr_in addr;
			socklen_t length = sizeof(struct sockaddr_in);
			int nSocket = Accept((struct sockaddr *)&addr, &length);
			if (nSocket < 0) cout << "accept error." << endl;
			else
			{
				SocketClient *pClient = new SocketClient();
				pClient->SetSocket(nSocket);

				if (pClient->SetNonblock())
				{
					m_vClient.push_back(pClient);
					OnConnected(pClient);
				}
				else
				{
					pClient->Close();
					delete pClient;
				}
			}
		}

		for (size_t i = 0; i < m_vClient.size(); i++)
		{
			int nRes = 1;
			SocketClient *pClient = m_vClient[i];
			int nSocket = pClient->GetSocket();

			if (FD_ISSET(nSocket, &readSet))
			{
				nRes = pClient->RunRecv();
				while ((pMessage = pClient->Prase()))
					OnMessage(pClient, pMessage);
			}

			if ((nRes > 0) && FD_ISSET(nSocket, &writeSet))
				nRes = pClient->RunSend();

			if (nRes <= 0)
			{
				m_vClient.erase(m_vClient.begin()+i);
				OnDisconnected(pClient);
				pClient->Close();
				delete pClient;
			}
		}
	}
}

void SocketServer::OnMessage(SocketClient *pClient, char *pBuffer)
{

}

void SocketServer::OnConnected(SocketClient *pClient)
{

}

void SocketServer::OnDisconnected(SocketClient *pClient)
{

}

