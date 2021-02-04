#pragma once
#define CRT_CECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include <string>
using namespace std;
template<class Set>
class My_Iterator //����� ���������
{
public:
    using Type = typename Set::ValueType; // �������� ��� ��������� ������ ���������
private:
    Type* my_pointer;
public:
    //�����������
    My_Iterator(Type* pointer) : my_pointer(pointer) {} 

    //���������� ���������� ������������ � ����������� ���������� � ����������
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

    // ����������� []
    Type& operator[] (int index)
    {
        return *(my_pointer + index);
    }

    //���������� *
    Type operator* ()
    {
        return *my_pointer;
    }

    //���������� ��������� ���������
    bool operator == (const My_Iterator& something) const
    {
        return my_pointer == something.my_pointer;
    }

    //���������� ��������� �� �����
    bool operator != (const My_Iterator& something) const
    {
        return !(*this == something);
    }

    //��������� ��������� ������������
    void operator=(const My_Iterator& something)
    {
        this->my_pointer = something.my_pointer;
    }
};

template <class Type>
class Set
{
private:
    enum { SIZE = 10 };// ������ ��������� �� ���������
    int array_size = 0;// ������ ������ ���������
    int cur_size = 0;
    Type* items = NULL;// �������� ���������
public:
    //������ ����� ������� ����������� 
    using iterator = My_Iterator<Set<Type>>; 
    using ValueType = Type;
public:
    explicit Set(); //�����������, ��������� ��������� �������� �� ���������
    Set(Type t);//����������� � �����������
    ~Set() //����������
    {
        delete[] items;
        cout << "Destroying succeeded" << endl;
    }
    void isempty(); //�������� �� �������
    bool push(Type item); //���������� �������� � ���������
    bool pop(Type item); //�������� �������� �� ���������
    void get_size(); //������ ���������
    bool is_in_set(Type item); //�������������� �������� ���������
    friend istream& operator >> (istream& is, Set<Type>& s) //���������� ��������� �����
    {
        Type tmp; //��������� ���������� ��� �����
        int n = 0;
        cout << "How much elements do you want to add? " << endl;
        is >> n; //������������ ������ ������� ��������� ������
        if (n > 0)
        {
            for (int i = 0; i < n; i++)
            {
                cout << "Enter " << i << " element: ";
                is >> tmp; //��������� � ������� ���������� ��� ������ 
                s.push(tmp); //���������� � ���������
            }
        }
        else
        {
            cout << "Wrong input! " << endl; //���� �������� ����
        }
        return is;
    }
    friend ostream& operator << (ostream& os, const Set<Type>& s) //��������� ��������� ������
    {
        if (s.cur_size == 0) //���� � ��������� ��� ���������
        {
            os << "Your set is empty" << endl;
            return os;
        }
        else //���� �������� ����, �� ������� ��
        {
            os << "Your set:" << endl;
            for (int i = 0; i < s.cur_size; i++) //���������� ������ �� ���� ��������� ��������� 
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

    //���������� �������� �� ������ ������� ����������
    iterator begin()
    {
        return iterator(items);
    }
    
    //���������� �������� �� ����� ����������
    iterator end()
    {
        return iterator(items + cur_size);
    }

    //��������� �� ������� pos ������� key
    iterator insert(iterator pos, const Type& key)
    {
        bool flag = false;
        iterator tmp(begin()); //�������� �� ������ ����������
        for (tmp; tmp != end(); tmp++) //� ����� ���� �� ���������� �� ������ �� �����
        {
            if (*tmp == key) // ���� �������� ��� ���� � ���������, ���������� ������� �� ���� �������
            {
                return tmp;
            }
            if (tmp == pos) //���� ����� ������ ������� ��� �������, ������ ���� 
            {
                flag = true;
            }
        }
        if (flag) //���� ������� ���� �������, �������� �������� ��� ������� ������ �� ������ �����
        {
            for (tmp; tmp != pos; tmp--) 
            {
                tmp[0] = tmp[-1];
            }
        }
        tmp[0] = key; //��������� �������
        cur_size++; //����������� ������� ��������� � ���������
        return tmp; //���������� ��������
    }

    //������� �������, ��� ������� ��������� �������� pos
    iterator erase(iterator pos)
    {
        bool flag = false;
        for (iterator tmp(begin()); tmp != end(); tmp++) //� ����� ���� �� ���������� �� ������ �� �����
        {
            if (tmp == pos) //���� ����� ������ ������� ��� �������, ������ ���� 
            {
                flag = true;
                tmp++;
            }
            if (flag && tmp != end()) //��������
            {
                tmp[-1] = tmp[0];
            }
            if (tmp == end()) //����� �����, ���������������
            {
                break;
            }
        }
        if (flag) //���� �������� ����, ��������� ������� ��������� � ���������
        {
            cur_size--;
        }
        return pos; //���������� �������� �� ��������� �� ��������� ������
    }

    //�������� ����� ��������� ���������� � iterator_begin �� iterator_end
    iterator erase(iterator iterator_begin, iterator iterator_end)
    {
        int i = 0;
        bool flag_1 = false, flag_2 = false; 
        iterator end_element(end()); //�������� �� ������� ��������� �� ���������
        for (iterator tmp(begin()); tmp != end_element; tmp++) //� ����� ���� �� ���������� �� ������ �� �����
        {
            if (tmp == iterator_begin) //���� ����� ������� ������, ������ ������ ����
            {
                flag_1 = true;
            }
            if (flag_1) //���� ����� ������� �����, ������ ���� 2 �������
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
                    cur_size--; // ��������� ������� ��������� � ��������� �� 1
                }
            }
        }
        return iterator_begin; //���������� �������� �� ������ ����������� �������
    }

