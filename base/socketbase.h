/*
 * socketbase.h
 *
 *  Created on: 2015年1月15日
 *      Author: root
 */

#ifndef SOCKETBASE_H_
#define SOCKETBASE_H_

#include <errno.h>
#include <string.h>

#ifdef WIN32
#include <winsock2.h>
typedef int socklen_t;
typedef short int in_port_t;
#elif __linux__
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define INVALID_SOCKET -1
#endif

#include "header.h"

class SocketBase {
public:
	SocketBase(int nSocket = INVALID_SOCKET);
	virtual ~SocketBase();

	bool Create(int nDomain = AF_INET, int nType = SOCK_STREAM, int nProtocol = IPPROTO_TCP);
	void Close(void);

	bool Bind(in_port_t nPort, int nAddress = INADDR_ANY, int nDomain = AF_INET);
	bool Bind(in_port_t nPort, const char *pAddress, int nDomain = AF_INET);

	bool Listen(int nQueue = 5);
	bool Accept(int &nSocket, sockaddr *pAddress = NULL, socklen_t *pLength = NULL);

	bool Connect(const char *pAddress, in_port_t nPort);
	bool Connect(const sockaddr *pAddress, socklen_t nLength);

	int Send(const char *pBuffer, size_t nLength, int nFlags = 0);
	int SendTo(const char *pBuffer, size_t nLength, const sockaddr *pToAddress, socklen_t nToLength, int nFlags = 0);

	int Receive(char *pBuffer, size_t nLength, int nFlags = 0);
	int ReceiveFrom(char *pBuffer, size_t nLength, sockaddr *pFromAddress, socklen_t *pFromLength, int nFlags = 0);

public:
	bool SetNonblock(void);
	bool SetReuseaddr(void);
	int CheckReadable(void);
	int CheckWritable(void);
	int CheckConnected(void);

public:
	int GetSocket(void)				{ return m_nSocket; }
	void SetSocket(int nSocket)	{ m_nSocket = nSocket; }

private:
	int m_nSocket;
};

#endif /* SOCKETBASE_H_ */
