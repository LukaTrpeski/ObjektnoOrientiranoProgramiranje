/*
Да се дефинира класа Krug, во која се чуваат информации за:

радиус float
бројот π const float.
Во класата да се реализираат:

default конструктор и конструктор со аргументи
метод за пресметување плоштина
метод за пресметување периметар
метод кој кажува дали плоштината и периметарот на даден круг се еднакви
*/
#include <iostream>
using namespace std;

class Krug {
public:
float radius;
const float pi=3.14;
Krug();
Krug(float r)
{radius=r;}
float plostina()
{
    return radius*radius*pi;
}
float perimetar()
{
    return 2*radius*pi;
}
bool ednakvi()
{
    return (radius*radius*pi)==(2*radius*pi);
};
};

int main() {
	float r;
	cin >> r;
	Krug k(r);
	cout << k.perimetar() << endl;
	cout << k.plostina() << endl;
	cout << k.ednakvi() <<endl;
    Krug k1();
	return 0;
}