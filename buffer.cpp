#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <string>
#include <set>
#include "buffer.h"

/*函数名：Buffer()
*功能：构造函数
*/
Buffer::Buffer()
{}

/*函数名：~Buffer()
*功能：析构函数
*/
Buffer::~Buffer()
{
	put_buffer.clear();
	remove_buffer.clear();
}

/*函数名：clear()
*功能：清空缓存
*/
void Buffer::clear()
{
	put_buffer.clear();
	remove_buffer.clear();
	read_buffer.clear();
}

/*函数名：check_buffer_put(const int key)
*功能：检查存储缓存是否含有key
*/
bool Buffer::check_buffer_put(const int key)
{
	if (put_buffer.count(key) == 1)
		return true;
	else
		return false;
}

/*函数名：check_buffer_remove(const int key)
*功能：检查删除缓存是否含有key
*/
bool Buffer::check_buffer_remove(const int key)
{
	if (remove_buffer.count(key) == 1)
		return true;
	else
		return false;
}

/*函数名：set_put(const int key, const string data)
*功能：将<key, value>存入存储缓存
*/
void Buffer::set_put(const int key, const string data)
{
	put_buffer[key] = data;
}

/*函数名：set_remove(const int key, const string data)
*功能：将<key, value>存入删除缓存
*/
void Buffer::set_remove(const int key, const string data)
{
	remove_buffer[key] = data;
}

/*函数名：buffer_get(const int key)
*功能：得到存储缓存中key对应的value
*/
string Buffer::buffer_get(const int key)
{
	return put_buffer[key];
}

/*函数名：buffer_remove(const int key)
*功能：得到删除缓存中key对应的value
*/
string Buffer::buffer_remove(const int key)
{
	return remove_buffer[key];
}

/*函数名：remove_erase(const int key)
*功能：从删除缓存中清除key
*/
void Buffer::remove_erase(const int key)
{
	remove_buffer.erase(key);
}

/*函数名：put_erase(const int key)
*功能：从存储缓存中清除key
*/
void Buffer::put_erase(const int key)
{
	put_buffer.erase(key);
}

/*函数名：change_put(const int key, const string data)
*功能：更改存储缓存key对应的data
*/
void Buffer::change_put(const int key, const string data)
{
	put_buffer[key] = data;
}

/*函数名：buffer_size()
*功能：得到缓存大小
*/
int Buffer::buffer_size()
{
	return put_buffer.size() + remove_buffer.size() + read_buffer.size();
}

/*函数名：put_size()
*功能：得到存储缓存大小
*/
int Buffer::put_size()
{
	return put_buffer.size();
}

/*函数名：remove_size()
*功能：得到删除缓存大小
*/
int Buffer::remove_size()
{
	return remove_buffer.size();
}

/*函数名：put_clear()
*功能：清空存储缓存
*/
void Buffer::put_clear()
{
	put_buffer.clear();
}

/*函数名：remove_clear()
*功能：清空删除缓存
*/
void Buffer::remove_clear()
{
	remove_buffer.clear();
}

/*函数名：put()
*功能：得到存储缓存
*/
map<int, string> Buffer::put()
{
	return put_buffer;
}

/*函数名：remove()
*功能：得到删除缓存
*/
map<int, string> Buffer::remove()
{
	return remove_buffer;
}

/*函数名：set_read(const int key, const string data)
*功能：设置读缓存
*/
void Buffer::set_read(const int key, const string data)
{
	read_buffer[key] = data;
}

/*函数名：read()
*功能：得到读缓存
*/
map<int, string> Buffer::read()
{
	return read_buffer;
}

/*函数名：read_size()
*功能：得到读缓存大小
*/
int Buffer::read_size()
{
	return read_buffer.size();
}

/*函数名：read_erase(const int key)
*功能：清除读缓存中的key
*/
void Buffer::read_erase(const int key)
{
	read_buffer.erase(key);
}

/*函数名：buffer_read(const int key)
*功能：得到读缓存中的key对应值
*/
string Buffer::buffer_read(const int key)
{
	return read_buffer[key];
}

/*函数名：check_buffer_read(const int key)
*功能：判断读缓存中是否存在key
*/
bool Buffer::check_buffer_read(const int key)
{
	if (read_buffer.count(key) == 1)
		return true;
	else
		return false;
}

/*函数名：read_update()
*功能：更新读缓存
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