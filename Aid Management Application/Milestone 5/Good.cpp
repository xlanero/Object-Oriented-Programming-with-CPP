// Final Project Milestone 3
//
// Version 1.0
// Date Nov 25, 2018
// Author LISA NIRO 108760182
// Description: Good.cpp implementation file
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <fstream>

#include "Good.h"
#include "Error.h"
#include "iGood.h"

using namespace std;

namespace aid
{
	//stores the name of Good in dynamic mem, replaces any previously stored
	void Good::name(const char* pName) {

		//removes name of Good from memory if incoming parameter is nullptr or empty
		if (pName == nullptr || pName[0] == '\0') {
			delete[] gName;
			gName = nullptr;
		}
		else {
			//stores the name
			gName = new char[(strlen(pName)) + 1];
			strncpy(gName, pName, (strlen(pName)));
			gName[(strlen(pName))] = '\0';
		}
	}


	const char* Good::name() const {

		if (isEmpty()) {
			//checks if empty string and returns nullptr
			return nullptr;
		}

		return gName;
	}


	// returns address of sku of Good
	const char* Good::sku() const {

		return gSku;
	}


	// returns address of unit description of Good
	const char* Good::unit() const {

		return gUnit;
	}


	// returns if the object is taxable
	bool Good::taxed() const {

		return taxStatus;
	}


	// returns price of single item of Good before tax
	double Good::itemPrice() const {

		return subtotal;
	}


	// returns price of sngle item after tax
	double Good::itemCost() const {

		double itemC = itemPrice();

		if (taxStatus == true) {
			//calculates price after tax
			itemC = (subtotal * TAX_RATE) + subtotal;
		}
		else {
			itemC = subtotal;
		}
		return itemC;
	}


	//receives error message and stores that message in Error object to the current object
	void Good::message(const char* pError) {

		return gErr.message(pError);
	}


	// returns true if Error object is clear
	bool Good::isClear() const {

		return gErr.isClear();
	}

	//public member functions

	Good::Good(char pType) {

			type = pType;
			//sets current objet to safe empty state
			gName = nullptr;
			gSku[0] = '\0';
			gUnit[0] = '\0';
			qty = 0;
			taxStatus = false;
			subtotal = 0;
			qtyNeed = 0;
			Error();
	
	}

	//seven argument constructor
	// allocates enough memory to hold the name of the Good
	Good::Good(const char * gsku, const char * nm, const char * gunit, int currUnits, bool tx, double subt, int need) {

		if (gsku != nullptr || nm != nullptr || gunit != nullptr) {

			strncpy(gSku, gsku, max_sku_length);
			gSku[max_sku_length] = '\0';
			name(nm);
			strncpy(gUnit, gunit, max_unit_length);
			gUnit[max_unit_length] = '\0';
			qty = currUnits;
			taxStatus = tx;
			subtotal = subt;
			qtyNeed = need;
		}

		else {
			//sets to empty state with zero-one argument constructor
			*this = Good('N');
		
		}
	}


	//copies object referenced to current object
	Good::Good(const Good& g) {

		*this = g;
	}

	//copy assignment operator
	// replaces current object with copy of referenced object
	Good& Good::operator=(const Good& g) {
		if (this != &g) {

			type = g.type;
			strncpy(gSku, g.gSku, max_sku_length);
			gSku[max_sku_length] = '\0';
			strncpy(gUnit, g.gUnit, max_unit_length);
			gUnit[max_unit_length] = '\0';
			name(g.gName);
			qty = g.qty;
			qtyNeed = g.qtyNeed;
			subtotal = g.subtotal;
			taxStatus = g.taxStatus;
		}
		else {

			gName = nullptr;
		}

		return *this;
	}


	// deallocating dynamic memory
	Good::~Good() {

		delete[] gName;
		gName = nullptr;
	}


	//***FIX
	std::fstream& Good::store(std::fstream& file, bool newLine) const {
		if (type == 'N') {
			file << type << "," 
				<< sku() << "," 
				<< name() << "," 
				<< unit() << "," 
				<< qty << "," 
				<< subtotal << "," 
				<< qty << "," 
				<< qtyNeed;

			if (newLine) {
				file << endl;
			}
		}

		if (type == 'P') {
			file << type << "," 
				<< sku() << "," 
				<< name() << "," 
				<< unit() << "," 
				<< taxStatus << ","
				<< subtotal << "," 
				<< qty << "," 
				<< qtyNeed;

			if (newLine) {
				file << endl;
			}
		}
		return file;
	}


	//extracts fields for a single record, creates temporary object, opy assigns temp obj to current obj
	std::fstream& Good::load(std::fstream& file) {

		char sk[max_sku_length + 1], un[max_unit_length + 1], nm[max_name_length + 1], t;
		int qty, qtyN;
		double sub;
		bool tax;

		
		file.getline(sk, max_sku_length, ',');
		file.getline(nm, max_name_length, ',');
		file.getline(un, max_unit_length, ',');
		file >> tax >> t;
		file >> sub >> t;
		file >> qty >> t;
		file >> qtyN;

		//remember to match parameter order
		Good temp(sk, nm, un, qty, tax, sub, qtyN);

		*this = temp;
		return file;
	}


