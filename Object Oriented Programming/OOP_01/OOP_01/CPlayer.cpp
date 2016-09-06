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

	int total = 0;
	for (int i = 0; i < NUM_OF_CARDS; i++) total += deck->haveMushCards(i);

	int luck = 0;
	for (int i = 0; i <= left; i++) 
		luck += deck->haveMushCards(i);

	total++;
	if (hidenCard <= left) luck++;

	if (luck * 8 > total) return true;
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