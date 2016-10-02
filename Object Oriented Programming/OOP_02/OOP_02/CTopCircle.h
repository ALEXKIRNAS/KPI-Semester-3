#pragma once
#pragma once
#include "CPoint.h"
#include <iostream>


class CTopCircle : public CPoint {
private:
	double radius; // Радіус верхнього кола
public:
	 CTopCircle(pair <double, pair <double, double>> point); // Конструктор
	double getRadius(void); // Гетер радіуса
	double getSquare(void); // Розрахувати площу
};