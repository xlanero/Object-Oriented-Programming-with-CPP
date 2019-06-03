#ifndef SICT_STATION_H
#define SICT_STATION_H

#include <queue>
#include <iostream>
#include <string>

#include "ItemSet.h"
#include "CustomerOrder.h"

namespace sict
{
	/**
	* Contains all the functionality for filling customer orders with items.
	* NOTE: Each station that has an order can fill one request at a time for an ITEM from that station (each station has one item)
	* An order can be incomplete due to insufficient items in stock to cover its requests
	*/
	class Station {

		//CustomerOrder queue
		std::queue<CustomerOrder> stationOrderQueue;
		// ItemSet subobject
		ItemSet stationItemSet;
		// name of station (which is the name of the ItemSet subobject)
		std::string stationName;

	public:

		explicit Station(const std::string&);
		void display(std::ostream& os) const;
		void fill(std::ostream& os);
		const std::string& getName() const;
		bool hasAnOrderToRelease() const;
		Station& operator--();
		Station& operator+=(CustomerOrder&& order);
		bool pop(CustomerOrder& ready);
		void validate(std::ostream& os) const;

		// disabled copy & move constructors and assignments
		Station(const Station&) = delete;
		Station& operator=(const Station&) = delete;
		Station(Station&&) = delete;
		Station& operator=(Station&&) = delete;

	};
}

#endif
