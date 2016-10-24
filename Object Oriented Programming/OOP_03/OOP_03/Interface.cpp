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
	printf("OOP lab work #3\nVariant - 7, Level - C\nTask: Define figures using polymorphism\nWriter: Alexander ALEXKIRNAS Zarichkovyi\n\n");
	printf("Menu:\n1. Start program\n2. Exit\n\nMake your choice ");

	int t;
	scanf("%d", &t);
	switch (t) {
	case 1: {
		pair <int, int> vectorA = inputVector("first");
		printf("\n");
		pair <int, int> vectorB = inputVector("second");
		printf("\n");

		if (!(vectorA.first || vectorA.second) || !(vectorB.first || vectorB.second)) {
			printf("Incorect input data (zero lenth side)!\n");
			system("pause");
			return true;
		}

		CFigure* objects[3] = {
			new CRomb(vectorA, vectorB),
			new CSquare(vectorA, vectorB),
			new CParallelogram(vectorA, vectorB)
		};

		printf("Squares:\n");
		for (int i = 0; i < 3; i++) printf("%d - %.3Lf\n", i + 1, objects[i]->Square());

		printf("\n\nPerimeter:\n");
		for (int i = 0; i < 3; i++) printf("%d - %.3Lf\n", i + 1, objects[i]->Perimeter());
		printf("\n\nWhere:\n1 - Romb\n2 - Square\n3 - Parellelogram\n\n");

		for (int i = 0; i < 3; i++) delete objects[i];

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