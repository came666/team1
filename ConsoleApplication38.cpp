// ConsoleApplication38.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <iostream>
#include<typeinfo>
#include<string>
using std::cout;
class value_holder {
public:
	virtual const std::type_info & type() const= 0;
	virtual value_holder * copy() const= 0;
	virtual ~value_holder(){}
};
template<typename T>
class holder : public value_holder {
public:
	holder(const T &a):data(a){}
	T data;
	virtual const std::type_info & type() const{
		return typeid(T);
	}
	virtual value_holder *copy() const{
		return new holder(data);
	}
};
class any {
public:
	template<typename T>
	any(const T &a):value(new holder<T>(a)){}
	any &operator=(any const &a) {
		delete value;
		value = a.value->copy();
		return *this;
	}
	const std::type_info & type() {
		return value ? value->type() : typeid(void);
	}
	value_holder * value;
	any reset() {
		delete value;
		value = nullptr;
		return *this;
	}
	any swap(any &obj) {
		std::swap(value, obj.value);
		return *this;
	}
	bool has_value() {
		return value != nullptr;
	}
};
template<typename T>
any make_any(T &value) {
	return any(value);
}
class bad_any_cast :public std::bad_cast{
public:
	virtual const char *what() {
		return "bad cast happened!";
	}
};
template<typename T>
T any_cast(any &a) {
	if (a.type() != typeid(T))
		throw bad_any_cast();
	return dynamic_cast<holder<T>*>(a.value)->data;
}
int main()
{
	any a = 1;
	cout << a.type().name() << "\n";
	a = 3.14;
	cout << a.type().name() << "\n";
	if (a.has_value())
		cout << "has value!\n";
	a.reset();
	if (!a.has_value())
		cout << "no value!\n";
	a = 2.5;
	try
	{
		double b = any_cast<double>(a);
		cout << b << "\n";
	}
	catch (bad_any_cast &e)
	{
		cout << e.what() << "\n";
	}
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
