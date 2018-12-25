#include"test.h"
#include"database.h"
#include<iostream>
#include<time.h>
using namespace std;
static const int TIMES = 1000;

/*��Ѱ������
 *����������洢һ�����������ݿ��У����һ�ض����ݣ�����������ɾ���������ݣ����в��ҡ�ɾ�������ҡ��޸Ĳ���
 */
void abnormal_test()
{
	srand((int)time(NULL));
	database db;
	map<int, string> test;
	set_rand(TIMES, test);
	rand_put(db, test);
	int key;
	string value;
	int length;
	do
	{
		key = rand();
	} while (test.count(key) == 1);
	length = rand()%50;
	set_value(length, value);
	cout << db.add(key, value) << endl;
	cout << db.fetch(key) << endl;
	cout << db.move(key) << endl;
	cout << db.fetch(key) << endl;
	length = rand()%50;
	set_value(length, value);
	cout << db.change(key, value) << endl;
	cout << db.fetch(key) << endl;
	length = rand()%50;
	set_value(length, value);
	cout << db.add(key, value) << endl;
	cout << db.fetch(key) << endl;
	db.close();
}