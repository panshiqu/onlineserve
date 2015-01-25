/*
 * socketclient.h
 *
 *  Created on: 2015年1月25日
 *      Author: root
 */

#ifndef SOCKETCLIENT_H_
#define SOCKETCLIENT_H_

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <list>
#include <iostream>
using namespace std;

#ifndef SOCKET_READ_BUFFER_SIZE
#define SOCKET_READ_BUFFER_SIZE 8192
#endif

typedef struct SENDBUFFER
{
	char *pBuffer;
	int nOffset;
	int nLength;
} SendBuffer;

typedef struct HEADER
{
	int nLength;
} Header;

class SocketServer;
class SocketClient {
public:
	SocketClient(SocketServer *pServer, int nSocket);
	virtual ~SocketClient();

	void Send(char *pBuffer, int nLength);
	char *Prase(void);

	bool RunSend(void);
	bool RunRecv(void);

	int GetSocket(void)				{ return m_nSocket; }
	int GetSendSize(void)			{ return m_lSendBuffers.size(); }

	void SetSocket(int nSocket)	{ m_nSocket = nSocket; }

private:
	int m_nSocket;
	int m_nBufferOffset;
	SocketServer *m_pParent;
	list<SendBuffer *> m_lSendBuffers;
	char m_szRecvBuffers[SOCKET_READ_BUFFER_SIZE];
};

#endif /* SOCKETCLIENT_H_ */
