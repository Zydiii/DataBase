#include"test.h"
#include"BTree.h"
#include"database.h"
#include<iostream>
#include<random>
#include<string>
#include<map>
#include<time.h>
int TIMES = 1000;

/*��ȷ�Բ���
*����������洢��ɾ�����޸ġ�����һ��������
*/
void correctness_test()
{
	srand((int)time(NULL));
	database db;
	map<int, string> test;
	set_rand(TIMES, test);
	clock_t start = clock();
	rand_put(db, test);
	clock_t finish = clock();
	double time = (finish - start) / 1000;
	cout << time << endl;
	start = clock();
	rand_move(db, test);
	finish = clock();
	time = (finish - start) / 1000;
	cout << time << endl;
	db.flush();
	start = clock();
	rand_put(db, test);
	finish = clock();
	time = (finish - start) / 1000;
	cout << time << endl;
	start = clock();
	rand_fetch(db, test);
	finish = clock();
	time = (finish - start) / 1000;
	cout << time << endl;
	start = clock();
	rand_change(db, test);
	finish = clock();
	time = (finish - start) / 1000;
	cout << time << endl;
	start = clock();
	rand_fetch(db, test);
	finish = clock();
	time = (finish - start) / 1000;
	cout << time << endl;
	map<int, string> Test;
	set_rand(TIMES, Test);
	rand_put(db, Test);
	rand_fetch(db, test);
	rand_fetch(db, Test);
	db.close();
}