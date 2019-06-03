#ifndef SICT_CUSTOMER_ORDER_H
#define SICT_CUSTOMER_ORDER_H

#include <string>
#include <iostream>

#include "ItemSet.h"
#include "Utilities.h"

namespace sict
{
	class CustomerOrder {
		
		// nested object to hold item information
		struct ItemInfo {
			std::string itemName;
			int itemSerial;
			bool itemFilled;
			// sets item info to default state
			ItemInfo() {
				itemName = ""; 
				itemSerial = 0;
				itemFilled = false;
			}
		};

		ItemInfo* itemInfo;
		std::string customerName;
		std::string productName;
		size_t numItems;
		static size_t fieldWidth;

	public:
		CustomerOrder();
		explicit CustomerOrder(const std::string&);
		CustomerOrder(CustomerOrder&&);
		CustomerOrder& operator=(CustomerOrder&&);
		~CustomerOrder();

		void fillItem(ItemSet&, std::ostream&);
		bool isFilled() const;
		bool isItemFilled(const std::string&) const;
		std::string getNameProduct() const;
		void display(std::ostream& os, bool showDetail = false) const;

		// disabled copy constructor and copy assignment
		CustomerOrder(const CustomerOrder&) = delete;
		CustomerOrder& operator=(const CustomerOrder&) = delete;
	};
}

#endif
