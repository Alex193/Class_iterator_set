#pragma once
#define CRT_CECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include <string>
using namespace std;
template<class Set>
class My_Iterator //класс итератора
{
public:
    using Type = typename Set::ValueType; // получаем тип элементов нашего множества
private:
    Type* my_pointer;
public:
    //конструктор
    My_Iterator(Type* pointer) : my_pointer(pointer) {} 

    //перегрузки операторов постфиксного и префиксного инкремента и декремента
    My_Iterator& operator++ ()
    {
        my_pointer++;
        return *this;
    }

    My_Iterator& operator-- ()
    {
        my_pointer--;
        return *this;
    }

     template<typename T>
    My_Iterator operator++ (T)
    {
        My_Iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    template<typename T>
    My_Iterator operator-- (T)
    {
        My_Iterator tmp = *this;
        --(*this);
        return tmp;
    }

    // перрегрузка []
    Type& operator[] (int index)
    {
        return *(my_pointer + index);
    }

    //перегрузка *
    Type operator* ()
    {
        return *my_pointer;
    }

    //перегрузка оператора равенства
    bool operator == (const My_Iterator& something) const
    {
        return my_pointer == something.my_pointer;
    }

    //перегрузка оператора не равно
    bool operator != (const My_Iterator& something) const
    {
        return !(*this == something);
    }

    //перегузка оператора присваивания
    void operator=(const My_Iterator& something)
    {
        this->my_pointer = something.my_pointer;
    }
};

template <class Type>
class Set
{
private:
    enum { SIZE = 10 };// размер множества по умолчанию
    int array_size = 0;// храним размер множества
    int cur_size = 0;
    Type* items = NULL;// элементы множества
public:
    //делаем более удобные обозначения 
    using iterator = My_Iterator<Set<Type>>; 
    using ValueType = Type;
public:
    explicit Set(); //конструктор, создающий множество размером по умолчанию
    Set(Type t);//конструктор с параметрами
    ~Set() //деструктор
    {
        delete[] items;
        cout << "Destroying succeeded" << endl;
    }
    void isempty(); //проверка на пустоту
    bool push(Type item); //добавление элемента в множество
    bool pop(Type item); //удаление элемента из множества
    void get_size(); //размер множества
    bool is_in_set(Type item); //принадлежность элемента множеству
    friend istream& operator >> (istream& is, Set<Type>& s) //перегрузка оператора ввода
    {
        Type tmp; //временная переменная для ввода
        int n = 0;
        cout << "How much elements do you want to add? " << endl;
        is >> n; //пользователь вводит сколько элементов ввести
        if (n > 0)
        {
            for (int i = 0; i < n; i++)
            {
                cout << "Enter " << i << " element: ";
                is >> tmp; //считываем с консоли переменную для записи 
                s.push(tmp); //записываем в множество
            }
        }
        else
        {
            cout << "Wrong input! " << endl; //если неверный ввод
        }
        return is;
    }
    friend ostream& operator << (ostream& os, const Set<Type>& s) //перегузка оператора вывода
    {
        if (s.cur_size == 0) //если в множестве нет элементов
        {
            os << "Your set is empty" << endl;
            return os;
        }
        else //если элементы есть, то выводим их
        {
            os << "Your set:" << endl;
            for (int i = 0; i < s.cur_size; i++) //проходимся циклом по всем элементам множества 
            {
                cout << s.items[i] << " ";
            }
            cout << "\n";
            return os;
        }
    }
    Set<Type>& operator=(const Set<Type>& s)
    {
        delete[] items;
        array_size = s.array_size;
        cur_size = s.cur_size;
        items = new Type[array_size];
        for (int i = 0; i < cur_size; i++)
        {
            items[i] = s.items[i];
        }
        return *this;
    }

    //возвращает итератор на первый элемент контейнера
    iterator begin()
    {
        return iterator(items);
    }
    
