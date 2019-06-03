// Final Project Milestone 5
//
// Version 1.0
// Date 
// Author LISA NIRO 108760182
// Description: Perishable.cpp implementation file
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////


#include <iostream>
#include <fstream>
#include "Perishable.h"




using namespace std;

namespace aid
{
	//passes file record tag and sets to empty state
	Perishable::Perishable() : Good ('P') {

		expDate = Date();
	}

	//stores a single file record for the current object, appends expDate
	fstream& Perishable::store(fstream& file, bool newLine) const {

		Good::store(file, false);
	

			if (newLine == true) {

				file << "," << expDate << endl;
			}
			else{ 
				file << "," << expDate; 
			}
	

		return file;
	}

	//extracts data fields from an fstream object
	fstream& Perishable::load(fstream& file) {
		if (file.is_open()) {
			Good::load(file);
			int tY, tM, tD;
			char c;
			file >> c;
			file >> tY >> c;
			file >> tM >> c;
			file >> tD;

			Date temp(tY, tM, tD);
			expDate = temp;
		}
		return file;

	}

	//inserts expDate if not in safe empty state
	ostream& Perishable::write(ostream& os, bool linear) const {

		Good::write(os, linear);

		if (isClear() && !isEmpty())
		{
			if (linear)
				expDate.write(os);

			else
			{
				os << "\n Expiry date: ";
				expDate.write(os);
			}
		}
		return os;
	}

	//reads the input data and sends error messages if does not pass requirements
	istream& Perishable::read(istream& is) {
		Good::read(is);

		if (!is.fail()) {
			cout << " Expiry date (YYYY/MM/DD): ";
			is >> expDate;

			if (expDate.errCode() == CIN_FAILED)
			{
				is.setstate(std::ios::failbit);
				Good::message("Invalid Date Entry");
				
			}

			if (expDate.errCode() == YEAR_ERROR)
			{
				is.setstate(std::ios::failbit);
				Good::message("Invalid Year in Date Entry");
				
			}

			if (expDate.errCode() == MON_ERROR)
			{
				is.setstate(std::ios::failbit);
				Good::message("Invalid Month in Date Entry");
				
			}

			if (expDate.errCode() == DAY_ERROR)
			{
				is.setstate(std::ios::failbit);
				Good::message("Invalid Day in Date Entry");
				
			}

			if (expDate.errCode() == PAST_ERROR)
			{
				is.setstate(std::ios::failbit);
				Good::message("Invalid Expiry in Date Entry");
				
			}

		
		}

		return is;
	}

	//returns the expiry date
	const Date& Perishable::expiry() const {
		
		return expDate;
	}
}