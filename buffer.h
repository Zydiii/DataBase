#pragma once
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <string>
#include <set>
using namespace std;

//������
class Buffer
{
public:
	Buffer();
	~Buffer();
	//�洢
	void set_put(const int key, const string data);
	//ɾ��
	void set_remove(const int key, const string data);
	//������
	void set_read(const int key, const string data);
	void read_update();
	//��ѯ
	bool check_buffer_put(const int key);
	bool check_buffer_remove(const int key);
	bool check_buffer_read(const int key);
	//get
	string buffer_get(const int key);
	string buffer_remove(const int key);
	string buffer_read(const int key);
	//���
	void remove_erase(const int key);
	void put_erase(const int key);
	void read_erase(const int key);
	//����
	void change_put(const int key, const string data);
	//����
	int buffer_size();
	int put_size();
	int read_size();
	int remove_size();
	//���
	void put_clear();
	void remove_clear();
	void clear();
	//�õ�����
	map<int, string> read();
	map<int, string> put();
	map<int, string> remove();
private:
	map<int, string> put_buffer;  //�洢����
	map<int, string> remove_buffer;  //ɾ������
	map<int, string> read_buffer;   //������
};