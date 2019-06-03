// Final Project Milestone 3
//
// Version 1.0
// Date Nov 25, 2018
// Author LISA NIRO 108760182
// Description: Good.h header file
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#ifndef AID_GOOD_H
#define AID_GOOD_H

#include <iostream>
#include "Error.h"

namespace aid
{
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double TAX_RATE = 0.13;

	class Good {

		char type;
		char gSku[max_sku_length + 1];
		char gUnit[max_unit_length + 1];
		char * gName = nullptr;
		int qty;
		int qtyNeed;
		double subtotal;
		bool taxStatus;
		Error gErr;

	protected:

		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char*);
		bool isClear() const;

	public:
		//construtors
		Good(char type = 'N');
		Good(const char *, const char *, const char *, int qty = 0, bool taxStatus = true, double subtotal = 0, int qtyNeed = 0);
		Good(const Good&);
		//copy assignment operator
		Good& operator=(const Good&);
		//destructor
		~Good();

		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);

		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const Good&) const;
		int operator+=(int);
	};

	//helper functions
	std::ostream& operator<<(std::ostream&, const Good&);
	std::istream& operator>>(std::istream&, Good&);
	double operator+=(double&, const Good&);
}
#endif
