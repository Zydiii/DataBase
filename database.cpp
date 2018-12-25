#include "database.h"
#include "BTree.h"
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <set>

map<int, int> moved;   //ɾ�����λ�úͳ���

/*��������database()
*���ܣ����캯��
*/
database::database()
{
	init();
	open_data();
}

/*��������open_data()
*���ܣ��������ļ�
*/
void database::open_data()
{
	this->valuefile.open("value.dat", ios::in|ios::out |ios::binary);
	int pos = this->valuefile.tellg();
}

/*��������~database()
*���ܣ���������
*/
database::~database()
{
	this->buffer.clear();
	this->Keys.clear();
}

/*��������init()
*���ܣ���ʼ�����ڵ�
*/
void database::init()
{
	ifstream keyFile("key.index", ios::binary);
	string x;
	int key, data;
	while (getline(keyFile, x))
	{
		if (x == "*")
			break;
		else
		{
			istringstream is(x);
			is >> key >> data;
			Data y;
			y.key = key;
			y.value = data;
			Keys.BTree_insert(y);
		}
	}

}

/*��������search(const string filename, const int val)
*���ܣ����������ļ�
*/
string database::search(const string filename, const int val)
{
	ifstream keyFile(filename, ios::binary);
	string x;
	int flag = 0, flag2 = 0, found = 0;
	int index = 0;
	int t = 0;
	int key, data;
	while (getline(keyFile, x))
	{
		if (x == "*")
		{
			flag = 1;
			flag2 = 1;
			break;
		}
		istringstream is(x);
		is >> key >> data;
		Data y;
		y.key = key;
		y.value = data;
		Keys.BTree_insert(y);
		if (key == val)
		{
			found = 1;
		}
		else if (key < val)
		{
			index++;
			continue;
		}
		else
			break;
	}
	if (flag2 == 0)
	{
		while (getline(keyFile, x))
		{
			if (x == "*")
			{
				flag = 1;
				break;
			}
			istringstream is(x);
			is >> key >> data;
			Data y;
			y.key = key;
			y.value = data;
			Keys.BTree_insert(y);
		}
	}
	if (found == 1)
		return "True";
	if (flag == 0)
		return "NONE";
	else
	{
		while (getline(keyFile, x))
		{
			if (t == index)
			{
				return search(x, val);
			}
			else
				t++;
		}
	}
}

/*��������fetch(const int val)
*���ܣ���ѯ
*/
string database::fetch(const int val)
{
	if (buffer.check_buffer_read(val))
	{
		return buffer.buffer_get(val);
	}
	if (buffer.check_buffer_remove(val))
		return "Document dosen't exist.";
	if (buffer.check_buffer_put(val))
	{
		return buffer.buffer_get(val);
	}
	int result = Keys.fetch(val);
	if (result != -1)
	{
		string data;
		Find_Data(result, data);
		return data;
	}
	if (search("key.index", val) == "NONE")
	{
		return "Document dosen't exist.";
	}
	else
	{
		string data;
		Find_Data(Keys.fetch(val), data);
		return data;
	}
}

/*��������add(const int val, const string data)
*���ܣ��������
*/
string database::add(const int val, const string data)
{
	if (buffer.check_buffer_remove(val))
	{
		buffer.remove_erase(val);
		return "Successful Insertion.";
	}
	fetch(val);
	if (buffer.check_buffer_put(val) || Keys.contain(val))
		return "Document exists.";
	buffer.set_put(val, data);
	buffer.set_read(val, data);
	return "Successful Insertion.";
}

/*��������move(const int val)
*���ܣ�ɾ������
*/
string database::move(const int val)
{
	int flag1, flag2;
	if (!buffer.check_buffer_put(val))
		flag1 = 0;
	else
	{
		buffer.put_erase(val);
		flag1 = 1;
	}
	if (!Keys.contain(val))
	{
		flag2 = 0;
		fetch(val);
	}
	else
	{
		int result = Keys.fetch(val);
		string data;
		Find_Data(result, data);
		buffer.set_remove(val, data);
		moved[data.length()] = result;
		flag2 = 1;
	}
	if (buffer.check_buffer_read(val))
	{
		buffer.read_erase(val);
	}
	if (flag1 == 0 && flag2 == 0)
		return "Document doesn't exist.";
	return "Successfully remove.";
}

/*��������fetch_range(int val1, int val2)
*���ܣ���Χ����
*/
vector<string> database::fetch_range(int val1, int val2)
{
	if (val1 > val2)
	{
		int val = val2;
		val2 = val1;
		val1 = val;
	}
	vector<string> results;
	vector<int> result;
	for (int i = val1; i <= val2; i++)
	{
		if (buffer.check_buffer_read(i))
		{
			results.push_back(buffer.buffer_read(i));
			continue;
		}
		int x = Keys.fetch(i);
		if (x == -1)
		{
			fetch(i);
			x = Keys.fetch(i);
			if (x != -1)
			{
				result.push_back(x);
			}
		}
		else
			result.push_back(x);
	}
	for (int i = 0; i < result.size(); i++)
	{
		string data;
		Find_Data(result[i], data);
		results.push_back(data);
	}
	map<int, string> put = buffer.put();
	map<int, string>::iterator it = put.begin();
	while (it != put.end())
	{
		if (val1 <= it->first && val2 >= it->first)
			results.push_back(it->second);
		it++;
	}
	return results;
}

