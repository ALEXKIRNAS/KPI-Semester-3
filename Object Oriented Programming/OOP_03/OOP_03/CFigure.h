#pragma once
#include <cmath>
#include <utility>
#define M_PI       3.14159265358979323846   // pi
using std::pair;

// Абстрактний базовий клас
class CFigure {
protected:
	double sideA, sideB; // Довжина сторін
	double angle; // Кут між сторонами
public:
	virtual double Square (void) = 0;
	virtual double Perimeter (void) = 0;
};