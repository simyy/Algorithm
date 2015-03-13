/*
 * ConsistHash.h
 *
 *  Created on: 2014/9/10
 *      Author: yxd123
 * @class ConsistentHash 一致性hash类
 */
#ifndef CONSISTHASH_H_
#define CONSISTHASH_H_

#include <list>
#include <iostream>
#include "Node.h"
#include "VNode.h"

using namespace std;

class ConsistentHash{
public:
	ConsistentHash();
	~ConsistentHash();

	long getHash(char* id);

	/* 增加实体结点 , 0代表成功 , -1代表失败 */
	int addNode(CNode* pNode);

	/* 删除实体结点 , 0代表成功 , -1代表失败 */
	int delNode(CNode* pNode);

	/* 查找实体结点 */
	CNode* lookupNode(const char * object);

	/* 获取一致性hash结构的所有虚拟结点数量 */
	int getVNodesNum();

	/* 增加虚节点 */
	int addVNode(CVNode* pvnode);

	/* 显示所有实节点  */
	void showNode();

protected:
	/* 设置hash函数 */
	void setFunc(int (*pFunc)(string key));

private:
	void* func;			//Hash函数
	int vNodes;			//虚拟结点总个数
	//void* vnode_tree;	//存储虚拟结点的红黑树
	list<CNode> *nodelist;

	int (*pHashFunc)(string key);
};

int FNVHash(string key);

#endif /* CONSISTHASH_H_ */
