/*
 * socketbase.cpp
 *
 *  Created on: 2015年1月15日
 *      Author: root
 */

#include "socketbase.h"

SocketBase::SocketBase(int nSocket)
	: m_nSocket(nSocket)
{

}

SocketBase::~SocketBase()
{

}

bool SocketBase::Create(int nDomain, int nType, int nProtocol)
{
	if ((m_nSocket = socket(nDomain, nType, nProtocol)) == INVALID_SOCKET)
		return false;
	return true;
}

void SocketBase::Close(void)
{
	if (m_nSocket != INVALID_SOCKET)
	{
		shutdown(m_nSocket, SHUT_RDWR);
		close(m_nSocket);
		m_nSocket = INVALID_SOCKET;
	}
}

bool SocketBase::Bind(in_port_t nPort, int nAddress, int nDomain)
{
	if (m_nSocket == INVALID_SOCKET) return false;

	struct sockaddr_in addr;
	addr.sin_family = nDomain;
	addr.sin_port = htons(nPort);
	addr.sin_addr.s_addr = nAddress;

	if (bind(m_nSocket, (struct sockaddr *)&addr, sizeof(addr)) == 0)
		return true;
	return false;
}

bool SocketBase::Bind(in_port_t nPort, const char *pAddress, int nDomain)
{
	if (m_nSocket == INVALID_SOCKET || pAddress == NULL) return false;

	struct sockaddr_in addr;
	addr.sin_family = nDomain;
	addr.sin_port = htons(nPort);
	inet_pton(AF_INET, pAddress, &(addr.sin_addr));

	if (bind(m_nSocket, (struct sockaddr *)&addr, sizeof(addr)) == 0)
		return true;
	return false;
}

bool SocketBase::Listen(int nQueue)
{
	if (m_nSocket == INVALID_SOCKET) return false;

	if (listen(m_nSocket, nQueue) == 0)
		return true;
	return false;
}

bool SocketBase::Accept(int &nSocket, sockaddr *pAddress, socklen_t *pLength)
{
	if (m_nSocket == INVALID_SOCKET) return false;

	while (((nSocket = accept(m_nSocket, pAddress, pLength)) == INVALID_SOCKET) && (errno == EINTR));
	return nSocket == INVALID_SOCKET ? false : true;
}

bool SocketBase::Connect(const char *pAddress, in_port_t nPort)
{
	if (m_nSocket == INVALID_SOCKET) return false;

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPort);
	inet_pton(AF_INET, pAddress, &(addr.sin_addr));
	if (addr.sin_addr.s_addr == INADDR_NONE)
	{
		struct hostent *phe;
		if ((phe = gethostbyname(pAddress)) == NULL) return false;

		memcpy(&addr.sin_addr, phe->h_addr_list, phe->h_length);
	}

	int nRes;
	while (((nRes = connect(m_nSocket, (struct sockaddr *)&addr, sizeof(addr))) != 0) && (errno == EINTR));

	if (nRes != 0 && errno != EINPROGRESS) return false;
	return true;
}

bool SocketBase::Connect(const sockaddr *pAddress, socklen_t nLength)
{
	if (m_nSocket == INVALID_SOCKET) return false;

	int nRes;
	while (((nRes = (connect(m_nSocket, pAddress, nLength))) != 0) && (errno == EINTR));

	if (nRes != 0 && errno != EINPROGRESS) return false;
	return true;
}

int SocketBase::Send(const char *pBuffer, size_t nLength, int nFlags)
{
	if (m_nSocket == INVALID_SOCKET || pBuffer == NULL || nLength <= 0) return INVALID_SOCKET;

	int nRes;
	while ((nRes = send(m_nSocket, pBuffer, nLength, nFlags)) == -1 && errno == EINTR);
	return nRes;
}

int SocketBase::SendTo(const char *pBuffer, size_t nLength, const sockaddr *pToAddress, socklen_t nToLength, int nFlags)
{
	return true;
}

int SocketBase::Receive(char *pBuffer, size_t nLength, int nFlags)
{
	if (m_nSocket == INVALID_SOCKET || pBuffer == NULL || nLength <= 0) return INVALID_SOCKET;

	int nRes;
	while ((nRes = recv(m_nSocket, pBuffer, nLength, nFlags)) == -1 && errno == EINTR);
	return nRes;
}

int SocketBase::ReceiveFrom(char *pBuffer, size_t nLength, sockaddr *pFromAddress, socklen_t *pFromLength, int nFlags)
{
	return true;
}

bool SocketBase::SetNonblock(void)
{
	if (m_nSocket == INVALID_SOCKET) return false;

	// 获取描述符属性
	int nOptions = fcntl(m_nSocket, F_GETFL);
	if (nOptions == -1) return false;
	nOptions |= O_NONBLOCK;

	// 设置非阻塞属性
	if (fcntl(m_nSocket, F_SETFL, nOptions) == -1) return false;
	return true;
}

bool SocketBase::SetReuseaddr(void)
{
	if (m_nSocket == INVALID_SOCKET) return false;

	// 设置可重用属性
	int nReuseaddr = 1;
	if (setsockopt(m_nSocket, SOL_SOCKET, SO_REUSEADDR, &nReuseaddr, sizeof(nReuseaddr)) == -1)
		return false;
	return true;
}

bool SocketBase::CheckReadable(void)
{
	if (m_nSocket == INVALID_SOCKET) return false;

	int nRes;
	fd_set fds;
	struct timeval tv;

	// 检查可读
	FD_ZERO(&fds);
	FD_SET(m_nSocket, &fds);
	memset(&tv, 0, sizeof(tv));
	while(((nRes = select(m_nSocket+1, &fds, NULL, NULL, &tv)) == -1) && (errno == EINTR));
	return ((nRes > 0) && FD_ISSET(m_nSocket, &fds) > 0) ? true : false;
}

bool SocketBase::CheckWritable(void)
{
	if (m_nSocket == INVALID_SOCKET) return false;

	int nRes;
	fd_set fds;
	struct timeval tv;

	// 检查可写
	FD_ZERO(&fds);
	FD_SET(m_nSocket, &fds);
	memset(&tv, 0, sizeof(tv));
	while(((nRes = select(m_nSocket+1, NULL, &fds, NULL, &tv)) == -1) && (errno == EINTR));
	return ((nRes > 0) && FD_ISSET(m_nSocket, &fds) > 0) ? true : false;
}

int SocketBase::CheckConnected(void)
{
	// 检查可写
	if (CheckWritable())
	{
		// 连接状态
		int nError;
		socklen_t nLength = sizeof(nError);
		if (getsockopt(m_nSocket, SOL_SOCKET, SO_ERROR, &nError, &nLength) == -1)
			return SOCKET_CONNECTFAILED;

		// 连接拒绝或超时
		if (nError == ECONNREFUSED || nError == ETIMEDOUT)
			return SOCKET_CONNECTFAILED;

		return SOCKET_CONNECTED;
	}

	return SOCKET_CONNECTING;
}

