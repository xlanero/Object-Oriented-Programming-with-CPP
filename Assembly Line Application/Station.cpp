#include "Station.h"
#include "ItemSet.h"

namespace sict
{
	// Receives a reference to an unmodifiable string and passes that reference to the ItemSet sub-object of the current object
	//
	Station::Station(const std::string& string) : stationItemSet(string){
		
		stationName = { stationItemSet.getName() };
	}

	// displays ItemSet object information into os
	void Station::display(std::ostream& os) const {

		stationItemSet.display(os, true);
	}

	// fills the last order in the customer order queue (if there is one), if the queue is empty, the function does nothing
	//
	void Station::fill(std::ostream& os) {
		//checks if empty
		if (!stationOrderQueue.empty()) {
			//fills
			stationOrderQueue.front().fillItem(stationItemSet, os);
		}
	}

	// returns a reference to the name of the ItemSet sub-object
	//
	const std::string& Station::getName() const {

		return stationItemSet.getName();
	}

	// Returns the release state of the current object
	// Return true if the station has filled item requests for the customer order at the front of the queue or the station has no items left
	//
	bool Station::hasAnOrderToRelease() const {

		bool filled = stationOrderQueue.front().isItemFilled(this->getName());

		if (stationItemSet.getQuantity() == 0 || !filled) {
			return false;
		}
		else {
			return true;
		}

	}

	Station& Station::operator--() {
		--stationItemSet;
		return *this;
	}

	// (Modifier) - Receives an rvalue reference to a CustomerOrder object and moves that CustomerOrder object to the back of the station's queue and returns a reference to the current object
	//
	Station& Station::operator+=(CustomerOrder&& order) {
		stationOrderQueue.push(std::move(order));
		return *this;
	}

	bool Station::pop(CustomerOrder& ready) {

		// check if the order at the front of the station's queue is filled
		bool filled = false;

		if (!stationOrderQueue.empty()) {
			ready.isItemFilled(stationName);
			ready = std::move(stationOrderQueue.front());
			stationOrderQueue.pop();
		}

		return filled;
	}

	// reports state of the ItemSet object into ostream
	void Station::validate(std::ostream & os) const {

		os << " getName(): " << stationItemSet.getName() << std::endl;
		os << " getSerialNumber(): " << stationItemSet.getSerialNumber() << std::endl;
		os << " getQuantity(): " << stationItemSet.getQuantity() << std::endl;
	}

}