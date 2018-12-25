#include"test.h"
#include"database.h"
#include<iostream>
#include <vector>
using namespace std;

//用户界面
void menu()
{
	statement();
	database db;
	int flag;
	int num = 0;
	while (true)
	{
		choice();
		cin >> flag;
		while (cin.fail())
		{
			cout << "Invalid choice! Try again:  ";
			cin.clear();
			cin.sync();
			cin.ignore(1024, '\n');
			cin >> flag;
		}
		switch (flag)
		{
		case 1:
		{
			int key;
			cout << "Enter the key:   ";
			cin >> key;
			while (cin.fail())
			{
				cout << "Invalid key! Try again:  ";
				cin.clear();
				cin.sync();
				cin.ignore(1024, '\n');
				cin >> key;
			}
			cout << db.fetch(key) << endl;
			break;
		}
		case 2:
		{
			int key1, key2;
			cout << "Enter the keys:" << endl;
			cout << "Key1:   ";
			cin >> key1;
			while (cin.fail())
			{
				cout << "Invalid key1! Try again:  ";
				cin.clear();
				cin.sync();
				cin.ignore(1024, '\n');
				cin >> key1;
			}
			cout << "Key2:   ";
			cin >> key2;
			while (cin.fail())
			{
				cout << "Invalid key2! Try again:  ";
				cin.clear();
				cin.sync();
				cin.ignore(1024, '\n');
				cin >> key2;
			}
			vector<string> values = db.fetch_range(key1, key2);
			if (values.size() == 0)
			{
				cout << "No document." << endl;
				break;
			}
			else
			{
				for (int i = 0; i < values.size(); i++)
				{
					cout << values[i] << endl;
				}
				break;
			}
		}
		case 3:
		{
			int key;
			string value;
			cout << "Enter key:   ";
			cin >> key;
			while (cin.fail())
			{
				cout << "Invalid key! Try again:  ";
				cin.clear();
				cin.sync();
				cin.ignore(1024, '\n');
				cin >> key;
			}
			cout << "Enter value:   ";
			cin >> value;
			cout << db.add(key, value) << endl;
			break;
		}
		case 4:
		{
			int key;
			cout << "Enter key:   ";
			cin >> key;
			while (cin.fail())
			{
				cout << "Invalid key! Try again:  ";
				cin.clear();
				cin.sync();
				cin.ignore(1024, '\n');
				cin >> key;
			}
			cout << db.move(key) << endl;
			break;
		}
		case 5:
		{
			int key;
			string value;
			cout << "Enter key:   ";
			cin >> key;
			while (cin.fail())
			{
				cout << "Invalid key! Try again:  ";
				cin.clear();
				cin.sync();
				cin.ignore(1024, '\n');
				cin >> key;
			}
			cout << "Enter value:   ";
			cin >> value;
			cout << db.change(key, value) << endl;
			break;
		}
		case 6:
		{
			db.flush();
			cout << "Successfully update." << endl;
			break;
		}
		case 7:
		{
			db.close();
			exit(0);
		}
		default:
			cout << "Invalid choice! Try again" << endl;
		}
		num++;
		if (num == 100)
		{
			db.update();
			num = 0;
		}
	}
	db.close();
}

void statement()
{
	cout << "*************************************" << endl;
	cout << " Hello! Database for <int, string>!  " << endl;
	cout << "*************************************" << endl;
	cout << "*    You can store your document    *" << endl;
	cout << "*    You can fetch the message      *" << endl;
	cout << "*    You can delete some data       *" << endl;
	cout << "*    You can modify the value       *" << endl;
	cout << "*    Update it whenever you like    *" << endl;
	cout << "*              Have fun!            *" << endl;
	cout << "*************************************"<< endl;
}

void choice()
{
	cout << endl;
	cout << "(1)For query one key" << endl;
	cout << "(2)For query a range of keys" << endl;
	cout << "(3)For insertion" << endl;
	cout << "(4)For remove" << endl;
	cout << "(5)For modification" << endl;
	cout << "(6)For update" << endl;
	cout << "(7)For exit" << endl;
	cout << "Enter:   ";
}