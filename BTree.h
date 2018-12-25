#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<set>
using namespace std;

//�ڵ����
static const int m = 64;  
//���ڵ��ֵ
static const int key_max = 2 * m - 1;
//��С�ڵ��ֵ��
static const int key_min = m - 1;
//����ӽڵ���
static const int child_max = key_max + 1;
//�����ӽڵ���
static const int child_min = key_min + 1;

//Data
typedef struct Data
{
	int key;
	long value;
}Data;

//BTnode
class BTnode
{
friend class BTree;
public:
	BTnode();
	~BTnode();
	void clear();
	BTnode *get_parent();
	int getKeyindex(int key);
private:
	bool isleaf;
	int keyNum;
	int count;
	int height;
	BTnode* parent;
	BTnode* pchild[child_max];
	Data   keyvalue[key_max];
};

//BTree
class BTree
{
public:
	BTree();
	~BTree();
	//����
	bool BTree_insert(Data value);
	void SplitBlock(BTnode* node_parent, int child_index, BTnode* node_child);
	void Notfull_insert(BTnode* node, Data value);
	//��ѯ
	bool contain(int key);
	BTnode* BTree_find(BTnode* node, int key);
	int fetch(int key);
	int BTree_get(BTnode* node, int key);
	//ɾ��
	bool BTree_delete(int key);
	void MergeBlock(BTnode* node_parent, int child_index);
	Data getprev(BTnode* node);
	Data getnext(BTnode* node);
	void BTree_deletebalance(BTnode* node, int key);
	//д�����
	void set_file();
	void index(BTnode* node);
	void clear();
	string get_id(BTnode* node);
	void id(BTnode* node, BTnode* n, string &i);
	std::set<BTnode*> read();
	BTnode* get_root();
private:
	BTnode * root;//���ڵ�
};