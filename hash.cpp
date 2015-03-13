#include<string>
#include<set>
#include<stdlib.h>
#include<iostream>

using namespace std;

/********************************
 *加法哈希
 *@key   输入字符串
 *@prime 素数
 ********************************/
int additiveHash(string key, int prime)
{
	int hash, i;
	for(hash = key.length(), i = 0; i < key.length(); ++i)
	{
		hash += int(key.at(i));
	}
	return (hash%prime);
}

/********************************
 *旋转哈希（移位）
 *@key   输入字符串
 *@prime 素数
 ********************************/
int rotatingHash(string key, int prime)
{
	int hash, i;
	for(hash = key.length(), i = 0; i < key.length(); ++i)
	{
		hash = (hash << 4)^(hash >> 28)^int(key.at(i));
	}
	return (hash%prime);
}

/********************************
 *乘法哈希
 *@key   输入字符串
 *@prime 素数
 ********************************/
int bernstein(string key)
{
	int hash, i;
	for(hash = 0, i = 0; i < key.length(); ++i)
	{
		hash = 33*hash + int(key.at(i));
	}
	return hash;
}

/********************************
 *32位FNV算法(乘法)
 *@key   输入字符串
 *@prime 素数
 ********************************/
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

/**
 * JAVA自己带的算法

public static int java(String str) {
	int h = 0;
    int off = 0;
    int len = str.length();
    for (int i = 0; i < len; i++)
    {
        h = 31 * h + str.charAt(off++);
    }
    return h;
}
*/

int main()
{
	int result = 0;
	//result = additiveHash("hello", 111);
	//result = rotatingHash("helloworld", 111);
	//result = bernstein("hello");
	//result = FNVHash("hello");
	//char x = 'a', y = 'z', z = 'A', q = 'Z';
	//cout<<int(x)<<" "<<int(y)<<" "<<int(z)<<" "<<int(q)<<endl;
	//cout<<result;
	//97 122
	set<int> mySet;
	int sameNum = 0;
	for(int i = 0; i < 1000; ++i)
	{
		string s = "";
		int n = rand()%10 + 1;//位数
		for(int j = 0; j < n; ++j)
		{
			int tmp = rand()%25 + 97;
			char ttmp = char(tmp);
			s = s + ttmp;
		}
		int value = rotatingHash(s, 688);
		cout<<value<<" "<<s<<endl;
		if(!mySet.insert(value).second)
			sameNum += 1;
	}
	cout<<"same num: "<<sameNum<<endl;
	return 0;
}



