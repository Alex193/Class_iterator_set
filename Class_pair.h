#pragma once
#include <iostream>
using namespace std;
class Pair
{
private:
	int int_num; //объ€вили целочисленную переменную 
	double double_num; //объ€вили переменную типа double
public:
	explicit Pair() : int_num(0), double_num(0) {} //конструктор без параметров
	Pair(const int a, const double b) //конструктор с параметрами
	{
		int_num = a;
		double_num = b;
	}
	friend istream& operator>> (istream& in, Pair& numbers) //перегрузка опрератора ввода
	{
		cout << "¬вод чисел класса Pair" << endl;
		cout << "¬ведите ÷≈Ћќ≈ число: ";
		in >> numbers.int_num; //считываем целое число
		cout << "¬ведите ¬≈ў≈—“¬≈ЌЌќ≈ число: ";
		in >> numbers.double_num; //считываем вещественное число
		return in;
	}
	friend ostream& operator<< (ostream& out, const Pair& numbers) //перегрузка опрератора вывода
	{
		out << numbers.int_num << ":" << numbers.double_num;
		return out;
	}
	bool operator== (const Pair& numbers) const //перегрузка опрератора сравнени€ ==
	{
		return (int_num == numbers.int_num) && (double_num == numbers.double_num);
	}
	bool operator!= (const Pair& numbers) const //перегрузка опрератора сравнени€ !=
	{
		return !((int_num == numbers.int_num) && (double_num == numbers.double_num));
	}
	Pair& operator= (const Pair& numbers) //перегрузка опереатора присваивани€
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

