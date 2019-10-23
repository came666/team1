// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <iostream>

template<typename T>
class my_shared_ptr final{
	int *counter;
	T *data = nullptr;
public:
	my_shared_ptr() = default;
	my_shared_ptr(T d) :data(new T(d)) {
		counter = new int(1);
	}
	my_shared_ptr(const my_shared_ptr &a){
		if (counter != nullptr) {
			(*counter)--;
			clear();
		}
		(*a.counter)++;
		data = new T(*a.data);
		counter = a.counter;
	}
	~my_shared_ptr() {
		(*counter)--;
		clear();
	}
	void clear() {
		if (*counter == 0) {
			delete counter;
			delete data;
		}
	}
	my_shared_ptr<T> &operator=(const my_shared_ptr<T> &a) {
		if (data!=a.data)
		{
			(*counter)--;
			clear();
			(*a.counter)++;
			data = a.data;
			counter = a.counter;
		}
		return *this;
	}
	my_shared_ptr reset(T *new_data) {
		*counter--;
		clear();
		data = new T(*new_data);
		counter = new int(1);
	}
	int use_count() {
		return *counter;
	}
	T operator*() {
		return *data;
	}
};
template<typename T>
my_shared_ptr<T> make_shared(T data) {
	my_shared_ptr<T>a(data);
	return a;
}
int main()
{
	my_shared_ptr<int>a = make_shared<int>(1);
	std::cout << a.use_count() << std::endl;
	my_shared_ptr<int>b(2);
	std::cout << b.use_count() << std::endl;
	b = a;
	std::cout << a.use_count() << std::endl;
	std::cout << b.use_count() << std::endl;
	std::cout << *a << std::endl;
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
