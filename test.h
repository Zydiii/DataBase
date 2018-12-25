#pragma once
#include<vector>
#include<fstream>
#include<string>
#include<set>
#include<map>
#include"database.h"
using namespace std;

//��ȷ�Բ���
void correctness_test();
//�ǳ������
void abnormal_test();
//�ۺϲ���
void round_test();
//�ռ����
void space_test();
//��ͬ��ѯƵ������������
void popular_test();
//�˵�
void menu();
void statement();
void choice();
//�����������
void set_pos(vector<int> &pos);
void set_popular_pos(vector<int> &pos);
//�����������
void set_value(const int length, string &value);
void set_rand(const int TIMES, map<int, string> &test);
//����洢
void rand_put(database&db, map<int, string>test);
//���ɾ��
void rand_move(database&db, map<int, string>test);
//�����ѯ
void rand_fetch(database&db, map<int, string>test);
//�������
void rand_change(database&db, map<int, string> test);
//ȫ��ɾ��
void rand_move_all(database&db, map<int, string>test);
//��ͬ��ѯƵ�����ݴ洢
void set_poular(database&db, int TIMES);
