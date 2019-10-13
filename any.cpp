
#include <iostream>
#include<typeinfo>
#include<string>
using std::cout;
class value_holder {
public:
	virtual std::type_index type() const noexcept= 0;
	virtual value_holder * copy() const= 0;
	virtual ~value_holder(){}
};
template<typename T>
class holder : public value_holder {
public:
	holder(const T &a):data(a){}
	T data;
 	virtual std::type_index & type() const noexcept override{
		return typeid(T);
	}
	virtual value_holder *copy() const override{
		return new holder(data);
	}
};
class any final{
	value_holder *value;
public:
	~any(){
		delete value;
	}
	any(){
		value =nullptr;
	}
	template<typename T>
	any(const T &a):value(new holder<T>(a)){}
	any(const any &a){
		value = a.value->copy();
	}
	any &operator=(any const &a) {
		if (*this != a){
		delete value;
		value = a.value->copy();
		}
		return *this;
	}
	std::type_index & type() {
		return value ? value->type() : typeid(void);
	}
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
	return static_cast<holder<T>*>(a.value)->data;
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

