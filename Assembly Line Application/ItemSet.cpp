#include <iostream>
#include "ItemSet.h"
#include "Utilities.h"

namespace sict
{
	//default constructor sets to safe, empty state
	ItemSet::ItemSet(){

		name.clear();
		serial = 0;
		quantity = 0;
		description.clear();
	}

	//extracts 4 tokens, populates object with tokens and determines fieldWidth for display
	ItemSet::ItemSet(std::string& str){

		// MS2: UPDATED CONSTRUCTOR TO FIX ERRORS IN ASSIGNING EXTRACTED TOKENS

		//populates object with tokens
		try {
			size_t next_pos = str.find(util.getDelimiter());

			name = str.substr(0, next_pos);
			//converts to unsigned integer
			serial = std::stoul(util.extractToken(str, next_pos));
			//converts to unsigned integer
			quantity = std::stoul(util.extractToken(str, next_pos));
			description = util.extractToken(str, next_pos);

			// updates the fieldWidth
			if (util.getFieldWidth() < name.length()) {
				util.setFieldWidth(name.length());
			}
			
		}

		//catches the error message thrown from Utilites, if error occured in extractToken
		catch (const char* error) {
			std::cout << error << std::endl;
		}
	}

	// MS2 EDIT: clearing temp object
	ItemSet::ItemSet(ItemSet&& is){

		//checks for self assignment
		if (this != &is) {

			//moves the incoming data into the current object
			name = is.name;
			description = is.description;
			serial = is.serial;
			quantity = is.quantity;

			//clears temporary object
			is.name = "";
			is.description = "";
			is.serial = 0;
			is.quantity = 0;
		}
	}

	//returns name of item
	const std::string & ItemSet::getName() const {

		return name;
	}

	//returns serial number of item
	const unsigned int ItemSet::getSerialNumber() const {

		return serial;
	}

	//returns remaining number of items in set
	const unsigned int ItemSet::getQuantity() const {

		return quantity;
	}

	//operator that reduces quantity by one, increases serial number by one
	ItemSet & ItemSet::operator--(){

		quantity--;
		serial++;
		return *this;
	}

	//inserts data for the current object into the ostream
	void ItemSet::display(std::ostream & os, bool full) const {

		size_t fw = util.getFieldWidth();
		//MS2: had to make adjustments to fieldWidth for submitter
		if (full) {

			os << std::left 
				<< std::setw(fw - 11) 
				<< name 
				<< " [" 
				<< std::setw(5) 
				<< serial 
				<< "] Quantity " 
				<< std::setw(3) 
				<< quantity 
				<< " Description: " 
				<< description 
				<< std::endl;
		}
		else {

			os << std::left 
				<< std::setw(fw - 11) 
				<< name << " [" 
				<< std::setw(5) 
				<< serial << "]" 
				<< std::endl;
		}
	}
}