#include "CPlayer.h"

// ������� ���������� ���� �����
void CPlayer::addcard(char newCard) {
	cards.push_back(newCard);
}

// ������� ������� �������� ������
bool CPlayer::giveMoney(int cash) {
	if (cash <= this->money) this->money -= cash;
	else return false;
	
	return true;
}

// ����������� �� �������������
CPlayer::CPlayer(void) : money(START_MONEY) {}

// ϳ��������� ��������� ������ "������ �����"
bool CPlayer::checkChance(const CDeck* deck, char hidenCard, char left) {

	int total = deck->countTotal() + 1;

	int luck = deck->countLessThat(left);
	if (hidenCard <= left) luck++;

	if (luck * 3 > total) return true;
	else return false;
}

// ������ ������� ����� �����
char CPlayer::lastCard(void) const {
	return cards.back();
}

// ������� ������ ����
vector <char> CPlayer::listOfCards(void) const {
	return cards;
}

// ������ �� ����� � ������
void CPlayer::clearCards(void) {
	cards.clear();
}

// ������� ������� ������ � ������
int CPlayer::getMoney(void) const {
	return money;
}