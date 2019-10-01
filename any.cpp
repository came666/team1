
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

