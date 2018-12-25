#include"BTree.h"
#include"test.h"
#include"database.h"
#include<iostream>
#include<random>
#include<vector>
#include<string>
#include<map>
#include<time.h>

//不同频率查询数据测试
void popular_test()
{
	srand((int)time(NULL));
	database db;
	vector<int> keys;
	set_popular_pos(keys);
	int TIMES = 5000;
	set_poular(db, TIMES);
	db.flush();
	for (int i = 0; i < keys.size(); i++)
	{
		db.fetch(i);
	}
	
}