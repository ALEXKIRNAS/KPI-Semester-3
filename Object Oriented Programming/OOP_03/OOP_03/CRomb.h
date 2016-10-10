#pragma once
#include "CFigure.h"

// Клас ромба
class CRomb : public CFigure {
public:
	CRomb(pair <int, int> vectorA, pair <int, int> vectorB);
	double Square(void);
	double Perimeter(void);
};