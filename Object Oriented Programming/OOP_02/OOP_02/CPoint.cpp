#include "CPoint.h"
using std::make_pair;

// �����������
CPoint::CPoint(pair <double, pair <double, double>> point) {
	setPoint(point);
}

// ����� �����
pair <double, pair <double, double>> CPoint::getPoint(void) {
	return make_pair(x, make_pair(y, z));
}

// ����� �����
void CPoint::setPoint(pair <double, pair <double, double>> point) {
	x = point.first;
	y = point.second.first;
	z = point.second.second;
}