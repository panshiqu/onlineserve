/*
 * socketclient.h
 *
 *  Created on: 2015年1月25日
 *      Author: root
 */

#ifndef SOCKETCLIENT_H_
#define SOCKETCLIENT_H_

#include <list>
#include <iostream>
using namespace std;

typedef struct SENDBUFFER
{
	char *pBuffer;
	int nOffset;
	int nLength;
} SendBuffer;

class SocketClient {
public:
	SocketClient(int nSocket);
	virtual ~SocketClient();

	void Recv(void);
	void Send(void);

	int GetSocket(void)				{ return m_nSocket; }
	int GetSendSize(void)			{ return m_lBuffers.size(); }

	void SetSocket(int nSocket)	{ m_nSocket = nSocket; }

private:
	int m_nSocket;
	list<SendBuffer> m_lBuffers;
};

#endif /* SOCKETCLIENT_H_ */
