#pragma once
#include "CFigure.h"

// ���� �����
class CRomb : public CFigure {
public:
	CRomb(pair <int, int> vectorA, pair <int, int> vectorB);
	double Square(void);
	double Perimeter(void);
};