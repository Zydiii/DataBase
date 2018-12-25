#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<set>
#include"BTree.h"

using namespace std;
set<BTnode*> changed; //�����洢���Ĺ��Ľڵ�

/*��������getKeyindex(int key)
 *���ܣ��õ�һ�ض���ֵ�ڽڵ�������λ��
 */
int BTnode::getKeyindex(int key)
{
	int left = 0;
	int right = keyNum;
	int current;
	while (left != right)
	{
		current = (left + right) / 2;
		int currentKey = keyvalue[current].key;
		if (key > currentKey)
		{
			left = current + 1;
		}
		else
		{
			right = current;
		}
	}
	return left;
}

/*��������get_parent()
 *���ܣ��õ��ڵ�ĸ��ڵ�
 */
BTnode *BTnode::get_parent()
{
	return parent;
}

/*��������BTnode()
 *���ܣ����캯��
 */
BTnode::BTnode()
{
	keyNum = 0;
	parent = NULL;
	isleaf = true;
	for (int i = 0; i < child_max; i++)
	{
		pchild[i] = NULL;
	}
	for (int i = 0; i < key_max; i++)
	{
		keyvalue[i].key = 0;
		keyvalue[i].value = 0;
	}
}

/*��������~BTnode()
 *���ܣ���������
 */
BTnode::~BTnode()
{
	parent = NULL;
	for (int i = 0; i < keyNum; i++)
	{
		pchild[i] = NULL;
	}
	keyNum = 0;
}

/*��������clear()
 *���ܣ�����ڵ��ӽڵ���Ϣ
 */
void BTnode:: clear()
{
	for (int i = 0; i < keyNum; i++)
	{
		if(pchild!=NULL)
		   pchild[i] = 0;
	}
}

/*��������BTree()
 *���ܣ����캯��
 */
BTree::BTree()
{
	root = NULL;
}

/*��������~BTree()
 *���ܣ���������
 */
BTree::~BTree()
{
	clear();
}

/*��������BTree_insert(Data value)
 *���ܣ�����value
 */
bool BTree:: BTree_insert(Data value)
{
		if (contain(value.key))
		{
			return false;
		}
		else
		{
			if (root == NULL)
			{
				root = new BTnode();
			}
			if (root->keyNum == key_max)
			{
				BTnode* newnode = new BTnode();
				newnode->pchild[0] = root;
				newnode->isleaf = false;
				SplitBlock(newnode, 0, root);
				root = newnode;
			}
			Notfull_insert(root, value);
			return true;
		}
}

/*��������SplitBlock(BTnode* node_parent, int child_index, BTnode* node_child)
 *���ܣ����ѽڵ�
 */
void  BTree:: SplitBlock(BTnode* node_parent, int child_index, BTnode* node_child)
{
	BTnode* node_right = new BTnode();
	node_right->isleaf = node_child->isleaf;
	node_right->keyNum = key_min;
	int i;

	for (i = 0; i < key_min; i++)
	{
		node_right->keyvalue[i] = node_child->keyvalue[i + child_min];
	}

	if (!node_child->isleaf)
	{
		for (i = 0; i < child_min; i++)
		{
			node_right->pchild[i] = node_child->pchild[i + child_min];
			node_child->pchild[i + child_min]->parent = node_right->pchild[i];
		}
	}
	node_child->keyNum = key_min;
	for (i = node_parent->keyNum; i > child_index; --i)
	{
		node_parent->pchild[i + 1] = node_parent->pchild[i];
		node_parent->keyvalue[i] = node_parent->keyvalue[i - 1];
	}

		node_parent->keyNum++;
		node_parent->pchild[child_index + 1] = node_right;
		node_parent->keyvalue[child_index] = node_child->keyvalue[key_min];
	}

/*��������Notfull_insert(BTnode* node, Data value)
 *���ܣ�����value
 */
void BTree::Notfull_insert(BTnode* node, Data value)
{

	int node_keynum = node->keyNum;
	if (node->isleaf)
	{
		while (node_keynum > 0 && value.key < node->keyvalue[node_keynum - 1].key)
		{
			node->keyvalue[node_keynum] = node->keyvalue[node_keynum - 1];
			--node_keynum;
		}
		node->keyvalue[node_keynum] = value;
		node->keyNum++;
		changed.insert(node);
	}
	else
	{
		while (node_keynum > 0 && value.key < node->keyvalue[node_keynum - 1].key)
		{
			--node_keynum;
		}

		BTnode* node_child = node->pchild[node_keynum];
		if (node_child->keyNum == key_max)
		{
			changed.insert(node);
			SplitBlock(node, node_keynum, node_child);
			if (value.key > node->keyvalue[node_keynum].key)
			{
				node_child = node->pchild[node_keynum + 1];
			}
		}
		Notfull_insert(node_child, value);
	}
}

/*��������contain(int key)
 *���ܣ��ж������Ƿ����key
 */
