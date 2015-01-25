/*
 * socketclient.cpp
 *
 *  Created on: 2015年1月25日
 *      Author: root
 */

#include "socketclient.h"

SocketClient::SocketClient(int nSocket)
	: m_nSocket(nSocket)
	, m_nBufferOffset(0)
{
	memset(m_szRecvBuffers, 0, SOCKET_READ_BUFFER_SIZE);
}

SocketClient::~SocketClient()
{

}

void SocketClient::RunSend(void)
{
//	SendBuffer &sendBuffer = m_lSendBuffers.front();
//	int nRes = send(m_nSocket, sendBuffer.pBuffer + sendBuffer.nOffset, sendBuffer.nLength - sendBuffer.nOffset, 0);
}

bool SocketClient::RunRecv(void)
{
	int nRes = recv(m_nSocket, &m_szRecvBuffers[m_nBufferOffset], SOCKET_READ_BUFFER_SIZE - m_nBufferOffset, 0);

	if (nRes <= 0)
	{
		return false;
	}

	cout << m_szRecvBuffers << endl;
	memset(m_szRecvBuffers, 0, SOCKET_READ_BUFFER_SIZE);
	return true;
}

