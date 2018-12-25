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

//���ݿ���
class database
{
public:
	database();
	~database();
	//����
	void update();
	void Delete_Data();
	void Set_Data();
	void Find_Data(int pos, string &data);
	void index();
	void init();
	//��ѯ
	string search(const string filename, const int val);
	string fetch(const int val);
	//���
	string add(const int val, const string data);
	//ɾ��
	string move(const int val);
	//����
	string change(const int val, const string data);
	//��Χ��ѯ
	vector<string> fetch_range(int val1, int val2);
	void read();
	//��������̲���
	set<BTnode*> get_change();
	void flush();
	void read_file(string name);
	//��ȡ�����ļ�
	void open_data();
	//�ر����ݿ�
	void close();
private:
	Buffer buffer;   //����
	BTree Keys;   //B��
	fstream valuefile;   //�����ļ�
}; 