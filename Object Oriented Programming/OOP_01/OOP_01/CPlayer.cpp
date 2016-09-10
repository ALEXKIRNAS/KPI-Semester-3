#include "CPlayer.h"

// Функція добавлення нової карти
void CPlayer::addcard(char newCard) {
	cards.push_back(newCard);
}

// Функція знімання наступної ставки
bool CPlayer::giveMoney(int cash) {
	if (cash <= this->money) this->money -= cash;
	else return false;
	
	return true;
}

// Конструктор за замовчуванням
CPlayer::CPlayer(void) : money(START_MONEY) {}

// Підрахувати ймовірність вибору "хорошої карти"
bool CPlayer::checkChance(const CDeck* deck, char hidenCard, char left) {

	int total = deck->countTotal() + 1; // Підрахувати кількість карт, що залишилмся в колоді

	int luck = deck->countLessThat(left); // Підрахувати кількількіть карт, що можна безпечно взяти
	if (hidenCard <= left) luck++; // Якщо серед безпечних карт є прихована карта ділера, то її потрібно забрати

	// Обрати дію виходячи з ймовірності
	if (luck * 2.75f > total) return true;
	else return false;
}

// Показує останню зданю карту
char CPlayer::lastCard(void) const {
	return cards.back();
}

// Повертає список карт
vector <char> CPlayer::listOfCards(void) const {
	return cards;
}

// Забирає всі карти у гравця
void CPlayer::clearCards(void) {
	cards.clear();
}

// Повертає кількість грошей в гравця
int CPlayer::getMoney(void) const {
	return money;
}