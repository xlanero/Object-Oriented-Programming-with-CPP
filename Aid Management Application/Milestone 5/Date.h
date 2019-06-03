// Final Project Milestone 1
//
// Version 1.0
// Date Nov 20, 2018
// Author LISA NIRO 108760182
// Description: DATE.CPP header file
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#ifndef AMA_DATE_H
#define AMA_DATE_H

#define NO_ERROR 0

#define CIN_FAILED 1
#define DAY_ERROR 2
#define MON_ERROR 3
#define YEAR_ERROR 4
#define PAST_ERROR 5
const int min_year = 2018;
const int max_year = 2038;
const int min_date = 751098;

namespace aid
{

	class Date {
		int year;
		int month;
		int day;
		int mdays(int, int)const;
		//comparator value
		int fullDate;
		int error;
		void errCode(int errorCode);

	public:

		Date();
		Date(int, int, int);
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;

	};

	//helper functions
	std::ostream& operator<<(std::ostream& ostr, const Date&);
	std::istream& operator>>(std::istream& istr, Date&);


}
#endif
