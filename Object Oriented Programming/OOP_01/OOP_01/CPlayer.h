#pragma once
#include <vector>
#include "�Deck.h"
using std::vector;

#define START_MONEY 10000

// ���� ������
class CPlayer {
private:
	vector <char> cards; // �����, �� � �� ����� � ������
	int money; // ʳ������ ������ (�����), �� � � ������

public:
	void addcard(char); // ������� ���������� ���� �����
	bool giveMoney(int); // ������� ������� �������� ������
	CPlayer(void);  // ����������� �� �������������
	bool checkChance(const CDeck*, char, char); // ϳ��������� ��������� ������ "������ �����"
	char lastCard(void) const; // ������ ������� ����� �����
	vector <char> listOfCards(void) const; // ������� ������ ����
};