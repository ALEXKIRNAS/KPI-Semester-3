#pragma once
#pragma once
#include "CPoint.h"
#include <iostream>


class CTopCircle : public CPoint {
private:
	double radius; // ����� ��������� ����
public:
	 CTopCircle(pair <double, pair <double, double>> point); // �����������
	double getRadius(void); // ����� ������
	double getSquare(void); // ����������� �����
};