    //возвращает итератор на конец контейнера
    iterator end()
    {
        return iterator(items + cur_size);
    }

    //вставляет на позицию pos элемент key
    iterator insert(iterator pos, const Type& key)
    {
        bool flag = false;
        iterator tmp(begin()); //итератор на начало контейнера
        for (tmp; tmp != end(); tmp++) //в цикле идем по контейнеру от начала до конца
        {
            if (*tmp == key) // если значение уже есть в множестве, возвращаем итерато на этот элемент
            {
                return tmp;
            }
            if (tmp == pos) //если нашли нужную позицию для вставки, меняем флаг 
            {
                flag = true;
            }
        }
        if (flag) //если позиция была найдена, сдвигаем элементы для вставки нового на нужное место
        {
            for (tmp; tmp != pos; tmp--) 
            {
                tmp[0] = tmp[-1];
            }
        }
        tmp[0] = key; //вставляем элемент
        cur_size++; //увеличиваем счетчик элементов в множестве
        return tmp; //возвращаем итератор
    }

    //удаляет элемент, наа которую указывает итератор pos
    iterator erase(iterator pos)
    {
        bool flag = false;
        for (iterator tmp(begin()); tmp != end(); tmp++) //в цикле идем по контейнеру от начала до конца
        {
            if (tmp == pos) //если нашли нужную позицию для вставки, меняем флаг 
            {
                flag = true;
                tmp++;
            }
            if (flag && tmp != end()) //сдвигаем
            {
                tmp[-1] = tmp[0];
            }
            if (tmp == end()) //когда конец, останавливаемся
            {
                break;
            }
        }
        if (flag) //если удаление было, уменьшаем счетчик элементов в множестве
        {
            cur_size--;
        }
        return pos; //возвращаем итератор на следующий за удаленным объект
    }

    //удаление части элементов контейнера с iterator_begin до iterator_end
    iterator erase(iterator iterator_begin, iterator iterator_end)
    {
        int i = 0;
        bool flag_1 = false, flag_2 = false; 
        iterator end_element(end()); //итератор на элемент следующий за последним
        for (iterator tmp(begin()); tmp != end_element; tmp++) //в цикле идем по контейнеру от начала до конца
        {
            if (tmp == iterator_begin) //если нашли позицию начала, меняем первый флаг
            {
                flag_1 = true;
            }
            if (flag_1) //если нашли позицию конца, меняем флаг 2 удаляем
            {
                if (tmp == iterator_end)
                {
                    flag_2 = true;
                }
                if (flag_2)
                {
                    iterator_begin[i] = iterator_end[i];
                    i++;
                }
                else
                {
                    cur_size--; // уменьшаем счетчик элементов в множестве на 1
                }
            }
        }
        return iterator_begin; //возвращаем итератор на начало удаляенного отрезка
    }

