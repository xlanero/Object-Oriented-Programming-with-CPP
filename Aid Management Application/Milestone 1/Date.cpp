// Final Project Milestone 1
//
// Version 1.0
// Date Nov 20, 2018
// Author LISA NIRO 108760182
// Description: DATE.CPP implementation file
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#include <iostream>
#include "Date.h"
using namespace std;

namespace aid
{

	// number of days in month mon and year year
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}
	void Date::errCode(int errorCode) {
		error = errorCode;
	}

	Date::Date() {
		//sets to a safe empty state
		year = 0000;
		month = 00;
		day = 00;
		fullDate = 0;
		error = NO_ERROR;

	}

	Date::Date(int yr, int mth, int dy) {
		//checks for validation
		if ((yr >= min_year && yr <= max_year) && (mth >= 1 && mth <= 12) && (dy <= mdays(mth, yr))) {

			//comparator
			fullDate = yr * 372 + mth * 31 + dy;

			//if everything is valid, copies data
			if (fullDate >= min_date) {
				year = yr;
				month = mth;
				day = dy;
				errCode(NO_ERROR);
			}

		}
		else {
			//sets to safe empty state
			*this = Date();

			//checks for validation errors
			if (yr < min_year || yr > max_year) {

				error = YEAR_ERROR;
			}

			else if (mth < 1 || mth > 12) {

				error = MON_ERROR;
			}

			else if (dy < 1 || dy > mdays(mth, yr)) {

				error = DAY_ERROR;
			}

			else if (fullDate < min_date) {

				error = PAST_ERROR;
			}
			

		}

	}		

	bool Date::operator==(const Date& rhs) const {
		return(this->fullDate == rhs.fullDate);
	}

	bool Date::operator!=(const Date& rhs) const {
		return(this->fullDate != rhs.fullDate);
	}

	bool Date::operator<(const Date& rhs) const {
		return(this->fullDate < rhs.fullDate);
	}

	bool Date::operator>(const Date& rhs) const {
		return(this->fullDate > rhs.fullDate);
	}

	bool Date::operator<=(const Date& rhs) const {
		return(this->fullDate <= rhs.fullDate);
	}

	bool Date::operator>=(const Date& rhs) const {
		return(this->fullDate >= rhs.fullDate);
	}

	int Date::errCode() const {
		return error;
	}

	bool Date::bad() const {
		return(error != NO_ERROR);
	}

	istream& Date::read(istream& istr) {
		int _year = 0, _month = 0, _day = 0;
		char delimiter;

		//receives input in a date format
		istr >> _year >> delimiter >> _month >> delimiter >> _day;
		fullDate = _year * 372 + _month * 31 + _day;

		if (istr.fail()) {
			error = CIN_FAILED;
		}

		else if (min_year > _year || _year > max_year) {
			errCode(YEAR_ERROR);
		}

		else if (_month < 1 ||_month > 12) {
			errCode(MON_ERROR);
		}

		else if (_day > mdays(_month, _year)) {
			errCode(DAY_ERROR);
		}
		else if (fullDate < min_date) {
			errCode(PAST_ERROR);
		}
		else {
			year = _year;
			month = _month;
			day = _day;
		}


		return istr;

	}
	

	ostream& Date::write(ostream& ostr) const {
		//prints to screen, checks if month / day is less than 10 and supplements 0 if necessary
		ostr << year << "/";

		if (month < 10) {

			ostr << "0" << month << "/";
		}

		else {
			ostr << month << "/";
		}

		if (day < 10) {
			ostr << "0" << day;
		}

		else {
			ostr << day;
		}

		return ostr;

	}

	//Helper functions
	istream& operator>> (istream& ist, Date& D) {

		return D.read(ist);

	}
	ostream& operator<< (ostream& ost, Date& D) {

		return D.write(ost);

	}

}


