/*
 * CNode.h
 *
 *  Created on: 2014/9/10
 *      Author: yxd123
 *
 * @class CNode
 * 一致性哈希中的实节点（映射节点）
 */
#ifndef CNODE_H_
#define CNODE_H_

#include "VNode.h"
#include <list>
using namespace std;

class CNode
{
public:
	CNode();
	~CNode();

	/* 获取哈希 */
	long getHash();

	/* 设置标识 */
	void setID(char* pid);

	/* 设置Hash */
	void setHash(long phash);

	/* 获取标识 */
	const char* getID();

	/* 获取虚拟节点数量 */
	int getVNodeNum();

	/* 增加虚节点数量 */
	void addVNodeNum(int n);

	/* 获取当前节点上虚拟节点的数据 */
	list<CVNode>* getVNode();

	/* 添加虚拟节点 */
	void addVNode(CVNode* pvnode);

protected:

private:
	char id[100];			//存储标识
	int  vNodeNum;			//虚拟节点数量
	list<CVNode>* vnodelist;//虚拟节点
	long hash;
};

#endif /* CNODE_H_ */
