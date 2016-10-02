#pragma once
#include "CPoint.h"
#include <iostream>


class CBaseCircle : public CPoint {
private:
	double radius; // Радіус основи
public:
	CBaseCircle(pair <double, pair <double, double>> point); // Конструктор
	double getRadius(void); // Гетер радіуса
	double getSquare(void); // Розрахувати площу
};