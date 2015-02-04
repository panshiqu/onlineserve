/*
 * socketserver.cpp
 *
 *  Created on: 2015年1月24日
 *      Author: root
 */

#include "socketserver.h"
#include "socketclient.h"

SocketServer::SocketServer()
	: m_nSocket(-1)
{

}

SocketServer::~SocketServer()
{
	for (auto client : m_vClient)
	{
		Close(client->GetSocket());
		delete client;
	}
}

bool SocketServer::SetNonblock(int nSocket)
{
	// 获取描述符属性
	int nOptions = fcntl(nSocket, F_GETFL);
	if (nOptions == -1) return false;
	nOptions |= O_NONBLOCK;

	// 设置非阻塞属性
	if (fcntl(nSocket, F_SETFL, nOptions) == -1) return false;
	return true;
}

void SocketServer::Close(int nSocket)
{
	if (nSocket != -1)
	{
		// 关闭套接字
		shutdown(nSocket, SHUT_RDWR);
		close(nSocket);
	}
}

bool SocketServer::Init(int nPort)
{
	// 创建套接字
	if ((m_nSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) return false;

	// 设置可重用属性
	int nReuseaddr = 1;
	if (setsockopt(m_nSocket, SOL_SOCKET, SO_REUSEADDR, &nReuseaddr, sizeof(nReuseaddr)) == -1) return false;

	// 设置非阻塞属性
	if (!SetNonblock(m_nSocket)) return false;

	// 绑定端口
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPort);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(m_nSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1) return false;

	// 监听端口
	if (listen(m_nSocket, 10) == -1) return false;
	return true;
}

void SocketServer::Run(void)
{
	int nMaxFD = 0;
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
			int fd = accept(m_nSocket, (struct sockaddr *)&addr, &length);
			if (fd < 0) cout << "accept error." << endl;
			else
			{
				if (!SetNonblock(fd)) Close(fd);
				else
				{
					SocketClient *pClient = new SocketClient(fd);
					m_vClient.push_back(pClient);
					OnConnected(pClient);
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
				if((nRes = pClient->RunRecv()))
				{
					char *pMessage = NULL;
					while ((pMessage = pClient->Prase()))
						OnMessage(pClient, pMessage);
				}
			}

			if ((nRes > 0) && FD_ISSET(nSocket, &writeSet))
				nRes = pClient->RunSend();

			if (nRes <= 0)
			{
				// 断开连接
				m_vClient.erase(m_vClient.begin()+i);
				OnDisconnected(pClient);
				Close(nSocket);
				delete pClient;
			}
		}
	}
}

void SocketServer::OnMessage(SocketClient *pClient, char *pBuffer)
{
	cout << "OnMessage." << endl;

	//cout << &pBuffer[sizeof(Header)] << endl;
	delete pBuffer;

	char szBuffer[7];
	memcpy(szBuffer, "welcome", 7);
	pClient->Send(szBuffer, 7);
}

void SocketServer::OnConnected(SocketClient *pClient)
{
	cout << "OnConnected." << endl;
}

void SocketServer::OnDisconnected(SocketClient *pClient)
{
	cout << "OnDisconnected." << endl;
}

