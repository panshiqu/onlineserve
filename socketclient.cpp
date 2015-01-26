/*
 * socketclient.cpp
 *
 *  Created on: 2015年1月25日
 *      Author: root
 */

#include "socketclient.h"
#include "socketserver.h"

SocketClient::SocketClient(SocketServer *pServer, int nSocket)
	: m_nSocket(nSocket)
	, m_nBufferOffset(0)
	, m_pParent(pServer)
{
	memset(m_szRecvBuffers, 0, SOCKET_READ_BUFFER_SIZE);
	m_pParent->Register(this);
}

SocketClient::~SocketClient()
{

}

void SocketClient::Send(char *pBuffer, int nLength)
{
	if (!pBuffer || nLength <= 0) return ;

	SendBuffer *pSendBuffer = new SendBuffer();
	pSendBuffer->pBuffer = pBuffer;
	pSendBuffer->nLength = nLength;
	pSendBuffer->nOffset = 0;

	m_lSendBuffers.push_back(pSendBuffer);
}

char *SocketClient::Prase(void)
{
	Header *pHeader = (Header *)m_szRecvBuffers;
	int nLength = pHeader->nLength;
	if (nLength > m_nBufferOffset)
		return NULL;

	char *pMessage = new char[nLength];
	memcpy(pMessage, m_szRecvBuffers, nLength);

	int nCopyLength = m_nBufferOffset - nLength < nLength ? nLength : m_nBufferOffset - nLength;
	memcpy(&m_szRecvBuffers[0], &m_szRecvBuffers[nLength], nCopyLength);
	m_nBufferOffset -= nLength;
	return pMessage;
}

bool SocketClient::RunSend(void)
{
	SendBuffer *pSendBuffer = m_lSendBuffers.front();

	int nRes;
	while ((nRes = send(m_nSocket, pSendBuffer->pBuffer + pSendBuffer->nOffset, pSendBuffer->nLength - pSendBuffer->nOffset, 0)) == -1 && errno == EINTR);

	if (nRes <= 0)
	{
		m_pParent->UnRegister(this);
		return false;
	}

	if (nRes == pSendBuffer->nLength - pSendBuffer->nOffset)
	{
		m_lSendBuffers.pop_front();
		delete pSendBuffer->pBuffer;
		delete pSendBuffer;
	}
	else
	{
		pSendBuffer->nOffset += nRes;
	}

	return true;
}

bool SocketClient::RunRecv(void)
{
	int nRes;
	while ((nRes = recv(m_nSocket, &m_szRecvBuffers[m_nBufferOffset], SOCKET_READ_BUFFER_SIZE - m_nBufferOffset, 0)) == -1 && errno == EINTR);

	if (nRes <= 0)
	{
		m_pParent->UnRegister(this);
		return false;
	}

	char *pBuffer = new char[7];
	memcpy(pBuffer, "welcome", 7);
	Send(pBuffer, 7);

	m_nBufferOffset += nRes;
	return true;
}

