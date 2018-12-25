#include"test.h"
#include"database.h"
#include<vector>
#include<fstream>
#include<string>
#include<set>
#include<map>
#include<time.h>
using namespace std;

/*函数名：set_value(const int length, string &value)
*功能：设置随机数据
*/
void set_value(const int length, string &value)
{
	for (int j = 0; j < length; j++)
	{
		switch (rand() % 3)
		{
		case1:
			{
				value += 'A' + rand() % 26;
				break;
			}
		case 2:
		{
			value += 'a' + rand() % 26;
			break;
		}
		default:
		{
			value += '0' + rand() % 10;
			break;
		}
		}
	}
}

/*函数名：set_rand(const int TIMES, map<int, string> &test)
*功能：设置随机<key, value>
*/
void set_rand(const int TIMES, map<int, string> &test)
{
	set<int> used;
	vector<int> pos;
	set_pos(pos);
	srand((int)time(NULL));
	ofstream t("test.txt" , ios::app | ios::binary);
	int key;
	string value="";
	int length;
	for (int i = 0; i < TIMES; i++)
	{
		do
		{
		key = rand();
		} while (used.count(key) == 1);
		used.insert(key);
		key = pos[i];
		length = rand() % 50;
		set_value(length, value);
		t << key << "   " << value << "\n";
		test[key] = value;
		value = "";
	}
	t.close();
}

/*函数名：rand_put(database &db, map<int, string> test)
*功能：随机存储
*/
void rand_put(database &db, map<int, string> test)
{
	map<int, string>::iterator it = test.begin();
	int flag = 1;
	while (it != test.end())
	{
		db.add(it->first, it->second);
		it++;
		flag++;
	}
	cout << "Insertion test finished." << endl;
	db.flush();
}

/*函数名：rand_move(database&db, map<int, string>test)
*功能：随机删除
*/
void rand_move(database&db, map<int, string>test)
{
	map<int, string>::iterator it = test.begin();
	it = test.begin();
	int flag = 1;
	while (it != test.end())
	{
		if (rand() % 5 == 0)
		{
			db.move(it->first);
		}
		it++;
	}
	cout << "Remove test finished." << endl;
	db.flush();
}

/*函数名：rand_move_all(database&db, map<int, string>test)
*功能：全部删除
*/
void rand_move_all(database&db, map<int, string>test)
{
	map<int, string>::iterator it = test.begin();
	it = test.begin();
	while (it != test.end())
	{
			db.move(it->first);
		it++;
	}
	cout << "Remove test finished." << endl;
}

/*函数名：rand_fetch(database&db, map<int, string>test)
*功能：随机查询
*/
void rand_fetch(database&db, map<int, string>test)
{
	map<int, string>::iterator it = test.begin();
	it = test.begin();
	int flag = 1;
	while (it != test.end())
	{
		db.fetch(it->first);
		it++;
	}
	cout << "Get test finished." << endl;
}

/*函数名：rand_change(database&db, map<int, string> test)
*功能：随机修改
*/
void rand_change(database&db, map<int, string> test)
{
	map<int, string>::iterator it = test.begin();
	it = test.begin();
	int flag = 1;
	while (it != test.end())
	{
		if (rand() % 3 == 0)
		{
			string value = "";
			int length = rand() % 50;
			set_value(length, value);
			db.change(it->first, value);
		}
		it++;
	}
	cout << "Modification test finished." << endl;
	db.flush();
}

/*函数名：set_pos(vector<int> &pos)
*功能：设置随机向量
*/
void set_pos(vector<int> &pos)
{
	for (int i = 0; i < 1000000; i++)
	{
		pos.push_back(i);
	}
	random_shuffle(pos.begin(), pos.end());
}

/*函数名：set_popular_pos(vector<int> &pos)
*功能：设置不同查询频率向量
*/
void set_popular_pos(vector<int> &pos)
{
	for (int i = 0; i < 5000; i++)
	{
		if (i % 100 == 0)
		{
			for (int j = 0; j < 100; j++)
			{
				pos.push_back(i);
			}
		}
		else
			pos.push_back(i);
	}
	random_shuffle(pos.begin(), pos.end());
}

/*函数名：set_poular(database &db, int TIMES)
*功能：设置不同查询频率数据
*/
void set_poular(database &db, int TIMES)
{
	for (int i = 0; i < TIMES; i++)
	{
		string value = "";
		int length = rand() % 50;
		set_value(length, value);
		db.add(i, value);
	}
}