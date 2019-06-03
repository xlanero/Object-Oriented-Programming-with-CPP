// Final Project Milestone 5
//
// Version 1.0
// Date 
// Author LISA NIRO 108760182
// Description: Perishable.h header file
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#ifndef AID_PERISHABLE_H
#define AID_PERISHABLE_H

#include "Date.h"
#include "Good.h"


namespace aid
{
	class Perishable : public Good {

		Date expDate;

	public:
		
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};
	
}
#endif