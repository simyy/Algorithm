/*
 * ConsistHash.cpp
 *
 *  Created on: 2014/9/10
 *      Author: yxd123
 */

#include <stdlib.h>
#include <string.h>
#include "ConsistHash.h"
#include "Node.h"
#include "VNode.h"

int M_SHIFT = 0;
int M_MASK = 0x8765fed1;

int FNVHash(string key)
{
	int hash = (int)2166136261L;
	for(int i = 0; i < key.length(); ++i)
	{
		hash = (hash * 16777619)^int(key.at(i));
	}
	if(M_SHIFT == 0)
		return hash;
	return (hash ^ (hash >> M_SHIFT)) & M_MASK;
}



ConsistentHash::ConsistentHash()
{
	nodelist = new list<CNode>;
	setFunc(FNVHash);
	vNodes = 0;
}

ConsistentHash::~ConsistentHash()
{
	delete nodelist;
}

long ConsistentHash::getHash(char* id)
{
	return pHashFunc(id);
}

void ConsistentHash::setFunc(int (*pFunc)(string key))
{
	pHashFunc = pFunc;
}

int ConsistentHash::addNode(CNode* pNode)
{
	if(pNode == NULL)
		return -1;

	if(nodelist->empty())
	{
		//cout<<"empty nodelist"<<endl;
		nodelist->push_back(*pNode);
		return 0;
	}

	list<CNode>::iterator i = nodelist->begin();
	while(pNode->getHash() > i->getHash() && i != nodelist->end())
		i++;

	int vNodeNum = i->getVNodeNum();
	if(vNodeNum <= 0)
	{
		//cout<<"vNodeNum<0"<<endl;
		nodelist->insert(i, *pNode);
		return -1;
	}

	//cout<<"vNodeNum: "<<vNodeNum<<endl;

	list<CVNode> *vnodes = i->getVNode();
	for(list<CVNode>::iterator j = vnodes->begin(); j != vnodes->end();)
	{
		//cout<<j->getHash()<<","<<pNode->getHash()<<endl;
		if(j->getHash() < pNode->getHash())
		{
			CVNode *p = new CVNode();
			p->setHash(j->getHash());
			p->setID(j->getID());
			pNode->addVNode(p);
			list<CVNode>::iterator q = j++;
			vnodes->erase(q);
			//cout<<"erase: "<<q->getHash()<<endl;
		}
		else
			++j;
	}
	nodelist->insert(i, *pNode);

	return 0;
}


int ConsistentHash::delNode(CNode* pNode)
{
	if(pNode == NULL)
		return -1;

	if(nodelist->empty())
		return -1;

	list<CNode>::iterator i = nodelist->begin();
	while(strcmp(pNode->getID(), i->getID()) && i != nodelist->end())
	{
		i++;
		if(i == nodelist->end())
		{
			return -1;
		}
	}
	list<CNode>::iterator tmp = i++;
	if(i == nodelist->end())
		i = nodelist->begin();
	list<CVNode> *vnodes = tmp->getVNode();
	for(list<CVNode>::iterator j = vnodes->begin(); j != vnodes->end(); ++j)
	{
		CVNode *p = new CVNode();
		p->setHash(j->getHash());
		p->setID(j->getID());
		i->addVNode(p);
	}

	nodelist->erase(tmp);

	return 0;
}

void ConsistentHash::showNode()
{
	if(nodelist->empty())
		cout<<"has no node"<<endl;

	list<CNode>::iterator i;
	for(i = nodelist->begin(); i != nodelist->end(); ++i)
	{
		cout<<i->getID()<<endl;
		list<CVNode> *p = i->getVNode();
		list<CVNode>::iterator i;
		for(i = p->begin(); i != p->end(); ++i)
			cout<<i->getID()<<" ";
		cout<<endl;
	}
}

int ConsistentHash::addVNode(CVNode* pvnode)
{
	list<CNode>::iterator i;
	for(i = nodelist->begin(); i != nodelist->end(); ++i)
	{
		if(i->getHash() > pvnode->getHash())
		{
			i->addVNodeNum(1);
			i->addVNode(pvnode);
			vNodes++;
			return 0;
		}
	}
	if(i == nodelist->end())
	{
		(nodelist->begin())->addVNode(pvnode);
		(nodelist->begin())->addVNodeNum(1);
	}
	vNodes++;
	return 0;
}

int ConsistentHash::getVNodesNum()
{
	return vNodes;
}
