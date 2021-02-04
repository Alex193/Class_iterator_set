#include "Header.h"
#include "Class_Pair.h"
int main()
{
	setlocale(LC_ALL, "rus");
	int choise;
	cout << "To test container and it's methods press 1" << endl;
	cout << "To test iterator press 2" << endl;
	cin >> choise;
	if (choise == 1)
	{
		Pair m(1, 2);
		Pair n(1, 3.14);
		Pair k;
		Set<int> a; //инстанцируем шаблон для элементов типа int
		Set<double> b(5); //инстанцируем шаблон (добавляем всего 1 элемент "5") типа double
		Set<float> c; //инстанцируем шаблон для элементов типа float
		Set<float> d; //инстанцируем еще один шаблон для элементов типа float
		Set<Pair> p(n); //инстанцируем шаблон для элементов пользовательского типа Pair 
		//выводим наши три  множества до основного ввода (проверка работы перегрузки оператора вывода)
		cout << "\nSet a:" << endl;
		cout << a;
		cout << "\nSet b:" << endl;
		cout << b;
		cout << "\nSet c:" << endl;
		cout << c;
		cout << "\nSet d:" << endl;
		cout << d;
		for (int i = 0; i < 14; i++) // заполняем множество a целыми числами от 0 до 14
		{
			a.push(i);
		}
		cout << "Заполнение множества с" << endl;
		cin >> c; //провека работы перегруженного оператора ввода
		d = c; //проверка работы перегруженного оператора присваивания
		//выводим наши три получившиеся множества (проверка работы перегрузки оператора вывода)
		cout << "\nSet a:" << endl;
		cout << a;
		cout << "\nSet b:" << endl;
		cout << b;
		cout << "\nSet c:" << endl;
		cout << c;
		cout << "\nSet d:" << endl;
		cout << d;
		cout << "Удаление из множества a числа 13" << endl;
		a.pop(13);
		cout << "Удаление из множества a числа 20, которого нет в множестве" << endl;
		a.pop(20);
		cout << "Пустое ли множество a?" << endl;
		a.isempty();
		cout << "Проверим лежит ли число 3 в множестве a" << endl;
		a.is_in_set(3);
		cout << "Множество а: " << endl;
		cout << a;
		cout << "ПОЛЬЗОВАТЕЛЬСКИЙ КЛАСС Pair" << endl;
		cout << "1) Проверка работы опереатора ввода" << endl;
		cin >> k;
		cout << "2) Проверка работы опереатора вывода" << endl;
		cout << "m = " << m << endl << "n = " << n << endl << "k = " << k << endl;
		cout << "3) Проверка работы операторов сравнения" << endl;
		cout << "Оператор ==" << endl;
		if (m == k)
		{
			cout << "Пары чисел " << m << " и " << k << " равны" << endl;
		}
		else
		{
			cout << "Пары чисел " << m << " и " << k << " НЕ равны" << endl;
		}
		cout << "Оператор !=" << endl;
		if (m != k)
		{
			cout << "Пары чисел " << m << " и " << k << " НЕ равны" << endl;
		}
		else
		{
			cout << "Пары чисел " << m << " и " << k << " равны" << endl;
		}
		cout << "4) Проверка работы оператора присваивания" << endl;
		m = n;
		cout << "m = " << m << endl << "n = " << n << endl;
		cout << "\nМножество, элементами которого являются объекты пользовательского класса Pair" << endl;
		cout << p;
		cout << "\nДобавляем новый элемент" << endl;
		p.push(m);
		cout << p;
		cout << "\nПроверка работы удаления" << endl;
		p.pop(n);
		cout << p;
		cout << "\nПроверка на пустоту" << endl;
		p.isempty();
		cout << "\nРазмера множества" << endl;
		p.get_size();
	}
	if (choise == 2)
	{
		cout << "Тестирование ИТЕРАТОРА"<< endl;
		cout << "Заполняем контейнер элементам типа int числами от 0 до 14"<< endl;
		Set<int> a;
		for (int i = 0; i < 15; i++) // заполняем множество a целыми числами от 0 до 14
		{
			a.push(i);
		}
		cout << "Обычный вывод контейнера, без итератора" << endl;
		cout << a;
		cout << "Вывод первого элемента контейнера с помощью итератора" << endl;
		cout << "Первый элемент - ";
		My_Iterator<Set<int>> begin(a.begin());
		cout << *begin << endl;
		cout << "Вывод последнего элемента контейнера с помощью итератора" << endl;
		cout << "Последний элемент - ";
		My_Iterator<Set<int>> end(a.end());
		cout << *(--end) << endl;
		cout << "Пытаемся вставить элемент 10 в наше множество"<< endl;
		pair<My_Iterator<Set<int>>, bool> q = a.insert(10);
		if (q.second == true)
		{
			cout << "Элемент " << *q.first << " уже находился в множестве" << endl;
		}
		else
		{
			cout << "Элемент " << *q.first << " был добавлен в множество" << endl;
		}
		cout << a;
		cout << "Пытаемся вставить элемент 69 в наше множество" << endl;
		pair<My_Iterator<Set<int>>, bool> r = a.insert(69);
		if (r.second == true)
		{
			cout << "Элемент " << *r.first << " уже находился в множестве" << endl;
		}
		else
		{
			cout << "Элемент " << *r.first << " был добавлен в множество" << endl;
		}
		cout << "Вывод элементов в помощью итератора" << endl;
		for (My_Iterator<Set<int>> tmp(a.begin()); tmp != a.end(); tmp++)
		{
			cout << *tmp << " ";
		}
		cout << endl;
		cout << "Пытаемся вставить элемент 59 на позицию 2" << endl;
		My_Iterator<Set<int>> res = a.insert((++(++a.begin())), 59);
		cout << "Вставленный объект - ";
		cout << *res << endl;
		cout << a;
		cout << "Удалим элемент с позиции 3" << endl;
		My_Iterator<Set<int>> res1 = a.erase((++(++(++a.begin()))));
		cout << "Следующий за удаленным элемент - " << *res1 << endl;
		cout << a;
		cout << "Удалим 3 последних элемента" << endl;
		My_Iterator<Set<int>> res2 = a.erase((--(--(--a.end()))), a.end());
		cout << a;
		cout << endl;
	}
	if ((choise < 1) || (choise > 2))
	{
		cout << "Your choise is bad" << endl;
	}
	return 0;
}