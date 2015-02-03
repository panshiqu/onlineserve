/*
 * dispatcher.h
 *
 *  Created on: 2015年1月26日
 *      Author: root
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <list>
#include <mutex>
#include <iostream>

using namespace std;

class Observer;
class Dispatcher {
public:
	Dispatcher();
	virtual ~Dispatcher();
	static Dispatcher &GetInstance(void);

	void Register(Observer *pObserver);
	void UnRegister(Observer *pObserver);

	void AddMessage(char *pBuffer);
	void Dispatch(void);

private:
	//std::mutex m_mMutex;
	list<char *> m_lRecvMessages;
};

#endif /* DISPATCHER_H_ */
