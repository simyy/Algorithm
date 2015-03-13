/*
 * CVNode.h
 *
 *  Created on: 2014/9/10
 *      Author: yxd123
 *
 * @class CVNode
 * 一致性哈希的虚拟节点（需要映射的节点）
 */
#include "Node.h"

#ifndef CVNODE_H_
#define CVNODE_H_

class CVNode{
public:
	CVNode(){}
	~CVNode(){}

	/* 设置ID */
	void setID(char* pid);

	/* 获取ID */
	char* getID();

	/* 设置哈希值 */
	void setHash(long hash);

	/* 获取哈希值 */
	long getHash();

protected:

private:
	char id[100];
	long  hash;		//哈希值
};

#endif /* CvNODE_H_ */
