/*
 * socketbase.cpp
 *
 *  Created on: 2015年1月15日
 *      Author: root
 */

#include "socketbase.h"

SocketBase::SocketBase()
	: m_socket(INVALID_SOCKET)
{

}

SocketBase::~SocketBase()
{

}

bool SocketBase::Create(int domain, int type, int protocol)
{
	int nReuseaddr = 1;

	if ((m_socket = socket(domain, type, protocol)) != -1)
	{
		if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &nReuseaddr, sizeof(nReuseaddr)) == -1)
		{
			Close();
			return false;
		}

		return true;
	}

	return false;
}

void SocketBase::Close(void)
{
	if (m_socket != INVALID_SOCKET)
	{
		shutdown(m_socket, SHUT_RDWR);
		close(m_socket);
		m_socket = INVALID_SOCKET;
	}
}

bool SocketBase::Bind(in_port_t port, int address, int domain)
{
	if (m_socket == INVALID_SOCKET) return false;

	struct sockaddr_in addr;
	addr.sin_family = domain;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = address;

	if (bind(m_socket, (struct sockaddr *)&addr, sizeof(addr)) == 0)
		return true;
	return false;
}

bool SocketBase::Bind(in_port_t port, const char *address, int domain)
{
	if (m_socket == INVALID_SOCKET || address == NULL) return false;

	struct sockaddr_in addr;
	addr.sin_family = domain;
	addr.sin_port = htons(port);
	inet_pton(AF_INET, address, &(addr.sin_addr));

	if (bind(m_socket, (struct sockaddr *)&addr, sizeof(addr)) == 0)
		return true;
	return false;
}

bool SocketBase::Listen(int queue)
{
	if (m_socket == INVALID_SOCKET) return false;

	if (listen(m_socket, queue) == 0)
		return true;
	return false;
}

bool SocketBase::Accept(SocketBase &socket, sockaddr *address, socklen_t *length)
{
	if (m_socket == INVALID_SOCKET) return false;

	int sock = INVALID_SOCKET;
	while ((sock = accept(m_socket, address, length)) == INVALID_SOCKET);

	if (sock == INVALID_SOCKET) return false;

	socket = sock;
	return true;
}

bool SocketBase::Connect(const char *address, in_port_t port)
{
	if (m_socket == INVALID_SOCKET) return false;

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_pton(AF_INET, address, &(addr.sin_addr));
	if (addr.sin_addr.s_addr == INADDR_NONE)
	{
		struct hostent *phe;
		if ((phe = gethostbyname(address)) == NULL) return false;

		memcpy(&addr.sin_addr, phe->h_addr_list, phe->h_length);
	}

	int res;
	while ((res = connect(m_socket, (struct sockaddr *)&addr, sizeof(addr))) != 0);

	if (res != 0) return false;
	return true;
}

bool SocketBase::Connect(const sockaddr *address, socklen_t length)
{
	if (m_socket == INVALID_SOCKET) return false;

	int res;
	while ((res = connect(m_socket, address, length)) != 0);

	if (res != 0) return false;
	return true;
}

int SocketBase::Send(const char *buf, size_t length, int flags)
{
	int sends = 0;
	int hasSend = 0;

	if (m_socket == INVALID_SOCKET || buf == NULL || length <= 0) return -1;

	while (length > 0)
	{
		while ((sends = send(m_socket, &buf[hasSend], length, flags)) == -1);
		if (sends <= 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				usleep(10000);
			else
				break;
		}
		else
		{
			length -= sends;
			hasSend += sends;
		}
	}

	return hasSend;
}

int SocketBase::SendTo(const char *buf, size_t length, const sockaddr *toaddress, socklen_t tolength, int flags)
{
	if (m_socket == INVALID_SOCKET || buf == NULL || length <= 0) return -1;

	return sendto(m_socket, buf, length, flags, toaddress, tolength);
}

int SocketBase::Receive(char *buf, size_t length, int flags)
{
	int res;

	if (m_socket == INVALID_SOCKET || buf == NULL || length <= 0) return -1;

	while ((res = recv(m_socket, buf, length, flags)) == -1);
	return res;
}

int SocketBase::ReceiveFrom(char *buf, size_t length, sockaddr *fromaddress, socklen_t *fromlength, int flags)
{
	int res;

	if (m_socket == INVALID_SOCKET || buf == NULL || length <= 0) return -1;

	while ((res = recvfrom(m_socket, buf, length, flags, fromaddress, fromlength)) == -1);
	return res;
}

