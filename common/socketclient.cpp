/*
 * socketclient.cpp
 *
 *  Created on: 2015年1月25日
 *      Author: root
 */

#include "socketclient.h"
#include "socketdelegate.h"

SocketClient::SocketClient(SocketDelegate *pDelegate)
	: m_pDelegate(pDelegate)
	, m_nBufferOffset(0)
{
	memset(m_szRecvBuffers, 0, SOCKET_READ_BUFFER_SIZE);
}

SocketClient::~SocketClient()
{

}

bool SocketClient::Init(const char *pAddress, int nPort)
{
	// 创建套接字
	if (!m_hSocket.Create()) return false;

	// 设置非阻塞属性
	if (!m_hSocket.SetNonblock()) return false;

	// 连接服务器
	if (!m_hSocket.Connect(pAddress, nPort)) return false;

	return true;
}

void SocketClient::Run(void)
{
	// 检查可读
	if (m_hSocket.CheckRead())
	{
		// 接收
		RunRecv();

		// 解析消息
		char *pMessage = NULL;
		while (PraseMessage(pMessage))
			m_pDelegate->OnMessage(pMessage);
	}

	// 检查可写
	if (GetSendSize() && m_hSocket.CheckWrite())
	{
		// 发送
		RunSend();
	}
}

int SocketClient::RunSend(void)
{
	// 取缓存
	SendBuffer *pSendBuffer = m_lSendBuffers.front();

	// 执行发送
	int nRes = m_hSocket.Send(pSendBuffer->pBuffer + pSendBuffer->nOffset, pSendBuffer->nLength - pSendBuffer->nOffset, 0);

	if (nRes > 0)
	{
		// 发送成功
		if (nRes == pSendBuffer->nLength - pSendBuffer->nOffset)
		{
			// 缓存发送完
			m_lSendBuffers.pop_front();
			delete pSendBuffer->pBuffer;
			delete pSendBuffer;
		}
		else
		{
			// 缓存未发送完
			pSendBuffer->nOffset += nRes;
		}
	}

	return nRes;
}

int SocketClient::RunRecv(void)
{
	// 执行接收
	int nRes = m_hSocket.Receive(&m_szRecvBuffers[m_nBufferOffset], SOCKET_READ_BUFFER_SIZE - m_nBufferOffset, 0);

	// 接收成功设置偏移
	if (nRes > 0) m_nBufferOffset += nRes;
	return nRes;
}

bool SocketClient::PraseMessage(char *pMessage)
{
	// 缓存无消息
	if (m_nBufferOffset <= 0) return false;

	// 缓存消息不完整
	Header *pHeader = (Header *)m_szRecvBuffers;
	int nLength = pHeader->nLength;
	if (nLength > m_nBufferOffset)
		return false;

	// 消息拷贝
	pMessage = new char[nLength];
	memcpy(pMessage, m_szRecvBuffers, nLength);

	// 数据前移
	int nCopyLength = m_nBufferOffset - nLength < nLength ? nLength : m_nBufferOffset - nLength;
	memcpy(&m_szRecvBuffers[0], &m_szRecvBuffers[nLength], nCopyLength);
	m_nBufferOffset -= nLength;
	return true;
}

void SocketClient::SendMessage(const char *pBuffer, int nLength, int nCommand)
{
	// 非法调用
	if (!pBuffer || nLength <= 0) return ;

	// 创建消息头
	Header head;
	int nLen = sizeof(Header);
	head.nCommand = nCommand;
	head.nLength = nLength + nLen;

	// 创建发送临时缓存
	char *pTemp = new char[head.nLength];

	// 拷贝消息头
	memcpy(pTemp, &head, nLen);

	// 拷贝消息体
	memcpy(&pTemp[nLen], pBuffer, nLength);

	// 创建发送缓存
	SendBuffer *pSendBuffer = new SendBuffer();
	pSendBuffer->pBuffer = pTemp;
	pSendBuffer->nLength = head.nLength;
	pSendBuffer->nOffset = 0;

	// 等待发送
	m_lSendBuffers.push_back(pSendBuffer);
}

