#pragma once
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <string>
#include <set>
using namespace std;

//»º´æÀà
class Buffer
{
public:
	Buffer();
	~Buffer();
	//´æ´¢
	void set_put(const int key, const string data);
	//É¾³ý
	void set_remove(const int key, const string data);
	//¶Á»º´æ
	void set_read(const int key, const string data);
	void read_update();
	//²éÑ¯
	bool check_buffer_put(const int key);
	bool check_buffer_remove(const int key);
	bool check_buffer_read(const int key);
	//get
	string buffer_get(const int key);
	string buffer_remove(const int key);
	string buffer_read(const int key);
	//Çå³ý
	void remove_erase(const int key);
	void put_erase(const int key);
	void read_erase(const int key);
	//¸ü¸Ä
	void change_put(const int key, const string data);
	//ÈÝÁ¿
	int buffer_size();
	int put_size();
	int read_size();
	int remove_size();
	//Çå¿Õ
	void put_clear();
	void remove_clear();
	void clear();
	//µÃµ½»º´æ
	map<int, string> read();
	map<int, string> put();
	map<int, string> remove();
private:
	map<int, string> put_buffer;  //´æ´¢»º´æ
	map<int, string> remove_buffer;  //É¾³ý»º´æ
	map<int, string> read_buffer;   //¶Á»º´æ
};