/*
 * processer.h
 *
 *  Created on: 2015年2月7日
 *      Author: root
 */

#ifndef PROCESSER_H_
#define PROCESSER_H_

#include "common/header.h"

class Processer
{
public:

	SINGLETON_DECLARATION(Processer)

	Processer();
	virtual ~Processer();

	int ProcLogin(void);
	int ProcLogout(void);
};

#endif /* PROCESSER_H_ */
