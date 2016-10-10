#include "Interface.h"
#include "CFigure.h"
#include "CParallelogram.h"
#include "CSquare.h"
#include "CRomb.h"
#include <cstdio>
#include <cstdlib>

// Виведення меню
bool outputMenu(void) {

	system("cls");
	printf("OOP lab work #2\nVariant - 7, Level - C\nTask: Define figures using polymorphism\nWriter: Alexander ALEXKIRNAS Zarichkovyi\n\n");
	printf("Menu:\n1. Start program\n2. Exit\n\nMake your choice ");

	int t;
	scanf("%d", &t);
	switch (t) {
	case 1: {
		

		system("pause");
		break;
	}
	case 2: return false;
	}

	return true;
}

// Введення вектора
pair <int, int> inputVector(char* str) {
	int x1, x2, y1, y2;
	printf("Input %s vector:\n", str);
	printf("X1: "); scanf("%d", &x1);
	printf("Y1: "); scanf("%d", &y1);
	printf("X2: "); scanf("%d", &x2);
	printf("Y2: "); scanf("%d", &y2);

	return std::make_pair(x2 - x1, y2 - y1);
}