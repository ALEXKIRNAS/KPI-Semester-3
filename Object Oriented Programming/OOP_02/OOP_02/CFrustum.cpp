#include "СFrustum.h"
#include <cmath>
#include <algorithm>

// Конструктор
CFrustum::CFrustum(pair <double, pair <double, double>> base, pair <double, pair <double, double>> top) : CBaseCircle(base), CTopCircle(top) {
	double deltaX, deltaY, deltaZ;

	deltaX = base.first - top.first;
	deltaY = base.second.first - top.second.first;
	deltaZ = base.second.second - top.second.second;

	height = sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2));
}

// Розрахувати обєм
double CFrustum::getVolume(void) {
	return static_cast<double> (1) / 3 * M_PI * height *
		(pow(CBaseCircle::getRadius(), 2) + CBaseCircle::getRadius() * CTopCircle::getRadius() + pow(CTopCircle::getRadius(), 2));
}

// Розрахувати площу поверхні
double CFrustum::getSufaceSquare(void) {
	double generatrix = sqrt(pow(height, 2) + pow((CBaseCircle::getRadius() - CTopCircle::getRadius()), 2));
	if(height != 0) return M_PI * generatrix * (CBaseCircle::getRadius() + CTopCircle::getRadius());
	else return std::max(CBaseCircle::getSquare(), CTopCircle::getSquare());
}