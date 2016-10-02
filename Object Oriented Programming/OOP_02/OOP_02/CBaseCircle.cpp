#include "CBaseCircle.h"
using std::cin;
using std::cout;

// �����������
CBaseCircle::CBaseCircle(pair <double, pair <double, double>> point) : CPoint(point)  {
	cout << "Enter radius of base circle: ";
	cin >> radius;
}

// ����� ������
double CBaseCircle::getRadius(void) {
	return radius;
}

// ����������� �����
double CBaseCircle::getSquare(void) {
	return radius * radius * M_PI;
}