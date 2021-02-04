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
		Set<int> a; //������������ ������ ��� ��������� ���� int
		Set<double> b(5); //������������ ������ (��������� ����� 1 ������� "5") ���� double
		Set<float> c; //������������ ������ ��� ��������� ���� float
		Set<float> d; //������������ ��� ���� ������ ��� ��������� ���� float
		Set<Pair> p(n); //������������ ������ ��� ��������� ����������������� ���� Pair 
		//������� ���� ���  ��������� �� ��������� ����� (�������� ������ ���������� ��������� ������)
		cout << "\nSet a:" << endl;
		cout << a;
		cout << "\nSet b:" << endl;
		cout << b;
		cout << "\nSet c:" << endl;
		cout << c;
		cout << "\nSet d:" << endl;
		cout << d;
		for (int i = 0; i < 14; i++) // ��������� ��������� a ������ ������� �� 0 �� 14
		{
			a.push(i);
		}
		cout << "���������� ��������� �" << endl;
		cin >> c; //������� ������ �������������� ��������� �����
		d = c; //�������� ������ �������������� ��������� ������������
		//������� ���� ��� ������������ ��������� (�������� ������ ���������� ��������� ������)
		cout << "\nSet a:" << endl;
		cout << a;
		cout << "\nSet b:" << endl;
		cout << b;
		cout << "\nSet c:" << endl;
		cout << c;
		cout << "\nSet d:" << endl;
		cout << d;
		cout << "�������� �� ��������� a ����� 13" << endl;
		a.pop(13);
		cout << "�������� �� ��������� a ����� 20, �������� ��� � ���������" << endl;
		a.pop(20);
		cout << "������ �� ��������� a?" << endl;
		a.isempty();
		cout << "�������� ����� �� ����� 3 � ��������� a" << endl;
		a.is_in_set(3);
		cout << "��������� �: " << endl;
		cout << a;
		cout << "���������������� ����� Pair" << endl;
		cout << "1) �������� ������ ���������� �����" << endl;
		cin >> k;
		cout << "2) �������� ������ ���������� ������" << endl;
		cout << "m = " << m << endl << "n = " << n << endl << "k = " << k << endl;
		cout << "3) �������� ������ ���������� ���������" << endl;
		cout << "�������� ==" << endl;
		if (m == k)
		{
			cout << "���� ����� " << m << " � " << k << " �����" << endl;
		}
		else
		{
			cout << "���� ����� " << m << " � " << k << " �� �����" << endl;
		}
		cout << "�������� !=" << endl;
		if (m != k)
		{
			cout << "���� ����� " << m << " � " << k << " �� �����" << endl;
		}
		else
		{
			cout << "���� ����� " << m << " � " << k << " �����" << endl;
		}
		cout << "4) �������� ������ ��������� ������������" << endl;
		m = n;
		cout << "m = " << m << endl << "n = " << n << endl;
		cout << "\n���������, ���������� �������� �������� ������� ����������������� ������ Pair" << endl;
		cout << p;
		cout << "\n��������� ����� �������" << endl;
		p.push(m);
		cout << p;
		cout << "\n�������� ������ ��������" << endl;
		p.pop(n);
		cout << p;
		cout << "\n�������� �� �������" << endl;
		p.isempty();
		cout << "\n������� ���������" << endl;
		p.get_size();
	}
	if (choise == 2)
	{
		cout << "������������ ���������"<< endl;
		cout << "��������� ��������� ��������� ���� int ������� �� 0 �� 14"<< endl;
		Set<int> a;
		for (int i = 0; i < 15; i++) // ��������� ��������� a ������ ������� �� 0 �� 14
		{
			a.push(i);
		}
		cout << "������� ����� ����������, ��� ���������" << endl;
		cout << a;
		cout << "����� ������� �������� ���������� � ������� ���������" << endl;
		cout << "������ ������� - ";
		My_Iterator<Set<int>> begin(a.begin());
		cout << *begin << endl;
		cout << "����� ���������� �������� ���������� � ������� ���������" << endl;
		cout << "��������� ������� - ";
		My_Iterator<Set<int>> end(a.end());
		cout << *(--end) << endl;
		cout << "�������� �������� ������� 10 � ���� ���������"<< endl;
		pair<My_Iterator<Set<int>>, bool> q = a.insert(10);
		if (q.second == true)
		{
			cout << "������� " << *q.first << " ��� ��������� � ���������" << endl;
		}
		else
		{
			cout << "������� " << *q.first << " ��� �������� � ���������" << endl;
		}
		cout << a;
		cout << "�������� �������� ������� 69 � ���� ���������" << endl;
		pair<My_Iterator<Set<int>>, bool> r = a.insert(69);
		if (r.second == true)
		{
			cout << "������� " << *r.first << " ��� ��������� � ���������" << endl;
		}
		else
		{
			cout << "������� " << *r.first << " ��� �������� � ���������" << endl;
		}
		cout << "����� ��������� � ������� ���������" << endl;
		for (My_Iterator<Set<int>> tmp(a.begin()); tmp != a.end(); tmp++)
		{
			cout << *tmp << " ";
		}
		cout << endl;
		cout << "�������� �������� ������� 59 �� ������� 2" << endl;
		My_Iterator<Set<int>> res = a.insert((++(++a.begin())), 59);
		cout << "����������� ������ - ";
		cout << *res << endl;
		cout << a;
		cout << "������ ������� � ������� 3" << endl;
		My_Iterator<Set<int>> res1 = a.erase((++(++(++a.begin()))));
		cout << "��������� �� ��������� ������� - " << *res1 << endl;
		cout << a;
		cout << "������ 3 ��������� ��������" << endl;
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