/*��������change(const int val, const string data)
*���ܣ���������
*/
string database::change(const int val, const string data)
{
	fetch(val);
	if (!buffer.check_buffer_put(val) && !Keys.contain(val))
		return "Document doesn't exist.";
	if (buffer.check_buffer_remove(val))
		return "Document doesn't exist.";
	if (buffer.check_buffer_put(val))
	{
		buffer.change_put(val, data);
		return "Successful modification.";
	}
	move(val);
	flush();
	buffer.set_put(val, data);
	if (buffer.check_buffer_remove(val))
		buffer.remove_erase(val);
	if (buffer.check_buffer_read(val))
		buffer.set_read(val, data);
	return "Successful modification.";
}

/*��������update()
*���ܣ���������
*/
void database::update()
{
	if (buffer.buffer_size() >= 100)
	{
		flush();
	}
	buffer.read_update();
}

/*��������Set_Data()
*���ܣ���������ӽ������ļ�
*/
void database::Set_Data()
{
	this->valuefile.seekp(0, ios::end);
	int pos;
	int reuse;
	map<int, string> put = buffer.put();
	map<int, string>::iterator it = put.begin();
	while (it != put.end())
	{
		if (moved.count(it->second.length()) == 1)
		{
			reuse = moved.find(it->second.length())->second;
			pos = this->valuefile.tellp();
			Data x;
			x.key = it->first;
			x.value = reuse;
			Keys.BTree_insert(x);
			this->valuefile.seekp(reuse, ios::beg);
			moved.erase(it->second.length());
			this->valuefile << it->second << "\n";
			this->valuefile.seekp(pos, ios::beg);
		}
		else
		{
			pos = this->valuefile.tellp();
			Data x;
			x.key = it->first;
			x.value = pos;
			Keys.BTree_insert(x);
			this->valuefile << it->second << "\n";
		}
		it++;
	}
}

/*��������Delete_Data()
*���ܣ������ݴ������ļ�ɾ��
*/
void database::Delete_Data()
{
	int pos;
	int result;
	map<int, string> remove = buffer.remove();
	map<int, string>::iterator it = remove.begin();
	while (it != remove.end())
	{
		result = Keys.fetch(it->first);
		pos = result;
		valuefile.seekp(pos, ios::beg);
		string x;
		getline(valuefile, x);
		valuefile.seekp(pos, ios::beg);
		string k = "";
		for (int i = 0; i < x.length(); i++)
		{
			k += " ";
		}
		valuefile << k;
		Keys.BTree_delete(it->first);
		it++;
	}
}

/*��������flush()
*���ܣ�����
*/
void database::flush()
{
	read_file("key.index");
	if (buffer.remove_size() > 0)
	{
		Delete_Data();
		buffer.remove_clear();
	}
	if (buffer.put_size() > 0)
	{
		Set_Data();
		buffer.put_clear();
	}
	Keys.set_file();
}

/*��������Find_Data(int pos, string &data)
*���ܣ��������ļ���������
*/
void database::Find_Data(int pos, string &data)
{
	string t;
	this->valuefile.seekg(pos, ios::beg);
	getline(valuefile, data);
}

/*��������index()
*���ܣ�������д�����
*/
void database::index()
{
	Keys.set_file();
}

/*��������close()
*���ܣ��ر����ݿ�
*/
void database::close()
{
	flush();
	this->valuefile.close();
}

/*��������read()
*���ܣ��õ����ĵĽڵ�
*/
void database::read()
{
	set<BTnode*> t = get_change();
	if (t.size() == 0)
		return;
	set<BTnode*> ::iterator it = t.begin();
	set<BTnode*> k;
	while (it!=t.end())
	{
		BTnode *node;
		node = *it;
		do
		{
			node = node->get_parent();
			if (node == Keys.get_root())
				break;
		} while (t.count(node)==1);
		if (k.count(node) == 1)
		{
			continue;
		}
		else 
		{
			string name = Keys.get_id(node);
			read_file(name);
			k.insert(node);
		}
		it++;
	}
}

/*��������read_file(string name)
*���ܣ����������ļ�
*/
void database::read_file(string name)
{
	ifstream keyFile(name, ios::binary);
	string x;
	int flag = 0;
	int index = 0;
	int t = 0;
	int key, data;
	while (getline(keyFile, x))
	{
		if (x == "*")
		{
			flag = 1;
			break;
		}
		istringstream is(x);
		is >> key >> data;
		Data y;
		y.key = key;
		y.value = data;
		Keys.BTree_insert(y);
	}
	if (flag == 0)
	{
		return;
	}
	else
	{
		while (getline(keyFile, x))
		{
			read_file(x);
		}
	}
}

/*��������get_change()
*���ܣ��õ����Ľڵ�
*/
set<BTnode*> database::get_change()
{
	return Keys.read();
}