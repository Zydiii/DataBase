#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<set>
#include"BTree.h"

using namespace std;
set<BTnode*> changed; //用来存储更改过的节点

/*函数名：getKeyindex(int key)
 *功能：得到一特定键值在节点中索引位置
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

/*函数名：get_parent()
 *功能：得到节点的父节点
 */
BTnode *BTnode::get_parent()
{
	return parent;
}

/*函数名：BTnode()
 *功能：构造函数
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

/*函数名：~BTnode()
 *功能：析构函数
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

/*函数名：clear()
 *功能：清除节点子节点信息
 */
void BTnode:: clear()
{
	for (int i = 0; i < keyNum; i++)
	{
		if(pchild!=NULL)
		   pchild[i] = 0;
	}
}

/*函数名：BTree()
 *功能：构造函数
 */
BTree::BTree()
{
	root = NULL;
}

/*函数名：~BTree()
 *功能：析构函数
 */
BTree::~BTree()
{
	clear();
}

/*函数名：BTree_insert(Data value)
 *功能：插入value
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

/*函数名：SplitBlock(BTnode* node_parent, int child_index, BTnode* node_child)
 *功能：分裂节点
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

/*函数名：Notfull_insert(BTnode* node, Data value)
 *功能：插入value
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

/*函数名：contain(int key)
 *功能：判断树中是否存在key
 */
bool BTree::contain(int key)
{
	if (BTree_find(root, key) != NULL)
		return true;
	return false;
}

/*函数名：BTree_find(BTnode* node, int key)
 *功能：寻找含有key值得节点
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

/*函数名：BTree_delete(int key)
 *功能：删除树中key
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

/*函数名：MergeBlock(BTnode* node_parent, int child_index)
 *功能：合并
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
 
/*函数名：getprev(BTnode* node)
 *功能：在左边的兄弟节点中找一个最大值
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
 
/*函数名：getnext(BTnode* node)
 *功能：在右边的兄弟节点中找一个最小值
 */
Data BTree::getnext(BTnode* node)
{
	while (!node->isleaf)
	{
		node = node->pchild[0];
	}
	return node->keyvalue[0];
}
 
/*函数名：BTree_deletebalance(BTnode* node, int key)
 *功能：删除并平衡
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

/*函数名：fetch(int key)
 *功能：得到key对应得value
 */
int BTree::fetch(int key)
{
	long result = BTree_get(root, key);
	return result;
}

/*函数名：BTree_get(BTnode* node, int key)
 *功能：得到key对应得value
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

/*函数名：clear()
 *功能：清除
 */
void BTree::clear()
{
    if (root != NULL)
	{
		root->clear();
	}
}

/*函数名：get_id(BTnode* node)
 *功能：得到每个节点的id
 */
string BTree::get_id(BTnode* node)
{
	string i = "";
	id(node, root, i);
	return i;
}

/*函数名：id(BTnode* node, BTnode* n, string &i)
 *功能：得到每个节点的id
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

/*函数名：set_file()
 *功能：存储索引文件
 */
void BTree::set_file()
{
	index(root);
}

/*函数名：index(BTnode* node)
 *功能：存储索引文件
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

/*函数名：get_root()
 *功能：得到根节点
 */
BTnode* BTree::get_root()
{
	return  root;
}

/*函数名：read()
 *功能：得到变化的节点
 */
set<BTnode*> BTree:: read()
{
	return changed;
}