    //������� �������� val � ���������
    pair<iterator, bool> insert(const Type& val)
    {
        iterator iter(begin()); //�������� �� ������
        pair<iterator, bool> res(iter, true); //������� ���� ��������-������� �������� 
        for (iter; iter != end(); iter++)  //���������� �� ��������� ���������
        {
            if (*iter == val) //���� ����� ������� ��� ���� � ���������, ���������� �������� �� ����
            {
                //�������� bool �������� true, ��� �������� ��� ������� �� ����, ��� ��� ����� ������� ��� ��� � ���������
                res.first = iter;
                return res;
            }
        }
        push(val); //���� �� ����� ������ �������� � ���������, �� ��������� ��� 
        res.first = iter; //���������� �������� �� ���������� �������
        res.second = false; //���� ���� ��� ������� ���������
        return res; //���������� ���� (�������, ������� ��������)
    }
};

template <class Type>
Set<Type>::Set() //����������� �� ���������
{
    items = new Type[SIZE]; //�������� ������ �� ���������� ��������� �� ���������
    array_size = SIZE; //���������� �� ������� ��������� �������� ������
}
template <class Type>
Set<Type>::Set(Type t)//����������� � ���������� 
{
    items = new Type[1]; //�������� ������ �� 1 �������
    array_size = 1; //���������� �� ������� ��������� �������� ������
    push(t); //���������� ������� � ���������
}
template <class Type>
bool Set<Type>::push(Type item) //���������� ��������� � ���������
{
    for (int i = 0; i < cur_size; i++) //��������� ��� �� �������� ��� � ���������
    {
        if (items[i] == item)// ���� ����, �� �� ��������� ������ ���
        {
            cout << "Element " << item << " is already in the set" << endl;
            return false;
        }
    }
    if (cur_size < array_size) //���� ������ ����������, �� �� ������������, � ������ ����������
    {
        items[cur_size] = item; //���������� ������� � ���������
        cur_size++; //����������� ���������� ���������� ��������� � ���������
        return true;
    }
    else
    {
        Type* tmp = NULL; //������� ��������� ����������
        int numTmp = cur_size + 10; //������������ ������ �� ��� ���������� 1 ��������, � ��� 10 ����
        tmp = new Type[numTmp]; //�������� ������ ��� ��������� ����������, ����� ���������� ���� ������������ ���������
        for (int i = 0; i < cur_size; i++)
        {
            tmp[i] = items[i]; //�������� ������ �� ������� �������
        }
        tmp[cur_size] = item; //���������� ������� � ��������� ���������
        delete[] items; //������ ������
        items = tmp; //����������� 
        cur_size++; //����������� ���������� ���������� ��������� � ���������
        array_size += 10; //����������� ���������� ������ ���������� ������ � ���������
        return true;
    }
}
template <class Type>
bool Set<Type>::pop(Type item) //�������� �������� �� ���������
{
    bool flag = 0;
    for (int i = 0; i < cur_size; i++)
    {
        if (items[i] == item) //���� ������������� ��� �������� ������� ���� � ���������, �� �������� � �������
        {
            for (int j = i + 1; j < cur_size; j++)
                items[j - 1] = items[j];
            cur_size--; //��������� ���������� ���������� ��������� � ���������
            flag = 1; //���� ����, ��� �������������� ��� �������� ������� ������ � ��������� 
            break;
        }
    }
    if (((array_size - cur_size) > 10) && (flag)) //���� ��������� ������ ������, ��� �� 10 ���������, �� ������������
    {
        Type* tmp = NULL; //������� ��������� ����������
        int numTmp = array_size - 10; //������������ ������ �� ��� ���������� 1 ��������, � ��� 10 ����
        tmp = new Type[numTmp]; //�������� ������ ��� ��������� ����������, ����� ���������� ���� ������������ ���������
        for (int i = 0; i < cur_size; i++)
        {
            tmp[i] = items[i]; //�������� ������ �� ������� �������
        }
        delete[] items; //������ ������
        items = tmp; //�����������
        array_size -= 10; //����������� ���������� ������ ���������� ������ � ���������
        return true;
    }
    //���� �������������� �������� ��� � ���������
    if (!flag)
    {
        cout << "\nThere is no element " << item << " in your set, unable to delete" << endl;
        return false;
    }
}
template <class Type>
void Set<Type>::isempty() //�������� �� ������� ���������
{
    if (cur_size == 0) //��������� ������� ��������� ��� �����
    {
        cout << "\nYour set is empty " << endl;
    }
    else
    {
        cout << "\nYour set is NOT empty " << endl;
    }
}
template <class Type>
void Set<Type>::get_size() //������ ���������
{
    //������� ������ ���������
    cout << "\nSet size: " << cur_size << " elements" << endl;
}
template <class Type>
bool Set<Type>::is_in_set(Type item) //�������������� � ���������
{
    for (int i = 0; i < cur_size; i++)
    {
        if (items[i] == item) //���� ������ �������, ������� �������������� ���������
        {
            cout << "\nElement " << item << " found in the set!" << endl;
            return true;
        }
    }
    cout << "\nThere is no element " << item << " in the set" << endl;
    return false;
}