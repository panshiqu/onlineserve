/*
 * socketclient.h
 *
 *  Created on: 2015年1月25日
 *      Author: root
 */

#ifndef SOCKETCLIENT_H_
#define SOCKETCLIENT_H_

#include "socketbase.h"

class SocketClient : public SocketBase
{
public:
	SocketClient();
	virtual ~SocketClient();

	virtual void OnMessage(char *pBuffer);

	bool Init(const char *pAddress, int nPort);
	void Run(void);

	char *Prase(void);
	void Send(char *pBuffer, int nLength);

	int RunSend(void);
	int RunRecv(void);

	int GetSendSize(void)			{ return m_lSendBuffers.size(); }

private:
	int m_nBufferOffset;
	list<SendBuffer *> m_lSendBuffers;
	char m_szRecvBuffers[SOCKET_READ_BUFFER_SIZE];
};

#endif /* SOCKETCLIENT_H_ */
