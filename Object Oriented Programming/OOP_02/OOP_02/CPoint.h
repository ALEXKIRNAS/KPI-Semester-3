#pragma once
#include <utility>
#define M_PI       3.14159265358979323846   // pi
using std::pair;

// Клас точки
class CPoint {
private:
	double x, y, z; // Координати точки
public:
	CPoint(pair <double, pair <double, double>> point); // Конструктор
	pair <double, pair <double, double>> getPoint(void); // Гетер точки
	void setPoint(pair <double, pair <double, double>> point); // Сетер точки
};