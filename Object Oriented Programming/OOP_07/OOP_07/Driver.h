#pragma once
#include "Address.h"
#include "Order.h"
#include <vector>
#include <tuple>
#include <string>

using std::vector;
using std::tuple;
using std::string;

class Driver {
private:
	string name;
	string car;
	vector <tuple <Driver, order>> tikets;

	address curAddr; // Current address
	bool isOnDuty;
	short timeOfEndingOrder;
public:

	Driver(char* name, char* car);
	Driver();

	void addTicket(const tuple<Driver, order>&&  ticket);
	const vector <tuple<Driver, order>>& getTickets(void);

	bool getIsOnDuty(void);
	void setOnDuty(void);
	void setAddr(address);
	address getAddr(void);
	short getTimeOfEndingOrder(void);
	void setTimeOfEndingOrder(short time);
	const string& getName(void);
};