/*
 * socketclient.cpp
 *
 *  Created on: 2015年1月25日
 *      Author: root
 */

#include "socketclient.h"
#include "socketserver.h"

SocketClient::SocketClient(int nSocket)
	: m_nSocket(nSocket)
	, m_nBufferOffset(0)
{
	memset(m_szRecvBuffers, 0, SOCKET_READ_BUFFER_SIZE);
}

SocketClient::~SocketClient()
{

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

void SocketClient::Send(char *pBuffer, int nLength)
{
	if (!pBuffer || nLength <= 0) return ;

	char *pTemp = new char[nLength];
	memcpy(pTemp, pBuffer, nLength);

	SendBuffer *pSendBuffer = new SendBuffer();
	pSendBuffer->pBuffer = pTemp;
	pSendBuffer->nLength = nLength;
	pSendBuffer->nOffset = 0;

	m_lSendBuffers.push_back(pSendBuffer);
}

int SocketClient::RunSend(void)
{
	SendBuffer *pSendBuffer = m_lSendBuffers.front();

	int nRes;
	while ((nRes = send(m_nSocket, pSendBuffer->pBuffer + pSendBuffer->nOffset, pSendBuffer->nLength - pSendBuffer->nOffset, 0)) == -1 && errno == EINTR);

	if (nRes > 0)
	{
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
	}

	return nRes;
}

int SocketClient::RunRecv(void)
{
	int nRes;
	while ((nRes = recv(m_nSocket, &m_szRecvBuffers[m_nBufferOffset], SOCKET_READ_BUFFER_SIZE - m_nBufferOffset, 0)) == -1 && errno == EINTR);

	if (nRes > 0) m_nBufferOffset += nRes;
	return nRes;
}

