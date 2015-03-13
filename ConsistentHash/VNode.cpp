/*
 * VNode.cpp
 *
 *  Created on: 2014年9月10日
 *      Author: yxd123
 */

#include "VNode.h"
#include <string.h>

void CVNode::setID(char* pid)
{
	memcpy(id, pid, strlen(pid));
	id[strlen(pid)] = '\0';
}

char* CVNode::getID()
{
	return id;
}

void CVNode::setHash(long hashVaule)
{
	hash = hashVaule;
}

long CVNode::getHash()
{
	return hash;
}



