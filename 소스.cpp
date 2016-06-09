#include <iostream>

using namespace std;

class A
{
private:
	int m_Num;

public:
	A() {};
	explicit A(int a)
	{
		int m_Num = a;
	}
	~A() {};
};

void main(void)
{
	A a;

	a = 10;
	

	
}