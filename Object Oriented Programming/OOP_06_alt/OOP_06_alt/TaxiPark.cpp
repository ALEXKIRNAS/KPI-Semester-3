#include "TaxiPark.h"
#include <algorithm>
#include <set>
#include <utility>
#include <iostream>

using std::cout;
using std::set;

TaxiPark::TaxiPark(Driver* drivers, int sizeDrivers, order* orders, int sizeOrders) {
	for (int i = 0; i < sizeDrivers; i++) this->drivers.push_back(drivers[i]);
	for (int i = 0; i < sizeOrders; i++) this->orders.push_back(orders[i]);
}

void TaxiPark::wokr(void) {

	class eventElement {
	public:
		short time;
		bool type;
		int index;

		bool operator< (const eventElement& obj) const {
			if (time != obj.time) return time < obj.time;
			if (index != obj.index) return index < obj.index;
			if(type != obj.type) return type;
			else return false;
		}
	};

	set <eventElement> Events; // type of event  (0 - woker is free, 1 - new order)

	for (int i = 0, size = orders.size(); i < size; i++)
		Events.insert({ orders[i].getTime(), true, i });

	cout << "Start woking:\n\n";

	while (!Events.empty()) {
		auto iter = Events.begin();

		if (iter->type) {
			int index = searhBestFree(iter->index);
			
			if (index != drivers.size()) {
				orders[iter->index].setIsCompleted(true);
				drivers[index].addTicket(Ticket<Driver, order>(drivers[index], orders[iter->index]));
				setDriverWork(index, iter->index, iter->time);
				eventElement event = { drivers[index].getTimeOfEndingOrder() , false, index };
				Events.insert(event);

				cout << iter->time << ": \n\tDriver " << drivers[index].getName() << " start to transit customer\n\tFrom point: " << orders[iter->index].getFrom().x << ", "
					<< orders[iter->index].getFrom().y << "\n\tTo: " << orders[iter->index].getDest().x << ", " << orders[iter->index].getDest().y << "\n"
					<< "\tTime of complete: " << event.time << "\n" << "\tOrder #" << iter->index + 1 << "\n\n";
				
			}
			else {
				index = searhBestOnDuty(iter->index);
				if (index == drivers.size()) {
					orders[iter->index].setIsCompleted(false);
					cout << iter->time << ": \n\tOrder #" << iter->index + 1 << " FAILD! No free drivers!\n\n";
				}
				else {
					eventElement event = *iter;
					event.time = drivers[index].getTimeOfEndingOrder();
					Events.insert(event);
				}
			}
		}
		else {
			drivers[iter->index].setOnDuty();
			cout << iter->time << ": \n\tDriver " << drivers[iter->index].getName() << " ready to transit new customer!\n"
				<< "\tStandby in point: " << drivers[iter->index].getAddr().x << ", " << drivers[iter->index].getAddr().y << "\n\n";
		}

		Events.erase(iter);
	}
}

int TaxiPark::searhBestFree(int orderIndex) {
	int index = drivers.size();

	for (int i = 0, size = drivers.size(); i < size; i++)
		if (!drivers[i].getIsOnDuty() && timeToGet(i, orderIndex) <= orders[orderIndex].getWaiting())
			if(index == size || timeToGet(i, orderIndex) < timeToGet(index, orderIndex)) index = i;

	return index;
}

int TaxiPark::searhBestOnDuty(int orderIndex) {
	int index = drivers.size();

	if (index == drivers.size())
		for (int i = 0, size = drivers.size(); i < size; i++)
			if (drivers[i].getIsOnDuty() && drivers[i].getTimeOfEndingOrder() + timeToGet(i, orderIndex) <= orders[orderIndex].getWaiting() + orders[orderIndex].getTime())
				if(index == size || drivers[i].getTimeOfEndingOrder() + timeToGet(i, orderIndex) < drivers[index].getTimeOfEndingOrder() + timeToGet(index, orderIndex)) index = i;
	return index;
}

void TaxiPark::setDriverWork(int indexOfDriver, int indexOfOrder, short curTime) {
	drivers[indexOfDriver].setTimeOfEndingOrder(curTime + timeToComplete(indexOfDriver, indexOfOrder));
	drivers[indexOfDriver].setAddr(orders[indexOfOrder].getDest());
	drivers[indexOfDriver].setOnDuty();
}

short TaxiPark::timeToGet(int indexOfDriver, int indexOfOrder) {
	int deltaX = abs(drivers[indexOfDriver].getAddr().x - orders[indexOfOrder].getFrom().x);
	int deltaY = abs(drivers[indexOfDriver].getAddr().y- orders[indexOfOrder].getFrom().y);
	return deltaX + deltaY;
}

short TaxiPark::timeToComplete(int indexOfDriver, int indexOfOrder) {
	int deltaX = abs(orders[indexOfOrder].getDest().x - orders[indexOfOrder].getFrom().x);
	int deltaY = abs(orders[indexOfOrder].getDest().y - orders[indexOfOrder].getFrom().y);

	return timeToGet(indexOfDriver, indexOfOrder) + deltaX + deltaY;
}

void TaxiPark::calcCharge(void) {
	for (int i = 0, size = drivers.size(); i < size; i++) {
		cout << "Driver " << drivers[i].getName() << " charged: ";
		int charge = 0;

		const vector<Ticket <Driver, order>>& tikets = drivers[i].getTickets();

		for (int z = 0; z < tikets.size(); z++)
			charge += tikets[z].getCost();

		cout << charge << "$\n";
	}
}