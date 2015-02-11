/*
 * agent.h
 *
 *  Created on: 2015年2月11日
 *      Author: root
 */

#ifndef AGENT_H_
#define AGENT_H_

class Agent {
public:
	Agent(int nID);
	virtual ~Agent();

public:
	int GetID(void)					{ return m_nID; }
	int GetStatus(void)				{ return m_nStatus; }

	void SetID(int nID)				{ m_nID = nID; }
	void SetStatus(int nStatus)	{ m_nStatus = nStatus; }

private:
	int m_nID = 0;			// 座席编号
	int m_nStatus = 0;	// 座席状态
};

#endif /* AGENT_H_ */
