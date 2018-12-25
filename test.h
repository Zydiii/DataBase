#pragma once
#include<vector>
#include<fstream>
#include<string>
#include<set>
#include<map>
#include"database.h"
using namespace std;

//正确性测试
void correctness_test();
//非常规测试
void abnormal_test();
//综合测试
void round_test();
//空间测试
void space_test();
//不同查询频率数据量测试
void popular_test();
//菜单
void menu();
void statement();
void choice();
//设置随机向量
void set_pos(vector<int> &pos);
void set_popular_pos(vector<int> &pos);
//设置随机数据
void set_value(const int length, string &value);
void set_rand(const int TIMES, map<int, string> &test);
//随机存储
void rand_put(database&db, map<int, string>test);
//随机删除
void rand_move(database&db, map<int, string>test);
//随机查询
void rand_fetch(database&db, map<int, string>test);
//随机更改
void rand_change(database&db, map<int, string> test);
//全部删除
void rand_move_all(database&db, map<int, string>test);
//不同查询频率数据存储
void set_poular(database&db, int TIMES);
