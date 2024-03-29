
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
			counter = nullptr;
			data = nullptr;
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
