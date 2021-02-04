#pragma once
#include <iostream>
using namespace std;
class Pair
{
private:
	int int_num; //объявили целочисленную переменную 
	double double_num; //объявили переменную типа double
public:
	explicit Pair() : int_num(0), double_num(0) {} //конструктор без параметров
	Pair(const int a, const double b) //конструктор с параметрами
	{
		int_num = a;
		double_num = b;
	}
	friend istream& operator>> (istream& in, Pair& numbers) //перегрузка опрератора ввода
	{
		cout << "Ввод чисел класса Pair" << endl;
		cout << "Введите ЦЕЛОЕ число: ";
		in >> numbers.int_num; //считываем целое число
		cout << "Введите ВЕЩЕСТВЕННОЕ число: ";
		in >> numbers.double_num; //считываем вещественное число
		return in;
	}
	friend ostream& operator<< (ostream& out, const Pair& numbers) //перегрузка опрератора вывода
	{
		out << numbers.int_num << ":" << numbers.double_num;
		return out;
	}
	bool operator== (const Pair& numbers) const //перегрузка опрератора сравнения ==
	{
		return (int_num == numbers.int_num) && (double_num == numbers.double_num);
	}
	bool operator!= (const Pair& numbers) const //перегрузка опрератора сравнения !=
	{
		return !((int_num == numbers.int_num) && (double_num == numbers.double_num));
	}
	Pair& operator= (const Pair& numbers) //перегрузка опереатора присваивания
	{
		if (this == &numbers) //если элементы равны, возвращаем текущий
		{
			return *this;
		}
		int_num = numbers.int_num;
		double_num = numbers.double_num;
		return *this;
	}
	~Pair() {}
};

