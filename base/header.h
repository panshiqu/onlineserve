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

using namespace std;

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

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
	int nCommand;
} Header;

#define SINGLETON_DECLARATION(classname) \
	static classname &GetInstance(void);

#define SINGLETON_IMPLEMENTATION(classname) \
	classname &classname::GetInstance(void) \
	{	\
		static classname instance; \
		return instance; \
	}

#define SINGLETON(classname) \
	static classname &GetInstance(void) \
	{	\
		static classname instance; \
		return instance; \
	}

#endif /* HEADER_H_ */
