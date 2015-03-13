/*
 * CNode.cpp

 *
 *  Created on: 2014/9/10
 *      Author: yxd123
 */
#include <stdlib.h>
#include <string.h>
#include "Node.h"

CNode::CNode()
{
	vnodelist = new list<CVNode>;
	vNodeNum = 0;
}

CNode::~CNode()
{
	delete vnodelist;
}

long CNode::getHash()
{
	return hash;
}

void CNode::setHash(long phash)
{
	hash = phash;
}

void CNode::setID(char* pid)
{
	memcpy(id, pid, strlen(pid));
	id[strlen(pid)] = '\0';
}

const char* CNode::getID()
{
	return id;
}

int CNode::getVNodeNum()
{
	return vNodeNum;
}

void CNode::addVNodeNum(int n)
{
	vNodeNum += n;
}

list<CVNode>* CNode::getVNode()
{
	return vnodelist;
}

void CNode::addVNode(CVNode* pvnode)
{
	if(pvnode == NULL)
		return;
	vnodelist->push_back(*pvnode);
}

