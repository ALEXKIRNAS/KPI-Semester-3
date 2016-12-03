#include "Interface.h"
#include "TaxiPark.h"
#include <iostream>
#include <cstdlib>
#include "CException.h"
#include <random>
#include <time.h>
using std::cout;

#define size 1024

bool outputMenu(void) {
	system("cls");
	cout << "OOP lab work #6\nVariant - 7, Level - C\nTask: Write variadic template class\nWriter: Alexander ALEXKIRNAS Zarichkovyi\n\n";
	cout << "Menu:\n1. Start program\n2. Exit\n\nMake your choice ";
	srand(time(0));

	try {
		char str[size];
		gets_s(str, size);

		if (strlen(str) != 1) throw CException("Wrong input format!!!");

		switch (str[0]) {
		case '1': {

			Driver drivers[] = {
				Driver("A", "1"),
				Driver("B", "2"),
				Driver("C", "3")
			};

			std::shared_ptr<order> orders[] = {
				genData(),
				genData(),
				genData(),
				genData(),
				genData(),
				genData(),
				genData()
			};

			/*order orders[] = {
				order("00:45",{ 10, 5 },{ 4, 3 }, "+123456789012", 10),
				order("00:45",{ 11, 3 },{ 0, 0 }, "+123456789012", 20),
				order("01:00",{ 0, 2 },{ 11, 5 }, "+123456789012", 2),
				order("12:45",{ 12, 35 },{ 40, 30 }, "+123456789012", 15),
				order("10:45",{ 12, 5 },{ 40, 30 }, "+123456789012", 100),
				order("10:35",{ 10, 50 },{ 4, 3 }, "+123456789012", 0),
				order("00:58",{ 10, 7 },{ 11, 4 }, "+123456789012", 2)
			};*/

			TaxiPark park(drivers, sizeof(drivers) / sizeof(Driver), orders, sizeof(orders) / sizeof(std::shared_ptr<order>));
			park.wokr();
			park.calcCharge();

			printf("\n");
			system("pause");
			break;
		}
		case '2': return false;
		default: throw CException("Unexpected input!");
		}

		return true;
	}
	catch (CException& excection) {
		excection.show();
		system("pause");
		return true;
	}

	catch (...) {
		std::cout << "Ops. Something go wrong =(\n\n";
		system("pause");
		return true;
	}
}

std::shared_ptr<order> genData(void) {
	short time = rand() % 1440;
	int x1 = rand() % 101 - 50;
	int y1 = rand() % 101 - 50;
	int x2 = rand() % 101 - 50;
	int y2 = rand() % 101 - 50;
	short delay = rand() % 200 + 10;

	char timeS[6];
	*timeS = 0;
	char buf[3];

	int hour = time / 60;
	int minute = time % 60;
	
	if (hour < 10) strcat(timeS, "0");
	strcat(timeS, itoa(hour, buf, 10));
	strcat(timeS, ":");
	if (minute < 10) strcat(timeS, "0");
	strcat(timeS, itoa(minute, buf, 10));

	std::shared_ptr <order> value(new order(timeS, { x2, y2 }, { x1, y1 }, "+123456789012", delay));
	return value;
}