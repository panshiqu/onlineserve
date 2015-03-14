/*
 * header.h
 *
 *  Created on: 2015年2月5日
 *      Author: root
 */

#ifndef HEADER_H_
#define HEADER_H_

#ifndef SOCKET_ADDRESS_SIZE
#define SOCKET_ADDRESS_SIZE 20
#endif

#ifndef SOCKET_READ_BUFFER_SIZE
#define SOCKET_READ_BUFFER_SIZE 8192
#endif

// 套接字状态
enum SOCKET_STATUS
{
	SOCKET_CLOSED				= 0,	// 已关闭
	SOCKET_CONNECTED			= 1,	// 已连接
	SOCKET_CONNECTING			= 2,	// 正在连接
	SOCKET_DISCONNECTED		= 3,	// 已断开
	SOCKET_CONNECTFAILED		= 4,	// 连接拒绝
	SOCKET_CONNECTTIMEOUT	= 5,	// 连接超时
};

// 发送缓存
typedef struct SENDBUFFER
{
	char *pBuffer;		// 内容
	int nOffset;		// 偏移
	int nLength;		// 长度
} SendBuffer;

// 消息头
typedef struct HEADER
{
	int nLength;		// 长度
	int nCommand;		// 命令
	int nErrorCode;	// 错误码
} Header;

// 单例模式宏
#define SINGLETON(classname) \
	static classname &GetInstance(void) \
	{	\
		static classname instance; \
		return instance; \
	}

#endif /* HEADER_H_ */
