#include "CParallelogram.h"

CParallelogram::CParallelogram(pair <int, int> vectorA, pair <int, int> vectorB) {
	sideA = sqrt(static_cast<double> (vectorA.first * vectorA.first + vectorA.second * vectorA.second));
	sideB = sqrt(static_cast<double> (vectorB.first * vectorB.first + vectorB.second * vectorB.second));

	angle = acos((vectorA.first * vectorB.first + vectorA.second * vectorB.second) / (sideA * sideB));
}

double CParallelogram::Square(void) {
	return sideA * sideB * sin(angle);
}

double CParallelogram::Perimeter(void) {
	return 2 * (sideA + sideB);
}