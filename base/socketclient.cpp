/*
 * socketclient.cpp
 *
 *  Created on: 2015年1月25日
 *      Author: root
 */

#include "socketclient.h"
#include "socketdelegate.h"

SocketClient::SocketClient()
{

}

SocketClient::SocketClient(int nSocket)
	: m_hSocket(nSocket)
{

}

SocketClient::SocketClient(SocketDelegate *pDelegate)
	: m_pDelegate(pDelegate)
{

}

SocketClient::~SocketClient()
{
	// 关闭收发套接字
	m_hSocket.Close();

	// 清空发送缓存队列
	for (auto pSendBuffer : m_lSendBuffers)
	{
		delete pSendBuffer->pBuffer;
		delete pSendBuffer;
	}

	m_lSendBuffers.clear();
}

bool SocketClient::Init(const char *pAddress, int nPort)
{
	// 创建套接字
	if (!m_hSocket.Create()) return false;

	// 设置非阻塞属性
	if (!m_hSocket.SetNonblock()) return false;

	// 设置套接字属性
	m_nPort = nPort;
	memcpy(m_szAddress, pAddress, strlen(pAddress));

	// 请求连接服务器
	m_hSocket.Connect(m_szAddress, m_nPort);
	m_nStatus = SOCKET_CONNECTING;
	return true;
}

bool SocketClient::Run(void)
{
	switch (m_nStatus)
	{
	case SOCKET_CONNECTED:
	{
		int nRes = 1;

		// 已连接检查可读
		if (m_hSocket.CheckReadable())
		{
			// 接收
			nRes = RunRecv();

			// 解析消息
			char *pMessage = NULL;
			while ((pMessage = PraseMessage()))
				m_pDelegate->OnMessage(pMessage);
		}

		// 已连接检查可写
		if ((nRes > 0) && GetSendSize() && m_hSocket.CheckWritable())
		{
			// 发送
			nRes = RunSend();
		}

		// 接收发送失败
		if (nRes <= 0)
		{
			// 连接断开
			m_nStatus = SOCKET_DISCONNECTED;
			m_pDelegate->OnDisconnected();
		}
	}
	break;

	case SOCKET_CONNECTING:
	{
		// 连接中检查连接状态
		switch (m_hSocket.CheckConnected())
		{
		case SOCKET_CONNECTED:
		{
			// 连接成功
			m_nStatus = SOCKET_CONNECTED;
			m_pDelegate->OnConnected();
		}
		break;

		case SOCKET_CONNECTFAILED:
		{
			// 连接失败
			m_nStatus = SOCKET_CONNECTFAILED;
			m_pDelegate->OnConnectFailed();
			return false;
		}
		break;

		case SOCKET_CONNECTING:
		{
			// 连接超时
		}
		break;

		default:
			assert(false);
			break;
		}
	}
	break;

	case SOCKET_DISCONNECTED:
	{
		// 自动重连
		return false;
	}
	break;

	default:
		assert(false);
		break;
	}

	return true;
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

char *SocketClient::PraseMessage(void)
{
	// 缓存无消息
	if (m_nBufferOffset <= 0) return NULL;

	// 缓存消息不完整
	Header *pHeader = (Header *)m_szRecvBuffers;
	int nLength = pHeader->nLength;
	if (nLength > m_nBufferOffset)
		return NULL;

	// 消息拷贝
	char *pMessage = new char[nLength];
	memcpy(pMessage, m_szRecvBuffers, nLength);

	// 数据前移
	int nCopyLength = m_nBufferOffset - nLength < nLength ? nLength : m_nBufferOffset - nLength;
	memcpy(&m_szRecvBuffers[0], &m_szRecvBuffers[nLength], nCopyLength);
	m_nBufferOffset -= nLength;
	return pMessage;
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