	//printing to screen
	std::ostream& Good::write(std::ostream& os, bool linear) const {

		if (gErr.isClear()) {
			if (linear) {

				os.unsetf(ios::right);
				os.width(max_sku_length);
				os.setf(ios::left);
				os << sku() << "|";
				os.width(20);

				//if empty, does not display anything
				if (isEmpty()) {
					os << "" << "|";
				}

				else {
					os << name() << "|";
				}

				//formatting
				os.unsetf(ios::left);
				os.width(7);
				os.setf(ios::right);
				os << std::fixed;
				os.precision(2);

				if (taxStatus == true) {
					os << itemCost() << "|";
				}
				else {
					os << itemPrice() << "|";
				}
				os.width(4);
				os.setf(ios::right);
				os << qty << "|";
				os.unsetf(ios::right);
				os.width(10);
				os.setf(ios::left);
				os << unit() << "|";
				os.width(4);
				os.setf(ios::right);
				os << qtyNeed << "|";
			}

			else {
				//separates lines when false
				os << " Sku: " << sku() << endl;

				os << " Name (no spaces): " << name() << endl;
				os << " Price: " << itemPrice() << endl;

				//checks if item is taxed and then displays cost
				if (taxed()) {
					os << " Price after tax: ";
					os << total_cost() << endl;
				}

				else {
					os << " Price after tax:  N/A" << endl;
				}

				os << " Quantity on Hand: " << qty << " " << unit() << endl;
				os << " Quantity needed: " << qtyNeed;
				os.clear();
			}
		}

		else {
			os.clear();
			os << gErr.message();
		}
		
		return os;
	}


	//reads input
	std::istream& Good::read(std::istream& is) {

		char sk[max_sku_length + 1], un[max_unit_length + 1], nm[max_name_length + 1], t;
		int qt, qtyN;
		double sub;
		//bool tx;

		gErr.clear();
		//print sku
		cout << " Sku: ";
		is >> sk;
		strncpy(gSku, sk, max_sku_length);

		//print name
		is.ignore(2000, '\n');
		cout << " Name (no spaces): ";
		is >> nm;
		name(nm);

		//print unit
		is.ignore(2000, '\n');
		cout << " Unit: ";
		is >> un;
		strncpy(gUnit, un, max_unit_length);

		//print if taxed or not
		is.ignore(2000, '\n');
		cout << " Taxed? (y/n): ";
		is >> t;

		if (!(t == 'y' || t == 'Y' || t == 'n' || t == 'N')) {
			is.setstate(ios::failbit);
			gErr.message("Only (Y)es or (N)o are acceptable");
			
			
		}
		else {
			//input must be a y/Y if item is taxed
			if (t == 'y' || t == 'Y') {

				taxStatus = true;
			}

			if (t == 'n' || t == 'N') {
				taxStatus = false;
			}
		}

		if (!is.fail()) {
			//prints price
			cout << " Price: ";
			is >> sub;
			is.clear();

			if (sub <= 0) {
				//displays error messsage
				gErr.message("Invalid Price Entry");
				is.setstate(ios::failbit);
			}
			else {
				subtotal = sub;
			}
		}

		if (!is.fail()) {
			//print quantity on hand
			cout << " Quantity on hand: ";
			is >> qt;
			is.clear();

			if (qt <= 0 ) {
				//displays error messsage
				gErr.message("Invalid Quantity Entry");
				is.setstate(ios::failbit);
			}
			qty = qt;
		}

		if (!is.fail()) {
			//print needed quantity
			cout << " Quantity needed: ";
			is >> qtyN;

			if (qtyN <= 0) {
				//displays error messsage
				gErr.message("Invalid Quantity Needed Entry");
				is.setstate(ios::failbit);

			}
			qtyNeed = qtyN;
		}

		if (!is.fail()) {
			is.clear();
			gErr.clear();
		}
		cin.ignore(1000, '\n');
		return is;
	}


	// compares string to sku of current object
	bool Good::operator==(const char * s) const {

		return (strcmp(this->gSku, s) == 0);
	}

	//calculate total cost of all items of the Good, including tax
	double Good::total_cost() const {

		return (itemCost() * qty);
	}

	//resets number of units on hand
	void Good::quantity(int pQty) {
		qty = pQty;
	}

	//checks for empty state
	bool Good::isEmpty() const {

		return (gName == nullptr || gName[0] == '\0');
	}

	// returns number of units that are needed
	int Good::qtyNeeded() const {

		return qtyNeed;
	}

	// returns number of units that are on hand
	int Good::quantity() const {

		return qty;
	}

	// returns true if sku of current object is greater than the string at received address (strcmp)
	bool Good::operator>(const char* s) const {

		return (strcmp(gSku, s) > 0);
	}

	// returns true if name of current object is greater than the string at received address (strcmp)
	bool Good::operator>(const iGood& g) const {

		return (strcmp(this->name(), g.name()) > 0);
	}

	//updates the quantity of the Good object
	int Good::operator+=(int qtyG) {
		if (qtyG > 0) {

			qty += qtyG;
		}
		return qty;
	}

	//Helper Functions
	//insert Good record into ostream
	std::ostream& operator<<(std::ostream& ostr, const iGood& g) {

		return g.write(ostr, true);
	}


	//reads Good record from istream
	std::istream& operator>>(std::istream& istr, iGood& g) {

		return g.read(istr);
	}


	//adds total cost of Good obj to received double and returns update
	double operator+=(double& t, const iGood& g) {

		double total;
		total = t + g.total_cost();

		return total;
	}

	//
}