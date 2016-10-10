#pragma once
#include"CFigure.h"

class CParallelogram : public CFigure {
public:
	CParallelogram (pair <int, int> vectorA, pair <int, int> vectorB);
	double Square(void);
	double Perimeter(void);
};