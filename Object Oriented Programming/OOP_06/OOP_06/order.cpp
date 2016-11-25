#include "Order.h"
#include "CException.h"
#include <string.h>
#include <cstdlib>
#include <ctype.h>

#define timeLenth 5
#define coefOfCost 5

order::order(char* timeOfOrder, address dest, address from, char* phone, short waiting) {
	if (!cheakTime(timeOfOrder)) throw CException("Wrong time input format");
	else time = atoi(timeOfOrder) * 60 + atoi(timeOfOrder + 3);
	

	destenetion = dest;
	startPoint = from;

	if(!cheakPhone(phone)) throw CException("Wrong phone input format");
	else strcpy(this->phone, phone);

	this->waiting = waiting;
}

bool order::getIsCompleted(void) {
	return isComplered;
}

void order::setIsCompleted(bool value) {
	isComplered = value;
}

bool order::cheakPhone(char* phone) {
	if (strlen(phone) != phoneSize || *phone != '+') return false;
	
	for (int i = 1; i < phoneSize; i++) if (!isdigit(phone[i])) return false;
	return true;
}

int order::getCost(void) const {
	return (abs(startPoint.x - destenetion.x) + abs(startPoint.y - destenetion.y)) * coefOfCost;
}

bool order::cheakTime(char* timeOfOrder) {
	if (strlen(timeOfOrder) != timeLenth || timeOfOrder[2] != ':') return false;
	if (!isdigit(timeOfOrder[0]) || timeOfOrder[0] > '2') return false;
	if (!isdigit(timeOfOrder[1]) || !isdigit(timeOfOrder[3]) || !isdigit(timeOfOrder[4])) return false;

	return true;
}

short order::getTime(void) const {
	return time;
}

short order::getWaiting(void) const {
	return waiting;
}

address order::getDest(void) const {
	return destenetion;
}

address order::getFrom(void) const {
	return startPoint;
}

bool order::operator< (const order& obj) const {
	return this->time < obj.time;
}