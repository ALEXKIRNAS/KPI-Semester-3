#include "CRomb.h"

CRomb::CRomb(pair <int, int> vectorA, pair <int, int> vectorB) {
	sideA = sqrt(static_cast<double> (vectorA.first * vectorA.first + vectorA.second * vectorA.second));
	sideB = sqrt(static_cast<double> (vectorB.first * vectorB.first + vectorB.second * vectorB.second));

	angle = acos((vectorA.first * vectorB.first + vectorA.second * vectorB.second) / (sideA * sideB));
}

double CRomb::Square(void) {
	if (sideA != sideB) return 0;
	else return sideA * sideA * sin(angle);
}

double CRomb::Perimeter(void) {
	if (sideA != sideB) return 0;
	else return 4 * sideA;
}