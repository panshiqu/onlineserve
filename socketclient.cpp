/*
 * socketclient.cpp
 *
 *  Created on: 2015年1月25日
 *      Author: root
 */

#include "socketclient.h"

SocketClient::SocketClient()
	: m_nBufferOffset(0)
{
	memset(m_szRecvBuffers, 0, SOCKET_READ_BUFFER_SIZE);
}

SocketClient::~SocketClient()
{

}

bool SocketClient::Init(const char *pAddress, int nPort)
{
	// 创建套接字
	if (!Create()) return false;

	// 设置非阻塞属性
	if (!SetNonblock()) return false;

	// 连接服务器
	if (!Connect(pAddress, nPort)) return false;

	return true;
}

void SocketClient::Run(void)
{
	if (CheckRead())
	{
		this->RunRecv();
		char *pMessage = NULL;
		while ((pMessage = Prase()))
			OnMessage(pMessage);
	}

	if (GetSendSize() && CheckWrite())
	{
		this->RunSend();
	}
}

char *SocketClient::Prase(void)
{
	if (m_nBufferOffset <= 0) return NULL;

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

	Header head;
	int nLen = sizeof(Header);
	head.nLength = nLength + nLen;
	char *pTemp = new char[head.nLength];
	memcpy(pTemp, &head, nLen);
	memcpy(&pTemp[nLen], pBuffer, nLength);

	SendBuffer *pSendBuffer = new SendBuffer();
	pSendBuffer->pBuffer = pTemp;
	pSendBuffer->nLength = head.nLength;
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

void SocketClient::OnMessage(char *pBuffer)
{
	cout << "Client Father OnMessage." << endl;
}

