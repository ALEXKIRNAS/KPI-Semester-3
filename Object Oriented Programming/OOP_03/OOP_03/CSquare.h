#pragma once
#include "CFigure.h"

// Клас прямокутника
class CSquare : public CFigure {
public:
	CSquare (pair <int, int> vectorA, pair <int, int> vectorB);
	double Square(void);
	double Perimeter(void);
};