/*
 * socketclient.h
 *
 *  Created on: 2015年1月25日
 *      Author: root
 */

#ifndef SOCKETCLIENT_H_
#define SOCKETCLIENT_H_

#include "socketbase.h"

class SocketDelegate;
class SocketClient {
public:
	SocketClient(SocketDelegate *pDelegate = NULL);
	virtual ~SocketClient();

	bool Init(const char *pAddress, int nPort);
	bool Connect(void);
	void Run(void);

public:
	int RunSend(void);
	int RunRecv(void);

	char *PraseMessage(void);
	void SendMessage(const char *pBuffer, int nLength, int nCommand);

public:
	void Close(void)					{ m_hSocket.Close(); }
	bool SetNonblock(void)			{ return m_hSocket.SetNonblock(); }
	int GetSendSize(void)			{ return m_lSendBuffers.size(); }

public:
	int GetSocket(void)				{ return m_hSocket.GetSocket(); }
	void SetSocket(int nSocket)		{ m_hSocket.SetSocket(nSocket); }

private:
	int m_nPort;												// 对端端口
	int m_nStatus;												// 套接字状态
	int m_nBufferOffset;										// 接收缓存偏移量
	SocketBase m_hSocket;									// 套接字句柄
	SocketDelegate *m_pDelegate;							// 套接字代理
	list<SendBuffer *> m_lSendBuffers;					// 发送缓存列表
	char m_szAddress[SOCKET_ADDRESS_SIZE];				// 对端网络地址
	char m_szRecvBuffers[SOCKET_READ_BUFFER_SIZE];	// 接收缓存
};

#endif /* SOCKETCLIENT_H_ */
