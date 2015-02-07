/*
 * socketbase.h
 *
 *  Created on: 2015年1月15日
 *      Author: root
 */

#ifndef SOCKETBASE_H_
#define SOCKETBASE_H_

#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "header.h"

class SocketBase {
public:
	SocketBase();
	virtual ~SocketBase();

	bool Create(int nDomain = AF_INET, int nType = SOCK_STREAM, int nProtocol = IPPROTO_TCP);
	void Close(void);

	bool Bind(in_port_t nPort, int nAddress = INADDR_ANY, int nDomain = AF_INET);
	bool Bind(in_port_t nPort, const char *pAddress, int nDomain = AF_INET);

	bool Listen(int nQueue = 5);
	int Accept(sockaddr *pAddress = NULL, socklen_t *pLength = NULL);

	bool Connect(const char *pAddress, in_port_t nPort);
	bool Connect(const sockaddr *pAddress, socklen_t nLength);

	int Send(const char *pBuffer, size_t nLength, int nFlags = 0);
	int SendTo(const char *pBuffer, size_t nLength, const sockaddr *pToAddress, socklen_t nToLength, int nFlags = 0);

	int Receive(char *pBuffer, size_t nLength, int nFlags = 0);
	int ReceiveFrom(char *pBuffer, size_t nLength, sockaddr *pFromAddress, socklen_t *pFromLength, int nFlags = 0);

	bool CheckRead(void);
	bool CheckWrite(void);
	bool SetNonblock(void);
	bool SetReuseaddr(void);

	int GetSocket(void)				{ return m_nSocket; }
	void SetSocket(int nSocket)	{ m_nSocket = nSocket; }

public:
	int m_nSocket;
};

#endif /* SOCKETBASE_H_ */