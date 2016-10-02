#include "CBaseCircle.h"
using std::cin;
using std::cout;

// Конструктор
CBaseCircle::CBaseCircle(pair <double, pair <double, double>> point) : CPoint(point)  {
	cout << "Enter radius of base circle: ";
	cin >> radius;
}

// Гетер радіуса
double CBaseCircle::getRadius(void) {
	return radius;
}

// Розрахувати площу
double CBaseCircle::getSquare(void) {
	return radius * radius * M_PI;
}