bool BTree::contain(int key)
{
	if (BTree_find(root, key) != NULL)
		return true;
	return false;
}

/*��������BTree_find(BTnode* node, int key)
 *���ܣ�Ѱ�Һ���keyֵ�ýڵ�
 */
BTnode* BTree::BTree_find(BTnode* node, int key)
{
	if (node == NULL)
	{
		return NULL;
	}
	else
	{
		int i;
		for (i = 0; i < node->keyNum; i++)
		{
			if (key <= node->keyvalue[i].key)
			{
				break;
			}
		}

		if (i < node->keyNum && key == node->keyvalue[i].key)
		{
			return node;
		}
		else
		{
			if (node->isleaf)
			{
				return NULL;
			}
			else
			{
				return BTree_find(node->pchild[i], key);
			}
		}
	}
}

/*��������BTree_delete(int key)
 *���ܣ�ɾ������key
 */
bool BTree::BTree_delete(int key)
{
	if (!contain(key))
	{
		return false;
	}
	if (root->keyNum == 1)
	{
		if (root->isleaf)
		{
			delete root;
			root = NULL;
			return true;
		}
		else
		{
			BTnode* node_child1 = root->pchild[0];
			BTnode* node_child2 = root->pchild[1];

			if (node_child1->keyNum == key_min && node_child2->keyNum == key_min)
			{
				MergeBlock(root, 0);
				delete root;
				root = node_child1;
			}
		}
	}
	BTree_deletebalance(root, key);
}

/*��������MergeBlock(BTnode* node_parent, int child_index)
 *���ܣ��ϲ�
 */
void BTree::MergeBlock(BTnode* node_parent, int child_index)
{
	BTnode* node_child1 = node_parent->pchild[child_index];
	BTnode* node_child2 = node_parent->pchild[child_index + 1];

	node_child1->keyvalue[key_min] = node_parent->keyvalue[child_index];
	node_child1->keyNum = key_max;
	int i;
	for (i = 0; i < key_min; i++)
	{
		node_child1->keyvalue[child_min + i] = node_child2->keyvalue[i];
	}

	if (!node_child1->isleaf)
	{
		for (i = 0; i < child_min; i++)
		{
			node_child1->pchild[i + child_min] = node_child2->pchild[i];
		}
	}

	node_parent->keyNum--;
	for (i = child_index; i < node_parent->keyNum; i++)
	{
		node_parent->keyvalue[i] = node_parent->keyvalue[i + 1];
		node_parent->pchild[i + 1] = node_parent->pchild[i + 2];
	}
	delete node_child2;
	node_child2 = NULL;
}
 
/*��������getprev(BTnode* node)
 *���ܣ�����ߵ��ֵܽڵ�����һ�����ֵ
 */
Data BTree::getprev(BTnode* node)
{
	while (!node->isleaf)
	{
		node = node->pchild[node->keyNum];
	}
	node->keyNum--;
	return node->keyvalue[node->keyNum - 1];
}
 
/*��������getnext(BTnode* node)
 *���ܣ����ұߵ��ֵܽڵ�����һ����Сֵ
 */
Data BTree::getnext(BTnode* node)
{
	while (!node->isleaf)
	{
		node = node->pchild[0];
	}
	return node->keyvalue[0];
}
 
/*��������BTree_deletebalance(BTnode* node, int key)
 *���ܣ�ɾ����ƽ��
 */
