/*
 * socketserver.cpp
 *
 *  Created on: 2015年1月24日
 *      Author: root
 */

#include "socketserver.h"

SocketServer::SocketServer()
	: m_nSocket(-1)
{

}

SocketServer::~SocketServer()
{

}

bool SocketServer::Init(int nPort)
{
	// 创建套接字
	if ((m_nSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) return false;

	// 设置可重用属性
	int nReuseaddr = 1;
	if (setsockopt(m_nSocket, SOL_SOCKET, SO_REUSEADDR, &nReuseaddr, sizeof(nReuseaddr)) == -1) return false;

	// 获取描述符属性
	int nOptions = fcntl(m_nSocket, F_GETFL);
	if (nOptions == -1) return false;
	nOptions |= O_NONBLOCK;

	// 设置非阻塞属性
	if (fcntl(m_nSocket, F_SETFL, nOptions) == -1) return false;

	// 绑定端口
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPort);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(m_nSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1) return false;

	// 监听端口
	if (listen(m_nSocket, 10) == -1) return false;
	return true;
}

void SocketServer::Release(void)
{
	if (m_nSocket != -1)
	{
		shutdown(m_nSocket, SHUT_RDWR);
		close(m_nSocket);
		m_nSocket = -1;
	}
}

void SocketServer::Run(void)
{
	int nMaxFD = m_nSocket;
	fd_set readSet, writeSet, exSet;

	FD_ZERO(&readSet);
	FD_ZERO(&writeSet);
	FD_ZERO(&exSet);

	FD_SET(m_nSocket, &readSet);

	select(nMaxFD+1, &readSet, &writeSet, &exSet, NULL);

	if (FD_ISSET(m_nSocket, &readSet))
	{
		cout << "srv recv." << endl;
	}

//	while (true)
//	{
//
//	}
//	while (1) {
//	        maxfd = listener;
//
//	        FD_ZERO(&readset);
//	        FD_ZERO(&writeset);
//	        FD_ZERO(&exset);
//
//	        FD_SET(listener, &readset);
//
//	        for (i=0; i < FD_SETSIZE; ++i) {
//	            if (state[i]) {
//	                if (i > maxfd)
//	                    maxfd = i;
//	                FD_SET(i, &readset);
//	                if (state[i]->writing) {
//	                    FD_SET(i, &writeset);
//	                }
//	            }
//	        }
//
//	        if (select(maxfd+1, &readset, &writeset, &exset, NULL) < 0) {
//	            perror("select");
//	            return;
//	        }
//
//	        if (FD_ISSET(listener, &readset)) {
//	            struct sockaddr_storage ss;
//	            socklen_t slen = sizeof(ss);
//	            int fd = accept(listener, (struct sockaddr*)&ss, &slen);
//	            if (fd < 0) {
//	                perror("accept");
//	            } else if (fd > FD_SETSIZE) {
//	                close(fd);
//	            } else {
//	                make_nonblocking(fd);
//	                state[fd] = alloc_fd_state();
//	                assert(state[fd]);/*XXX*/
//	            }
//	        }
//
//	        for (i=0; i < maxfd+1; ++i) {
//	            int r = 0;
//	            if (i == listener)
//	                continue;
//
//	            if (FD_ISSET(i, &readset)) {
//	                r = do_read(i, state[i]);
//	            }
//	            if (r == 0 && FD_ISSET(i, &writeset)) {
//	                r = do_write(i, state[i]);
//	            }
//	            if (r) {
//	                free_fd_state(state[i]);
//	                state[i] = NULL;
//	                close(i);
//	            }
//	        }
//	    }
}

