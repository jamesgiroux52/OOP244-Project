/*
 ============================================================================
 Name        : Error.cpp
 Author      : James Giroux - jgiroux1@myseneca.ca
 Student #   : 129198164
 Section     : SEE
 Date        : July 25, 2019
 ============================================================================
 */

/*
 ============================================================================
 Description : Error module file
 ============================================================================
 */

#include <iostream>
#include <cstring>
#include "Error.h"

using namespace std;

namespace aid {

	// Constructor
	Error::Error(const char * errorMessage) {
		if (errorMessage != nullptr) {
			m_message = nullptr;
			message(errorMessage);
		} else {
			m_message = nullptr;
		}
	}

	// destructor
	Error::~Error() {
		delete[] m_message;
	}

	void Error::clear() {
		delete[] m_message;
		m_message = nullptr;
	}

	// check for message
	bool Error::isClear() const {
		return (m_message == nullptr || m_message[0] == '\0') ? true : false;
	}

	// set message
	void Error::message(const char * str) {
		clear();

		if (str != nullptr) {
			m_message = new char[strlen(str) + 1];
			strcpy(m_message, str);
		} else {
			m_message = nullptr;
		}
	}

	// return message
	const char* Error::message() const {
		if (m_message != nullptr) {
			return m_message;
		} else {
			return nullptr;
		}
	}

	// << overload
	std::ostream & operator<<(std::ostream & ostr, Error& rhs) {
		if (rhs.m_message != nullptr) {
			ostr << rhs.message();
		}

		return ostr;
	}
}
