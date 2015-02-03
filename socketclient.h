/*
 * socketclient.h
 *
 *  Created on: 2015年1月25日
 *      Author: root
 */

#ifndef SOCKETCLIENT_H_
#define SOCKETCLIENT_H_

#include <errno.h>
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

class SocketClient {
public:
	SocketClient(int nSocket);
	virtual ~SocketClient();

	char *Prase(void);
	void Send(char *pBuffer, int nLength);

	int RunSend(void);
	int RunRecv(void);

	int GetSocket(void)				{ return m_nSocket; }
	int GetSendSize(void)			{ return m_lSendBuffers.size(); }

private:
	int m_nSocket;
	int m_nBufferOffset;
	list<SendBuffer *> m_lSendBuffers;
	char m_szRecvBuffers[SOCKET_READ_BUFFER_SIZE];
};

#endif /* SOCKETCLIENT_H_ */
