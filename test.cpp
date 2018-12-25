#include"test.h"
#include"database.h"
#include<vector>
#include<fstream>
#include<string>
#include<set>
#include<map>
#include<time.h>
using namespace std;

/*��������set_value(const int length, string &value)
*���ܣ������������
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

/*��������set_rand(const int TIMES, map<int, string> &test)
*���ܣ��������<key, value>
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

/*��������rand_put(database &db, map<int, string> test)
*���ܣ�����洢
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

/*��������rand_move(database&db, map<int, string>test)
*���ܣ����ɾ��
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

/*��������rand_move_all(database&db, map<int, string>test)
*���ܣ�ȫ��ɾ��
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

/*��������rand_fetch(database&db, map<int, string>test)
*���ܣ������ѯ
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

/*��������rand_change(database&db, map<int, string> test)
*���ܣ�����޸�
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

/*��������set_pos(vector<int> &pos)
*���ܣ������������
*/
void set_pos(vector<int> &pos)
{
	for (int i = 0; i < 1000000; i++)
	{
		pos.push_back(i);
	}
	random_shuffle(pos.begin(), pos.end());
}

/*��������set_popular_pos(vector<int> &pos)
*���ܣ����ò�ͬ��ѯƵ������
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

/*��������set_poular(database &db, int TIMES)
*���ܣ����ò�ͬ��ѯƵ������
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