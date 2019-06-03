#include <iostream>
#include <string>
#include "Utilities.h"

namespace sict
{
	
	char Utilities::delimiter = '\0';
	size_t Utilities::fieldWidth = 0;

	//default constructor for safe empty state
	Utilities::Utilities() {}

	const std::string Utilities::extractToken(const std::string & str, size_t & next_pos)
	{
		std::string token;
		size_t word_length = 0;
		size_t starting_pos = 0;
		size_t next_delimiter_pos = str.find(delimiter, next_pos + 1);	// find the next delimiter from 1 character after the previous one
		if (next_pos == 0)
		{
			word_length = next_delimiter_pos;
			starting_pos = next_pos;
		}
		else
		{
			word_length = (next_delimiter_pos - next_pos) - 1;			// get the length of the next word
			starting_pos = next_pos + 1;
		}
		token = str.substr(starting_pos, word_length);						// extract the string that starts from next_pos with the length of the next word
		next_pos = next_delimiter_pos;											// sets the next_pos to contain the position of the upcoming delimiter
		return token;
	}

	/*
	//extracts next token in string starting at next_pos and ending before delimiter character 
	const std::string Utilities::extractToken(const std::string& str, size_t& next_pos) {

		//MS2: UPDATED FUNCTION DUE TO ISSUES ASSIGNING EXTRACTED TOKENS

		size_t nextDelimiter = str.find(delimiter, next_pos + 1);
		// gets the length of the next token
		size_t tokenLen = (nextDelimiter - next_pos) - 1;
		// extracts string
		std::string token = str.substr(next_pos + 1, tokenLen);
		// sets the next_pos to next position of delimiter
		next_pos = nextDelimiter;
	
		//throws exception if no token
		if (token.empty()) {

			throw("Error: No token between delimiters!");
		}

		//compares size of extrated token with fieldWidth and if token is greater, increases width
		if (fieldWidth < token.size()) {

			fieldWidth = token.size();
		}

		return token;
	}*/

	//returns delimiter character
	const char Utilities::getDelimiter() const {

		return delimiter;
	}

	//returns fieldWidth for current object
	size_t Utilities::getFieldWidth() const {

		return fieldWidth;
	}


	//modifier that sets the delimiter character for all objects of this class
	void Utilities::setDelimiter(const char d) {

		delimiter = d;
	}

	//sets the fieldWith for the current object
	void Utilities::setFieldWidth(size_t fw) {

		fieldWidth = fw;
	}
}