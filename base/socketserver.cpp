/*
 * socketserver.cpp
 *
 *  Created on: 2015年1月24日
 *      Author: root
 */

#include "socketserver.h"
#include "socketclient.h"
#include "socketdelegate.h"

SocketServer::SocketServer(SocketDelegate *pDelegate)
	: m_pDelegate(pDelegate)
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
	if (!m_hSocket.Create()) return false;

	// 设置可重用属性
	if (!m_hSocket.SetReuseaddr()) return false;

	// 设置非阻塞属性
	if (!m_hSocket.SetNonblock()) return false;

	// 绑定端口
	if (!m_hSocket.Bind(nPort)) return false;

	// 监听端口
	if (!m_hSocket.Listen(10)) return false;

	return true;
}

void SocketServer::Run(void)
{
	int nMaxFD = 0;
	fd_set readSet, writeSet;

	while (true)
	{
		FD_ZERO(&readSet);
		FD_ZERO(&writeSet);

		// 始终轮询监听套接字
		nMaxFD = m_hSocket.GetSocket();
		FD_SET(m_hSocket.GetSocket(), &readSet);

		for (size_t i = 0; i < m_vClient.size(); i++)
		{
			SocketClient *pClient = m_vClient[i];
			int nSocket = pClient->GetSocket();

			// 确定最大套接字描述符
			if (nSocket > nMaxFD) nMaxFD = nSocket;

			// 是否轮询可写
			if (pClient->GetSendSize())
				FD_SET(nSocket, &writeSet);

			// 始终轮询可读
			FD_SET(nSocket, &readSet);
		}

		// Select轮询
		while ((select(nMaxFD+1, &readSet, &writeSet, NULL, NULL) == -1) && (errno == EINTR))

		// 监听套接字可读
		if (FD_ISSET(m_hSocket.GetSocket(), &readSet))
		{
			struct sockaddr_in addr;
			int nSocket = INVALID_SOCKET;
			socklen_t length = sizeof(struct sockaddr_in);

			// 接受连接
			if (m_hSocket.Accept(nSocket, (struct sockaddr *)&addr, &length))
			{
				// 创建收发套接字
				SocketClient *pClient = new SocketClient();
				pClient->SetSocket(nSocket);

				// 设置非阻塞
				if (pClient->SetNonblock())
				{
					m_vClient.push_back(pClient);
					m_pDelegate->OnConnected(pClient);
				}
				else
				{
					pClient->Close();
					delete pClient;
				}
			}
		}

		// 遍历收发套接字确定是否可读写
		for (size_t i = 0; i < m_vClient.size(); i++)
		{
			int nRes = 1;
			SocketClient *pClient = m_vClient[i];
			int nSocket = pClient->GetSocket();

			// 检查可读
			if (FD_ISSET(nSocket, &readSet))
			{
				// 接收
				nRes = pClient->RunRecv();

				// 解析消息
				char *pMessage = NULL;
				while (pClient->PraseMessage(pMessage))
					m_pDelegate->OnMessage(pMessage, pClient);
			}

			// 检查可写
			if ((nRes > 0) && FD_ISSET(nSocket, &writeSet))
			{
				// 发送
				nRes = pClient->RunSend();
			}

			if (nRes <= 0)
			{
				// 接收发送失败
				m_vClient.erase(m_vClient.begin()+i);
				m_pDelegate->OnDisconnected(pClient);
				pClient->Close();
				delete pClient;
			}
		}
	}
}

