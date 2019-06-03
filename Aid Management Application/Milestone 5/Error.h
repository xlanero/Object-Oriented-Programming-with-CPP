// Final Project Milestone 2
//
// Version 1.0
// Date Nov 24, 2018
// Author LISA NIRO 108760182
// Description: Error.cpp header file
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#ifndef AID_ERROR_H
#define AID_ERROR_H

#include <iostream>
#include <cstring>

using namespace std;

namespace aid
{
	class Error
	{
		char* ptrMessage;

	public:

		explicit Error(const char* errorMessage = nullptr);
		Error(const Error& em) = delete;
		Error& operator=(const Error& em) = delete;
		virtual ~Error();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
	};
	std::ostream& operator<<(std::ostream& os, const Error& err);
}

#endif


