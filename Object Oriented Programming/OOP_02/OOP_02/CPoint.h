#pragma once
#include <utility>
#define M_PI       3.14159265358979323846   // pi
using std::pair;

// ���� �����
class CPoint {
private:
	double x, y, z; // ���������� �����
public:
	CPoint(pair <double, pair <double, double>> point); // �����������
	pair <double, pair <double, double>> getPoint(void); // ����� �����
	void setPoint(pair <double, pair <double, double>> point); // ����� �����
};