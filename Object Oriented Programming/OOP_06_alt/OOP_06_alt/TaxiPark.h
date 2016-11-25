#pragma once
#include "Driver.h"
#include "Order.h"
#include "Tiket.h"
#include <vector>
#include "Order.h"
#include "Driver.h"

using std::vector;

class TaxiPark {
private:
	vector <order> orders;
	vector <Driver> drivers;
	
	int searhBestFree(int orderIndex); // Searching best driver for curr order
	int searhBestOnDuty(int orderIndex); // Searching best driver for curr order
	void setDriverWork(int indexOfDriver, int indexOfOrder, short curTime); // Setting driver to complete new order
	short timeToGet(int indexOfDriver, int indexOfOrder); // Calculation of time to get to the costumer
	short timeToComplete(int indexOfDriver, int indexOfOrder); // Calculation of time to finish order

public:
	
	TaxiPark(Driver* drivers, int sizeDrivers, order* orders, int sizeOrders);
	void calcCharge(void);
	void wokr(void);
};