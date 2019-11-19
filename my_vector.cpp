// ConsoleApplication6.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <initializer_list>
#include<string>
template<typename T>
class my_vector {
private:
	T *data = nullptr;
	int size;
	int cap;
public:
	my_vector(int si, T num = 0) :data(new T[2 * si]), size(si), cap(2 * si) {
		for (int i = 0; i < size; i++)
			data[i] = num;
	}
	my_vector(std::initializer_list<T> l) :data(new T[2 * l.size()]), size(l.size()), cap(2 * l.size()) {
		auto tem = l.begin();
		for (int i = 0; i < size; i++)
		{
			data[i] = *tem;
			tem++;
		}
	}
	~my_vector() {
		delete data;
	}
	my_vector(const my_vector& a) {
		this->size = a.size;
		this->cap = a.cap;
		if(this->data!=nullptr)
		{
			delete this->data;
			this->data = new T[a.cap];
			for (int i = 0; i < a.size; i++)
				this->data[i] = a.data[i];
		}
	}
	//修改器
	my_vector &push_back(T new_num) {
		if (++size > cap)
		{
			cap = 2 * size;
			T *tem = new T[size];
			for (int i = 0; i < size; i++)
				tem[i] = data[i];
			delete data;
			data = new T[cap];
			for (int i = 0; i < size; i++)
				data[i] = tem[i];
			delete tem;
		}
		data[size - 1] = new_num;
		return *this;
	}
	my_vector &clear() {
		size = 0;
		return *this;
	}
	my_vector &insert(T* pos,T d) {
		size++;
		for (auto a = pos+1; a < end(); a++)
			*a = *(a - 1);
		*pos = d;
		return *this;
	}
	void check(int i) {        //检查是否越界
		if (i >= size)
			throw -1;
	}
	//访问器
	T operator[](int i) {
		check(i);
		return data[i];
	}
	T& at(int i) {
		check(i);
		return data[i];
	}
	T& front(){
		return data[0];
	}
	T& back() {
		return data[size - 1];
	}

	int get_size() {
		return this->size;
	}
	//迭代器
	T *begin() {
		return &data[0];
	}
	T *end() {
		return &data[size];
	}
};
int main()
{
	my_vector<int> vec{2,3};
	vec.push_back(6);
	vec.insert(vec.end()-1, 5);
	for (int i = 0; i < vec.get_size(); i++)
		std::cout << vec[i] << std::endl;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
