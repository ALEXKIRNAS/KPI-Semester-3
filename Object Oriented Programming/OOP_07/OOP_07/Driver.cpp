#include "Driver.h"
#include "CException.h"
#include <string.h>

Driver::Driver(void) {}

Driver::Driver(char* name, char* car) {
	if (strlen(name) == 0) throw CException("Empty name of driver");
	if(strlen(car) == 0) throw CException("Empty car name for driver");
	this->name = string(name);
	this->car = string(car);

	isOnDuty = false;
	curAddr.x = curAddr.y = 0;
	timeOfEndingOrder = 0;
}

void Driver::addTicket(const tuple<Driver, order>&&  ticket) {
	tikets.push_back(ticket);
}

const vector <tuple<Driver, order>>& Driver::getTickets(void) {
	return tikets;
}

bool Driver::getIsOnDuty(void) {
	return isOnDuty;
}

void Driver::setOnDuty(void) {
	isOnDuty = !isOnDuty;
}

void Driver::setAddr(address addr) {
	this->curAddr = addr;
}

short Driver::getTimeOfEndingOrder(void) {
	return timeOfEndingOrder;
}

void Driver::setTimeOfEndingOrder(short time) {
	timeOfEndingOrder = time;
}

address Driver::getAddr(void) {
	return curAddr;
}

const string& Driver::getName(void) {
	return name;
}