    //вставка элемента val в множество
    pair<iterator, bool> insert(const Type& val)
    {
        iterator iter(begin()); //итератор на начало
        pair<iterator, bool> res(iter, true); //создаем пару итератор-булевое значение 
        for (iter; iter != end(); iter++)  //проходимся по элементам множества
        {
            if (*iter == val) //если такой элемент уже есть в множестве, возвращаем итератор на него
            {
                //значение bool осталось true, что означает что вставки не было, так как такой элемент уже был в множестве
                res.first = iter;
                return res;
            }
        }
        push(val); //если не нашли такого элемента в множестве, то добавляем его 
        res.first = iter; //возвращаем итератор на втавленный элемент
        res.second = false; //флаг того что вставка произошла
        return res; //возвращаем пару (итеатор, булевое значение)
    }
};

template <class Type>
Set<Type>::Set() //конструктор по умолчанию
{
    items = new Type[SIZE]; //выделяем память на количество элементов по умолчанию
    array_size = SIZE; //записываем на сколько элементов выделена память
}
template <class Type>
Set<Type>::Set(Type t)//конструктор с параметами 
{
    items = new Type[1]; //выделяем память на 1 элемент
    array_size = 1; //записываем на сколько элементов выделена память
    push(t); //записываем элемент в множество
}
template <class Type>
bool Set<Type>::push(Type item) //добавление элементов в множество
{
    for (int i = 0; i < cur_size; i++) //проверяем нет ли значения уже в множестве
    {
        if (items[i] == item)// если есть, то не добавляем второй раз
        {
            cout << "Element " << item << " is already in the set" << endl;
            return false;
        }
    }
    if (cur_size < array_size) //если памяти достаточно, то не перевыделяем, а просто записываем
    {
        items[cur_size] = item; //записываем элемент в множество
        cur_size++; //увеличиваем переменную количества элементов в множестве
        return true;
    }
    else
    {
        Type* tmp = NULL; //создаем временную переменную
        int numTmp = cur_size + 10; //перевыделяем память не при добавлении 1 элемента, а для 10 штук
        tmp = new Type[numTmp]; //выделяем память для временной переменной, чтобы скопиовать туда существующее множество
        for (int i = 0; i < cur_size; i++)
        {
            tmp[i] = items[i]; //копируем данные со старого массива
        }
        tmp[cur_size] = item; //записываем элемент в временное множество
        delete[] items; //чистим память
        items = tmp; //присваиваем 
        cur_size++; //увеличиваем переменную количества элементов в множестве
        array_size += 10; //увеличиваем переменную объема выделенной памяти в множестве
        return true;
    }
}
template <class Type>
bool Set<Type>::pop(Type item) //удаление элемента из множества
{
    bool flag = 0;
    for (int i = 0; i < cur_size; i++)
    {
        if (items[i] == item) //если запрашевыемый для удаления элемент есть в множестве, то сдвигаем и удаляем
        {
            for (int j = i + 1; j < cur_size; j++)
                items[j - 1] = items[j];
            cur_size--; //уменьшаем переменную количества элементов в множестве
            flag = 1; //флаг того, что запррашиваемый для удаления элемент найден в множестве 
            break;
        }
    }
    if (((array_size - cur_size) > 10) && (flag)) //если свободной памяти больше, чем на 10 элементов, то перевыделяем
    {
        Type* tmp = NULL; //создаем временную переменную
        int numTmp = array_size - 10; //перевыделяем память не при добавлении 1 элемента, а для 10 штук
        tmp = new Type[numTmp]; //выделяем память для временной переменной, чтобы скопиовать туда существующее множество
        for (int i = 0; i < cur_size; i++)
        {
            tmp[i] = items[i]; //копируем данные со старого массива
        }
        delete[] items; //чистим память
        items = tmp; //присваиваем
        array_size -= 10; //увеличиваем переменную объема выделенной памяти в множестве
        return true;
    }
    //если запрашевыемого элемента нет в множестве
    if (!flag)
    {
        cout << "\nThere is no element " << item << " in your set, unable to delete" << endl;
        return false;
    }
}
template <class Type>
void Set<Type>::isempty() //проверка на пустоту множества
{
    if (cur_size == 0) //проверяем сколько элементов там лежит
    {
        cout << "\nYour set is empty " << endl;
    }
    else
    {
        cout << "\nYour set is NOT empty " << endl;
    }
}
template <class Type>
void Set<Type>::get_size() //размер множества
{
    //выводим размер множества
    cout << "\nSet size: " << cur_size << " elements" << endl;
}
template <class Type>
bool Set<Type>::is_in_set(Type item) //принадлежность к множеству
{
    for (int i = 0; i < cur_size; i++)
    {
        if (items[i] == item) //если найден элемент, выводим соответсвующее сообщение
        {
            cout << "\nElement " << item << " found in the set!" << endl;
            return true;
        }
    }
    cout << "\nThere is no element " << item << " in the set" << endl;
    return false;
}
