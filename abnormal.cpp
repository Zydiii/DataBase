#include"test.h"
#include"database.h"
#include<iostream>
#include<time.h>
using namespace std;
static const int TIMES = 1000;

/*非寻常测试
 *方法：随机存储一定数据于数据库中，添加一特定数据，查找它，再删除这条数据，进行查找、删除、查找、修改操作
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