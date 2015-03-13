/*
 * main.cpp
 *
 *  Created on: 2014/9/11
 *      Author: yxd123
 */
#include "ConsistHash.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
	ConsistentHash *csthash = new ConsistentHash();

	CNode* p;
	p = new CNode();
	p->setID("192.168.0.1");
	p->setHash(713035665);
	csthash->addNode(p);

	p = new CNode();
	p->setID("192.168.0.2");
	p->setHash(1426071330);
	csthash->addNode(p);

	p = new CNode();
	p->setID("192.168.0.3");
	p->setHash(2139106996);
	csthash->addNode(p);

	long min = 0;
	long max = 0;

	for(int i = 0; i < 30; ++i)
	{
		char id[100];
		sprintf(id, "%d.%d.%d.%d\0",rand()%255,rand()%255,rand()%255,rand()%255);
		long hash = abs(csthash->getHash(id));
		//cout<<id<<" "<<hash<<endl;
		CVNode *q;
		q = new CVNode();
		q->setID(id);
		q->setHash(hash);
		csthash->addVNode(q);

		if(i == 0)
		{
			min = hash;
			max = hash;
		}
		else
		{
			if(min > hash)
				min = hash;
			if(max < hash)
				max = hash;
		}
	}

	cout<<csthash->getVNodesNum()<<endl;

	csthash->showNode();

	p = new CNode();
	p->setID("192.168.0.4");
	p->setHash(1039106996);
	csthash->addNode(p);

	csthash->showNode();

	//cout<<"max: "<<max<<endl;
	//cout<<"min: "<<min<<endl;

	p = new CNode();
	p->setID("192.168.0.4");
	csthash->delNode(p);

	csthash->showNode();

	cout<<"Finished!"<<endl;

	return 0;
}


