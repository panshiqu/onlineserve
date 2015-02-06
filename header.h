/*
 * header.h
 *
 *  Created on: 2015年2月5日
 *      Author: root
 */

#ifndef HEADER_H_
#define HEADER_H_

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
	int nCommond;
} Header;

#endif /* HEADER_H_ */
