#pragma once
#include "Address.h"
#define phoneSize 13

class order {
private:
	short time; // Time of order in format time = hours * 60 + minutes
	address destenetion; // Point of destenetion
	char phone[phoneSize]; // Phone number in international format
	address startPoint; // Position of client
	short waiting; // Time of client waiting

	bool isComplered; // Is completed oreder

	bool cheakPhone(char* phone); // Cheacking phone format
	bool cheakTime(char* time); // Cheaking time

public:
	bool operator< (const order& obj) const;

	order(char* timeOfOrder, address dest, address from, char* phone, short waiting);

	bool getIsCompleted(void);
	void setIsCompleted(bool value);

	int getCost(void) const;
	short getTime(void) const;
	short getWaiting(void) const;
	address getDest(void) const;
	address getFrom(void) const;
};