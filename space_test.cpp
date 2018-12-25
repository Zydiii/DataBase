#include"test.h"
#include"database.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
static const int TIMES = 1000;

//ø’º‰≤‚ ‘
void space_test()
{
	database db;
	map<int, string> test;
	set_rand(TIMES, test);
	rand_put(db, test);
	db.flush();
	rand_move_all(db, test);
	db.flush();
	map<int, string> Test;
	set_rand(TIMES, Test);
	rand_put(db, Test);
	db.flush();
	db.close();
}
