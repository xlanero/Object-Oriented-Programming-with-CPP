// Final Project Milestone 2
//
// Version 1.0
// Date Nov 24, 2018
// Author LISA NIRO 108760182
// Description: Error.cpp implementation file
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////


#include <iostream>
#include <cstring>
#include "Error.h"
using namespace std;

namespace aid
{
	Error::Error(const char* errorMessage)
	{
		if (errorMessage == nullptr)
		{
			ptrMessage = nullptr;
		}

		else
		{
			ptrMessage = new char[strlen(errorMessage) + 1];
			strncpy(ptrMessage, errorMessage, (strlen(errorMessage) + 1));
			ptrMessage[strlen(errorMessage) + 1] = '\0';
		}
	}

	//deallocates dynamic memory allocated by current object
	Error::~Error()
	{
		delete[] ptrMessage;
		ptrMessage = nullptr;
	}

	//clears message stored by current object
	void Error::clear()
	{
		delete[] this->ptrMessage;
		ptrMessage = nullptr;
	}

	//checks for safe empty state
	bool Error::isClear() const
	{
		if (ptrMessage == nullptr || ptrMessage[0] == '\0') {
			return true;
		}
		else {
			return false;
		}
	}

	void Error::message(const char* str)
	{
		delete[] ptrMessage;
		if (str != nullptr) {
			ptrMessage = new char[strlen(str) + 1];
			strcpy(ptrMessage, str);
		}
		else {
			ptrMessage = nullptr;
		}


	}

	const char* Error::message() const
	{
		if (ptrMessage != nullptr && ptrMessage[0] != '\0') {
			return ptrMessage;
		}
		else {
			return nullptr;
		}
	}

	std::ostream& operator<<(std::ostream& os, const Error& err)
	{
		if (!err.isClear()) {
			os << err.message();
		}
		return os;
	}
}
