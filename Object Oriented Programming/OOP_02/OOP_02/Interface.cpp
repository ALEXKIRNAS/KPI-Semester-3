#include "Interface.h"
#include "СFrustum.h"
#include <cstdio>
#include <cstdlib>

// Виведення меню
bool outputMenu(void) {

	system("cls");
	printf("OOP lab work #2\nVariant - 7, Level - C\nTask: Define class frustum using multiple imitation\nWriter: Alexander ALEXKIRNAS Zarichkovyi\n\n");
	printf("Menu:\n1. Start program\n2. Exit\n\nMake your choice ");

	int t;
	scanf("%d", &t);
	switch (t) {
		case 1: {
			pair <double, pair <double, double>> base = inputPoint("base");
			pair <double, pair <double, double>> top = inputPoint("top");

			CFrustum obj(base, top);

			printf("\nSquare of base circle: %Lf\n", obj.CBaseCircle::getSquare());
			printf("Square of top circle: %Lf\n\n", obj.CTopCircle::getSquare());
			printf("Volume of frustum: %Lf\n", obj.getVolume());
			printf("Surface square of frustum: %Lf\n\n", obj.getSufaceSquare());

			system("pause");
			break;
		}
		case 2: return false;
	}

	return true;
}

// Введення точки
pair <double, pair <double, double>> inputPoint(char * str) {
	double x, y, z;

	std::cout << "Enter X coordinate of " << str << " circle: ";
	std::cin >> x;
	std::cout << "Enter Y coordinate of " << str << " circle: ";
	std::cin >> y;
	std::cout << "Enter Z coordinate of " << str << " circle: ";
	std::cin >> z;
	std::cout << "\n";

	return std::make_pair(x, std::make_pair(y, z));
}