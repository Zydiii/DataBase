#include"test.h"
#include"database.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>

static const int nrec = 50;

/*函数名：key_test(map<int, string> test, int pos)
*功能：得到随机查询key
*/
int key_test(map<int, string> test, int pos)
{
	pos %= test.size();
	map<int, string>::iterator it = test.begin();
	for (int i = 0; i < pos; i++)
	{
		it++;
	}
	return it->first;
}

//综合测试
void round_test()
{
	vector<int> pos;
	set_pos(pos);
	int flag = 0;
	database db;
	map<int, string> test;
	set_rand(nrec, test);
	rand_put(db, test);
	rand_fetch(db, test);
	for (int i = 1; i <= nrec * 5; i++)
	{
		srand((int)time(NULL));
		int key = key_test(test, pos[flag]);
		flag++;
		cout << db.fetch(key) << endl;
		if (i % 37 == 0)
		{
			key = key_test(test, pos[flag]);
			flag++;
			cout<<db.move(key)<<endl;
		}
		if (i % 11 == 0)
		{
			key = pos[flag];
			flag++;
			string data;
			int length = rand() % 50;
			set_value(length, data);
			if (test.count(key) != 1)
			{
				test[key] = data;
			}
			cout<<db.add(key, data)<<endl;
			cout << db.fetch(key) << endl;
		}
		if (i % 17 == 0)
		{
			key = key_test(test, pos[flag]);
			flag++;
			string data;
			int length = rand() % 50;
			set_value(length, data);
			cout << db.change(key, data) << endl;
		}
	}
	db.close();
}