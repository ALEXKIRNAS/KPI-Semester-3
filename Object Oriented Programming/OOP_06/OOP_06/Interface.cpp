#include "Interface.h"
#include <iostream>
#include <cstdlib>
#include "TaxiPark.h"
#include "CException.h"
#include "Driver.h"
#include "Order.h"
using std::cout;

bool outputMenu(void) {
	/*system("cls");
	cout << "OOP lab work #6\nVariant - 7, Level - C\nTask: Write variadic template class\nWriter: Alexander ALEXKIRNAS Zarichkovyi\n\n";
	cout << "Menu:\n1. Start program\n2. Exit\n\nMake your choice ";

	try {
		char str[size];
		gets_s(str, size);

		if (strlen(str) != 1) throw CException("Wrong input format!!!");

		switch (str[0]) {
		case '1': {

			Driver drivers[] = {
				Driver("A", "1"),
				Driver("B", "2")
			};

			order orders[] = {
				order("00:45",{ 10, 5 },{ 4, 3 }, "+123456789012", 10),
				order("00:45",{ 11, 3 },{ 0, 0 }, "+123456789012", 20),
				order("01:00",{ 0, 2 },{ 11, 5 }, "+123456789012", 2),
				order("12:45",{ 12, 35 },{ 40, 30 }, "+123456789012", 15),
				order("10:45",{ 12, 5 },{ 40, 30 }, "+123456789012", 100),
				order("10:35",{ 10, 50 },{ 4, 3 }, "+123456789012", 0),
				order("00:58",{ 10, 7 },{ 11, 4 }, "+123456789012", 2)
			};

			TaxiPark park(drivers, sizeof(drivers) / sizeof(Driver), orders, sizeof(orders) / sizeof(order));
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

	catch(...) {
		std::cout << "Ops. Something go wrong =(\n\n";
		system("pause");
		return true;
	}*/
	return false;
}