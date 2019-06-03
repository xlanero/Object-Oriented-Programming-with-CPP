#include <iomanip>
#include <vector>
#include <algorithm>

#include "CustomerOrder.h"
#include "ItemSet.h"
#include "Utilities.h"

namespace sict
{
	size_t CustomerOrder::fieldWidth = 0;

	// safe empty state
	CustomerOrder::CustomerOrder() {
		itemInfo = nullptr;
		customerName = "";
		productName = "";
		numItems = 0;
	}

	// extracts at least 3 tokens from the received string and allocates memory for items
	CustomerOrder::CustomerOrder(const std::string& str) : CustomerOrder() {

		//temporary Utilities object for extractToken(), getDelimiter(), getFieldWidth()
		Utilities util;
		// determine the fieldWidth for the class
		if (fieldWidth < util.getFieldWidth()) {
			fieldWidth = util.getFieldWidth();
		}

		// delimiter variable
		size_t DEL = str.find(util.getDelimiter());

		// extracts customer and product names
		customerName = str.substr(0, DEL);
		productName = util.extractToken(str, DEL);


		// records to number of items in the record to store into item information
		numItems = std::count(str.begin(), str.end(), util.getDelimiter()) - 1;

		// allocates memory for the number of items in the record
		itemInfo = new ItemInfo[numItems];
		if (numItems >= 1) {

			for (size_t i = 0; i < numItems; i++) {
				// extracts item info for each item
				itemInfo[i].itemName = util.extractToken(str, DEL);
			}
		}
		// throws exception if no items have been requested to be added
		else {
			throw "***No items requested to be added***";
		}

	}

	// move constructor
	CustomerOrder::CustomerOrder(CustomerOrder&& co) {
		*this = std::move(co);
	}

	// move assigment operator
	CustomerOrder & CustomerOrder::operator=(CustomerOrder&& custO) {

		if (this != &custO) {

			customerName = custO.customerName;
			productName = custO.productName;
			numItems = custO.numItems;
			itemInfo = custO.itemInfo;

			custO.itemInfo = nullptr;
		}
		return *this;
	}

	// deallocates memory
	CustomerOrder::~CustomerOrder() {

		delete[] itemInfo;
		itemInfo = nullptr;
	}

	// checks item request and fills if item available and not filled yet, inserts information into ostream
	void CustomerOrder::fillItem(ItemSet& item, std::ostream& os) {

		for (size_t i = 0; i < numItems; i++) {

			if (item.getName() == itemInfo[i].itemName) {
				// if not available
				if (item.getQuantity() == 0) {
					os << " Unable to fill " 
						<< customerName 
						<< " [" 
						<< productName 
						<< "][" 
						<< itemInfo[i].itemName 
						<< "][" 
						<< itemInfo[i].itemSerial 
						<< "] out of stock" 
						<< std::endl;
				}
				else {
					// if already filled
					if (itemInfo[i].itemFilled) {
						os << " Unable to fill "
							<< customerName
							<< " ["
							<< productName
							<< "]["
							<< itemInfo[i].itemName
							<< "]["
							<< itemInfo[i].itemSerial
							<< "] already filled"
							<< std::endl;
					}

					// fills request
					else {
						itemInfo[i].itemSerial = item.getSerialNumber();
						itemInfo[i].itemFilled = true;
						//decrements item stock by one
						item.operator--();

						os << " Filled " 
							<< customerName 
							<< " [" 
							<< productName 
							<< "][" 
							<< itemInfo[i].itemName 
							<< "][" 
							<< itemInfo[i].itemSerial 
							<< "]" 
							<< std::endl;
					}
				}
			}
		}
	}

	// loops through requested items and returns true if filled
	bool CustomerOrder::isFilled() const {

		for (size_t i = 0; i < numItems; i++) {
			if (!itemInfo[i].itemFilled) {
				return false;
			}
		}
		return true;
	}

	// returns true if all items in the request list have been filled
	bool CustomerOrder::isItemFilled(const std::string& item) const {

		for (size_t i = 0; i < numItems; i++) {
			// compares name to received parameter and checks its bool itemFilled status
			if (itemInfo[i].itemName == item) {
				if (!itemInfo->itemFilled) {
					return false;
				}
			}
		}
		return true;
	}

	// returns customer name and product
	std::string CustomerOrder::getNameProduct() const {
		return std::string(customerName) + "[" + std::string(productName) + "]";
	}

	// inserts data into the ostream and determines to show item details or not
	void CustomerOrder::display(std::ostream & os, bool showDetail) const {

		// had to make adjustments to fieldWidth for submitter
		os << std::left << std::setw(fieldWidth - 11) 
			<< customerName 
			<< " [" 
			<< productName 
			<< "]" 
			<< std::endl;

		if (!showDetail) {

			for (size_t i = 0; i < numItems; i++) {
				os << std::setfill(' ') 
					<< std::setw(fieldWidth - 10) 
					<< "    " << std::right 
					<< itemInfo[i].itemName 
					<< std::endl;
			}
		}
	}
}