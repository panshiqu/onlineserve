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
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

class SocketBase {
public:
	SocketBase();
	virtual ~SocketBase();

	bool Create(int domain = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
	void Close(void);

	bool Bind(in_port_t port, int address = INADDR_ANY, int domain = AF_INET);
	bool Bind(in_port_t port, const char *address, int domain = AF_INET);

	bool Listen(int queue = 5);
	bool Accept(SocketBase &socket, sockaddr *address = NULL, socklen_t *length = NULL);

	bool Connect(const char *address, in_port_t port);
	bool Connect(const sockaddr *address, socklen_t length);

	int Send(const char *buf, size_t length, int flags = 0);
	int SendTo(const char *buf, size_t length, const sockaddr *toaddress, socklen_t tolength, int flags = 0);

	int Receive(char *buf, size_t length, int flags = 0);
	int ReceiveFrom(char *buf, size_t length, sockaddr *fromaddress, socklen_t *fromlength, int flags = 0);

	void operator=(int socket)		{ m_socket = socket; }

private:
	int m_socket;
};

#endif /* SOCKETBASE_H_ */
