#pragma once
#include <cmath>
#include <utility>
#define M_PI       3.14159265358979323846   // pi
using std::pair;

// ����������� ������� ����
class CFigure {
protected:
	double sideA, sideB; // ������� �����
	double angle; // ��� �� ���������
public:
	virtual double Square (void) = 0;
	virtual double Perimeter (void) = 0;
};