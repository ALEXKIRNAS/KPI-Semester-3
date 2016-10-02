#pragma once
#include "CPoint.h"
#include <iostream>


class CBaseCircle : public CPoint {
private:
	double radius; // ����� ������
public:
	CBaseCircle(pair <double, pair <double, double>> point); // �����������
	double getRadius(void); // ����� ������
	double getSquare(void); // ����������� �����
};