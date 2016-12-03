#include "TaxiPark.h"
#include <algorithm>
#include <set>
#include <utility>
#include <iostream>

using std::cout;
using std::set;

TaxiPark::TaxiPark(Driver* drivers, int sizeDrivers, std::shared_ptr<order>* orders, int sizeOrders) : isOut(sizeOrders, 0) {
	this->drivers.resize(sizeDrivers);
	std::copy(drivers, drivers + sizeDrivers, this->drivers.begin());

	std::for_each(orders, orders + sizeOrders, [&](std::shared_ptr<order> elem) {
		this->orders.push_back(*elem);
	});

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

	int index = 0;
	std::for_each(orders.begin(), orders.end(), [&Events, &index](order& elem) mutable {
		Events.insert({ elem.getTime(), true, index });
		index++;
	});

	cout << "Start woking:\n\n";

	while (!Events.empty()) {
		auto iter = Events.begin();

		if (!isOut[iter->index]) {
			isOut[iter->index] = 1;
			cout << iter->time << ": \n\tNew order #" << iter->index + 1 << "\n\tFrom point: " << orders[iter->index].getFrom().x << ", "
				<< orders[iter->index].getFrom().y << "\n\tTo: " << orders[iter->index].getDest().x << ", " << orders[iter->index].getDest().y << "\n";

			cout << "Free:\n";
			int i = 0;
			std::for_each(drivers.begin(), drivers.end(), [&](Driver& elem) {
				cout << "Driver " << elem.getName() << " Is free:" << !elem.getIsOnDuty();
				eventElement event = { elem.getTimeOfEndingOrder() + timeToComplete(i, iter->index) , false, i };
				cout << "\tTime of complete: " << event.time << "\n";
				i++;
			});

			cout << "\n";
		}

		if (iter->type) {
			int index = searhBestFree(iter->index);
			
			if (index != drivers.size()) {
				orders[iter->index].setIsCompleted(true);
				drivers[index].addTicket(tuple<Driver, order>(drivers[index], orders[iter->index]));
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
	int i = 0;
		
	std::for_each(drivers.begin(), drivers.end(), [&](Driver& elem) {
		if (!elem.getIsOnDuty() && timeToGet(i, orderIndex) <= orders[orderIndex].getWaiting())
			if (index == drivers.size() || timeToGet(i, orderIndex) < timeToGet(index, orderIndex)) index = i;
		i++;
	});

	return index;
}

int TaxiPark::searhBestOnDuty(int orderIndex) {
	int index = drivers.size();
	int i = 0;

	if (index == drivers.size())
		std::for_each(drivers.begin(), drivers.end(), [&](Driver elem) {
			if (elem.getIsOnDuty() && elem.getTimeOfEndingOrder() + timeToGet(i, orderIndex) <= orders[orderIndex].getWaiting() + orders[orderIndex].getTime())
				if (index == drivers.size() || elem.getTimeOfEndingOrder() + timeToGet(i, orderIndex) < drivers[index].getTimeOfEndingOrder() + timeToGet(index, orderIndex)) index = i;
			i++;
		});

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
	std::for_each(drivers.begin(), drivers.end(), [&](Driver elem) {
		cout << "Driver " << elem.getName() << " charged: ";
		int charge = 0;

		const vector<tuple<Driver, order>>& tikets = elem.getTickets();

		std::for_each(tikets.begin(), tikets.end(), [&charge](const tuple<Driver, order>& elem) {
			charge += std::get<1>(elem).getCost();
		});

		cout << charge << "$\n";
	});
}