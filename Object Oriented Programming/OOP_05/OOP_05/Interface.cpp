#include "Interface.h"
#include "set.h"
#include "CException.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

// ��������� ����
bool outputMenu(void) {

	system("cls");
	printf("OOP lab work #4\nVariant - 7, Level - C\nTask: Write set of charecters\nWriter: Alexander ALEXKIRNAS Zarichkovyi\n\n");
	printf("Menu:\n1. Start program\n2. Exit\n\nMake your choice ");

	try {
		char str[size];
		gets_s(str, size);

		if (strlen(str) != 1) throw CException("Wrong input format!!!");

		switch (str[0]) {
		case '1': {

			char* str = inputStr('A');
			set A(str);
			delete[] str;

			str = inputStr('B');
			set B(str);
			delete[] str;

			printf("\nSet A: "); A.printSet();
			printf("\nSet B: "); B.printSet();

			printf("\n\nUnion of A and B: "); (A + B).printSet();
			printf("\nDifference of A and B: "); (A - B).printSet();
			printf("\nDifference of B and A: "); (B - A).printSet();
			printf("\nIntersection of A * B: "); (A * B).printSet();

			printf("\n\nUnion of A and B: "); (A += B).printSet();
			printf("\nDifference of A and B: "); (A -= B).printSet();
			printf("\nIntersection of A * B: "); (A *= B).printSet();

			for (char i = 'A'; i <= 'E'; i++) A <<= i;
			printf("\n\nAdding to A symbols 'A' - 'E': "); A.printSet();
			for (char i = 'C'; i <= 'F'; i++) A >>= i;
			printf("\nDeleting from A symbols 'C' - 'F': "); A.printSet();

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
}

//�������� ������
char* inputStr(char c) {
	char* str = new char[size];

	printf("Input %c set: ", c);
	gets_s(str, size);

	return str;
}