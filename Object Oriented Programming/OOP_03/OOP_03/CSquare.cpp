#include "CSquare.h"

CSquare::CSquare(pair <int, int> vectorA, pair <int, int> vectorB) {
	sideA = sqrt(static_cast<double> (vectorA.first * vectorA.first + vectorA.second * vectorA.second));
	sideB = sqrt(static_cast<double> (vectorB.first * vectorB.first + vectorB.second * vectorB.second));

	angle = acos((vectorA.first * vectorB.first + vectorA.second * vectorB.second) / (sideA * sideB));
}

double CSquare::Square(void) {
	if (sideA != sideB || angle != M_PI / 2) return 0;
	else return sideA * sideA;
}
double CSquare::Perimeter(void) {
	if(sideA != sideB || angle != M_PI / 2) return 0;
	else return 4 * sideA;
}