void BTree::BTree_deletebalance(BTnode* node, int key)
{
	int i;
	for (i = 0; i < node->keyNum && key > node->keyvalue[i].key; i++){}
	if (i < node->keyNum && key == node->keyvalue[i].key)
	{
		if (node->isleaf)
		{
			node->keyNum--;
			for (; i < node->keyNum; i++)
			{
				node->keyvalue[i] = node->keyvalue[i + 1];
			}
			return;
		}
	    else
		{
			BTnode* node_left = node->pchild[i];
			BTnode* node_right = node->pchild[i + 1];
			if (node_left->keyNum >= child_min)
			{
				Data prev_replace = getprev(node_left);
				BTree_deletebalance(node_left, prev_replace.key);
				node->keyvalue[i] = prev_replace;
				changed.insert(node);
				return;
			}
			else if (node_right->keyNum >= child_min)
			{
				Data next_replace = getnext(node_right);
				BTree_deletebalance(node_right, next_replace.key);
				node->keyvalue[i] = next_replace;
				changed.insert(node);
				return;
			}
			else
			{
				MergeBlock(node, i);
				changed.insert(node);
				BTree_deletebalance(node_left, key);
			}
		}
	}
	else
	{
		BTnode* node_child = node->pchild[i];
		BTnode*  node_left = NULL;
		BTnode*  node_right = NULL;
		if (node_child->keyNum == key_min)
		{
			if (i >0)
			{
				node_left = node->pchild[i - 1];
			}
			if (i <= node->keyNum - 1)
			{
				node_right = node->pchild[i + 1];
			}
			int j;
			if (node_left && node_left->keyNum >= child_min)
			{
				changed.insert(node);
				for (j = node_child->keyNum; j > 0; j--)
				{
					node_child->keyvalue[j] = node_child->keyvalue[j - 1];
				}
				node_child->keyvalue[0] = node->keyvalue[i - 1];
				if (!node_left->isleaf)
				{
					for (j = node_child->keyNum + 1; j > 0; j--)
					{
						node_child->pchild[j] = node_child->pchild[j - 1];
					}
					node_left->pchild[node_left->keyNum]->parent = node_child->pchild[0];
					node_child->pchild[0] = node_left->pchild[node_left->keyNum];
				}
				node_child->keyNum++;
				node->keyvalue[i - 1] = node_left->keyvalue[node_left->keyNum - 1];
				node_left->keyNum--;
			}
			else if (node_right && node_right->keyNum >= child_min)
			{
				changed.insert(node);
				node_child->keyvalue[node_child->keyNum] = node->keyvalue[i];
			    node_child->keyNum++;
				node->keyvalue[i] = node_right->keyvalue[0];
				node_right->keyNum--;
				for (j = 0; j < node_right->keyNum; j++)
				{
					node_right->keyvalue[j] = node_right->keyvalue[j + 1];
				}
				if (!node_right->isleaf)
				{
					node_right->pchild[0]->parent = node_child->pchild[node_child->keyNum]->parent;
					node_child->pchild[node_child->keyNum] = node_right->pchild[0];
					for (j = 0; j < node_right->keyNum + 1; j++)
					{
						node_right->pchild[j + 1]->parent = node_right->pchild[j]->parent;
						node_right->pchild[j] = node_right->pchild[j + 1];

					}
				}
			}
			else if (node_left)
			{
				changed.insert(node);
				MergeBlock(node, i - 1);
				node_child = node_left;
			}
			else if (node_right)
			{
				changed.insert(node);
				MergeBlock(node, i);
			}
		}
		BTree_deletebalance(node_child, key);
	}
}

/*��������fetch(int key)
 *���ܣ��õ�key��Ӧ��value
 */
int BTree::fetch(int key)
{
	long result = BTree_get(root, key);
	return result;
}

/*��������BTree_get(BTnode* node, int key)
 *���ܣ��õ�key��Ӧ��value
 */
int BTree::BTree_get(BTnode* node, int key)
{
	if (node == NULL)
	{
		return -1;
	}
	else
	{
		int i;
		for (i = 0; i < node->keyNum; i++)
		{
			if (key <= node->keyvalue[i].key)
			{
				break;
			}
		}

	    if (i < node->keyNum && key == node->keyvalue[i].key)
		{
			return node->keyvalue[i].value;
		}
		else
		{
		    if (node->isleaf)
			{
				return -1;
			}
			else
			{
				return BTree_get(node->pchild[i], key);
			}
		}
	}
}

/*��������clear()
 *���ܣ����
 */
void BTree::clear()
{
    if (root != NULL)
	{
		root->clear();
	}
}

/*��������get_id(BTnode* node)
 *���ܣ��õ�ÿ���ڵ��id
 */
string BTree::get_id(BTnode* node)
{
	string i = "";
	id(node, root, i);
	return i;
}

/*��������id(BTnode* node, BTnode* n, string &i)
 *���ܣ��õ�ÿ���ڵ��id
 */
void BTree::id(BTnode* node, BTnode* n, string &i)
{
	if (n == NULL)
		return;
	if (n == node)
		return;
	else
	{
		int pos = node->keyNum;
		pos--;
		int key = node->keyvalue[pos].key;
		int index = n->getKeyindex(key);
		i += to_string(index);
		id(node, n->pchild[index], i);
	}
}

/*��������set_file()
 *���ܣ��洢�����ļ�
 */
void BTree::set_file()
{
	index(root);
}

/*��������index(BTnode* node)
 *���ܣ��洢�����ļ�
 */
void BTree::index(BTnode* node)
{
	if (node != NULL)
	{
		string name = "key" + get_id(node) + ".index";
		ofstream keyFile(name, ios::trunc | ios::binary);
		for (int i = 0; i < node->keyNum; i++)
		{
			keyFile << node->keyvalue[i].key << "  " << node->keyvalue[i].value << "\n";
		}
		if (!node->isleaf)
		{
			keyFile << "*" << "\n";
				for (int i = 0; i <= node->keyNum; i++)
				{
					if (node->pchild[i] != NULL)
					{
						name = "key" + get_id(node->pchild[i]) + ".index";
						keyFile << name << "\n";
						index(node->pchild[i]);
					}
				}
			}
			keyFile.close();
		}
		else
			return;
	}

/*��������get_root()
 *���ܣ��õ����ڵ�
 */
BTnode* BTree::get_root()
{
	return  root;
}

/*��������read()
 *���ܣ��õ��仯�Ľڵ�
 */
set<BTnode*> BTree:: read()
{
	return changed;
}