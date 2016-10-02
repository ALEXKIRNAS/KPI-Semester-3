#include "CTopCircle.h"
using std::cin;
using std::cout;

// Конструктор
CTopCircle::CTopCircle(pair <double, pair <double, double>> point) : CPoint(point) {
	cout << "Enter radius of top circle: ";
	cin >> radius;
}

// Гетер радіуса
double CTopCircle::getRadius(void) {
	return radius;
}

// Розрахувати площу
double CTopCircle::getSquare(void) {
	return radius * radius * M_PI;
}