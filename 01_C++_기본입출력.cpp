// 01_C++_�⺻�����.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iomanip>
//error C2065 : 'cout' : ������� ���� �ĺ����Դϴ�.
//error C2065 : 'endl' : ������� ���� �ĺ����Դϴ�.

//using std::cout;
//using std::endl;
using namespace std;

int main()
{
	/*
		cout << a+b;
		cout << 10;
		cout << �Լ�()
		cout << a;
	*/
	cout << "����Ӵ�!! ��������??^^" << endl;

	//< ��������
	int num = 10;
	float fnum = 20.0f;
	char ch = 'a';

	//< ���
	//std::cout.precision(3);
	
	//cout << fixed << setprecision(2) << (double)a / b;
	std::cout << num << std::endl;
	
	cout << fixed << setprecision(6) << fnum << endl;
	std::cout << fnum << std::endl;

	//< 16��
	std::hex(std::cout);
	std::cout << (int)&ch << std::endl;
		
	////< �Է�
	//std::cin >> num;
	//std::cin >> fnum;
	//std::cin >> ch;

	//std::cout << num << std::endl;
	//std::cout << fnum << std::endl;
	//std::cout << ch << std::endl;

	cout << "����ϰ��ִ�	" << endl;

    return 0;
}

