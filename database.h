#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <queue>
#include "buffer.h"
#include "BTree.h"
using namespace std;

//数据库类
class database
{
public:
	database();
	~database();
	//更新
	void update();
	void Delete_Data();
	void Set_Data();
	void Find_Data(int pos, string &data);
	void index();
	void init();
	//查询
	string search(const string filename, const int val);
	string fetch(const int val);
	//添加
	string add(const int val, const string data);
	//删除
	string move(const int val);
	//更改
	string change(const int val, const string data);
	//范围查询
	vector<string> fetch_range(int val1, int val2);
	void read();
	//更新与磁盘操作
	set<BTnode*> get_change();
	void flush();
	void read_file(string name);
	//读取数据文件
	void open_data();
	//关闭数据库
	void close();
private:
	Buffer buffer;   //缓存
	BTree Keys;   //B树
	fstream valuefile;   //数据文件
}; 