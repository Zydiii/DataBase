#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <string>
#include <set>
#include "buffer.h"

/*��������Buffer()
*���ܣ����캯��
*/
Buffer::Buffer()
{}

/*��������~Buffer()
*���ܣ���������
*/
Buffer::~Buffer()
{
	put_buffer.clear();
	remove_buffer.clear();
}

/*��������clear()
*���ܣ���ջ���
*/
void Buffer::clear()
{
	put_buffer.clear();
	remove_buffer.clear();
	read_buffer.clear();
}

/*��������check_buffer_put(const int key)
*���ܣ����洢�����Ƿ���key
*/
bool Buffer::check_buffer_put(const int key)
{
	if (put_buffer.count(key) == 1)
		return true;
	else
		return false;
}

/*��������check_buffer_remove(const int key)
*���ܣ����ɾ�������Ƿ���key
*/
bool Buffer::check_buffer_remove(const int key)
{
	if (remove_buffer.count(key) == 1)
		return true;
	else
		return false;
}

/*��������set_put(const int key, const string data)
*���ܣ���<key, value>����洢����
*/
void Buffer::set_put(const int key, const string data)
{
	put_buffer[key] = data;
}

/*��������set_remove(const int key, const string data)
*���ܣ���<key, value>����ɾ������
*/
void Buffer::set_remove(const int key, const string data)
{
	remove_buffer[key] = data;
}

/*��������buffer_get(const int key)
*���ܣ��õ��洢������key��Ӧ��value
*/
string Buffer::buffer_get(const int key)
{
	return put_buffer[key];
}

/*��������buffer_remove(const int key)
*���ܣ��õ�ɾ��������key��Ӧ��value
*/
string Buffer::buffer_remove(const int key)
{
	return remove_buffer[key];
}

/*��������remove_erase(const int key)
*���ܣ���ɾ�����������key
*/
void Buffer::remove_erase(const int key)
{
	remove_buffer.erase(key);
}

/*��������put_erase(const int key)
*���ܣ��Ӵ洢���������key
*/
void Buffer::put_erase(const int key)
{
	put_buffer.erase(key);
}

/*��������change_put(const int key, const string data)
*���ܣ����Ĵ洢����key��Ӧ��data
*/
void Buffer::change_put(const int key, const string data)
{
	put_buffer[key] = data;
}

/*��������buffer_size()
*���ܣ��õ������С
*/
int Buffer::buffer_size()
{
	return put_buffer.size() + remove_buffer.size() + read_buffer.size();
}

/*��������put_size()
*���ܣ��õ��洢�����С
*/
int Buffer::put_size()
{
	return put_buffer.size();
}

/*��������remove_size()
*���ܣ��õ�ɾ�������С
*/
int Buffer::remove_size()
{
	return remove_buffer.size();
}

/*��������put_clear()
*���ܣ���մ洢����
*/
void Buffer::put_clear()
{
	put_buffer.clear();
}

/*��������remove_clear()
*���ܣ����ɾ������
*/
void Buffer::remove_clear()
{
	remove_buffer.clear();
}

/*��������put()
*���ܣ��õ��洢����
*/
map<int, string> Buffer::put()
{
	return put_buffer;
}

/*��������remove()
*���ܣ��õ�ɾ������
*/
map<int, string> Buffer::remove()
{
	return remove_buffer;
}

/*��������set_read(const int key, const string data)
*���ܣ����ö�����
*/
void Buffer::set_read(const int key, const string data)
{
	read_buffer[key] = data;
}

/*��������read()
*���ܣ��õ�������
*/
map<int, string> Buffer::read()
{
	return read_buffer;
}

/*��������read_size()
*���ܣ��õ��������С
*/
int Buffer::read_size()
{
	return read_buffer.size();
}

/*��������read_erase(const int key)
*���ܣ�����������е�key
*/
void Buffer::read_erase(const int key)
{
	read_buffer.erase(key);
}

/*��������buffer_read(const int key)
*���ܣ��õ��������е�key��Ӧֵ
*/
string Buffer::buffer_read(const int key)
{
	return read_buffer[key];
}

/*��������check_buffer_read(const int key)
*���ܣ��ж϶��������Ƿ����key
*/
bool Buffer::check_buffer_read(const int key)
{
	if (read_buffer.count(key) == 1)
		return true;
	else
		return false;
}

/*��������read_update()
*���ܣ����¶�����
*/
void Buffer::read_update()
{
	if (read_size() > 100)
	{
		map<int, string> ::iterator it = read_buffer.end();
		it--;
		read_buffer.erase(it);
	}
}