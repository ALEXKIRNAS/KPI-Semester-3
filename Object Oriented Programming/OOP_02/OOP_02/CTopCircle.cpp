#include "CTopCircle.h"
using std::cin;
using std::cout;

// �����������
CTopCircle::CTopCircle(pair <double, pair <double, double>> point) : CPoint(point) {
	cout << "Enter radius of top circle: ";
	cin >> radius;
}

// ����� ������
double CTopCircle::getRadius(void) {
	return radius;
}

// ����������� �����
double CTopCircle::getSquare(void) {
	return radius * radius * M_PI;
}