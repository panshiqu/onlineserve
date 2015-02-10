/*
 * header.h
 *
 *  Created on: 2015年2月5日
 *      Author: root
 */

#ifndef HEADER_H_
#define HEADER_H_

#include <map>
#include <list>
#include <vector>
#include <iostream>
#include <functional>

#include <assert.h>

using namespace std;

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

#ifndef SOCKET_ADDRESS_SIZE
#define SOCKET_ADDRESS_SIZE 20
#endif

#ifndef SOCKET_READ_BUFFER_SIZE
#define SOCKET_READ_BUFFER_SIZE 8192
#endif

enum SOCKET_STATUS
{
	SOCKET_CLOSED				= 0,
	SOCKET_CONNECTED			= 1,
	SOCKET_CONNECTING			= 2,
	SOCKET_DISCONNECTED		= 3,
	SOCKET_CONNECTFAILED		= 4,
	SOCKET_CONNECTTIMEOUT	= 5,
};

typedef struct SENDBUFFER
{
	char *pBuffer;
	int nOffset;
	int nLength;
} SendBuffer;

typedef struct HEADER
{
	int nLength;
	int nCommand;
} Header;

#define SINGLETON(classname) \
	static classname &GetInstance(void) \
	{	\
		static classname instance; \
		return instance; \
	}

#endif /* HEADER_H_ */
