#ifndef SICT_ITEMSET_H
#define SICT_ITEMSET_H

#include "Utilities.h"

namespace sict
{
	class ItemSet
	{
		//Utilities to include fieldwidth functions
		Utilities util;

		//tokens
		std::string name;
		unsigned int serial;
		unsigned int quantity;
		std::string description;

	public:

		ItemSet();
		ItemSet(std::string&);
		const std::string& getName() const;
		const unsigned int getSerialNumber() const;
		const unsigned int getQuantity() const;
		ItemSet& operator--();
		void display(std::ostream& os, bool full) const;

		//move constructor
		ItemSet(ItemSet&&);


		//disabled copy constructor
		ItemSet(const ItemSet& incomingObj) = delete;
		//disabled copy assignment
		ItemSet& operator=(const ItemSet& incomingObj) = delete;
		//disabled move assignment
		ItemSet& operator=(ItemSet&& incomingObj) = delete;
	};
}

#endif
