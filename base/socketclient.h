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
	SocketClient();
	SocketClient(int nSocket);
	SocketClient(SocketDelegate *pDelegate);
	virtual ~SocketClient();

	bool Init(const char *pAddress, int nPort);
	bool Run(void);

public:
	int RunSend(void);
	int RunRecv(void);

	char *PraseMessage(void);
	void SendMessage(const char *pBuffer, int nLength, int nCommand);

public:
	int GetSocket(void)				{ return m_hSocket.GetSocket(); }
	int GetSendSize(void)			{ return m_lSendBuffers.size(); }
	bool SetNonblock(void)			{ return m_hSocket.SetNonblock(); }

private:
	int m_nPort = 0;													// 对端端口
	int m_nStatus = 0;												// 套接字状态
	int m_nBufferOffset = 0;										// 接收缓存偏移量
	SocketBase m_hSocket;											// 套接字句柄
	list<SendBuffer *> m_lSendBuffers;							// 发送缓存列表
	SocketDelegate *m_pDelegate = NULL;							// 套接字代理
	char m_szAddress[SOCKET_ADDRESS_SIZE] = {0};				// 对端网络地址
	char m_szRecvBuffers[SOCKET_READ_BUFFER_SIZE] = {0};	// 接收缓存
};

#endif /* SOCKETCLIENT_H_ */
