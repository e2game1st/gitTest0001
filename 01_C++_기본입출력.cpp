// 01_C++_기본입출력.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iomanip>
//error C2065 : 'cout' : 선언되지 않은 식별자입니다.
//error C2065 : 'endl' : 선언되지 않은 식별자입니다.

//using std::cout;
//using std::endl;
using namespace std;

int main()
{
	/*
		cout << a+b;
		cout << 10;
		cout << 함수()
		cout << a;
	*/
	cout << "출력임다!! 에러날걸??^^" << endl;

	//< 변수선언
	int num = 10;
	float fnum = 20.0f;
	char ch = 'a';

	//< 출력
	//std::cout.precision(3);
	
	//cout << fixed << setprecision(2) << (double)a / b;
	std::cout << num << std::endl;
	
	cout << fixed << setprecision(6) << fnum << endl;
	std::cout << fnum << std::endl;

	//< 16진
	std::hex(std::cout);
	std::cout << (int)&ch << std::endl;
		
	////< 입력
	//std::cin >> num;
	//std::cin >> fnum;
	//std::cin >> ch;

	//std::cout << num << std::endl;
	//std::cout << fnum << std::endl;
	//std::cout << ch << std::endl;

	cout << "출력하고있다	" << endl;

    return 0;
}

