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

	bool PraseMessage(char *pMessage);
	void SendMessage(const char *pBuffer, int nLength, int nCommand);

public:
	void Close(void)					{ m_hSocket.Close(); }
	bool SetNonblock(void)			{ return m_hSocket.SetNonblock(); }
	int GetSendSize(void)			{ return m_lSendBuffers.size(); }

public:
	int GetSocket(void)				{ return m_hSocket.GetSocket(); }
	void SetSocket(int nSocket)		{ m_hSocket.SetSocket(nSocket); }

private:
	int m_nPort;
	int m_nBufferOffset;
	SocketBase m_hSocket;
	SocketDelegate *m_pDelegate;
	list<SendBuffer *> m_lSendBuffers;
	char m_szAddress[SOCKET_ADDRESS_SIZE];
	char m_szRecvBuffers[SOCKET_READ_BUFFER_SIZE];
};

#endif /* SOCKETCLIENT_H_ */
