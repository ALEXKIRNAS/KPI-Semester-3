#pragma once
#include "CTopCircle.h"
#include "CBaseCircle.h"

class CFrustum : public CTopCircle, public CBaseCircle {
private:
	double height; // Висота конуса
public:
	CFrustum(pair <double, pair <double, double>> base, pair <double, pair <double, double>> top); // Конструктор
	double getVolume(void); // Розрахувати обєм
	double getSufaceSquare(void); // Розрахувати площу поверхні
};