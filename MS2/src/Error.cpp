/*
 ============================================================================
 Name        : Error.cpp
 Author      : James Giroux - jgiroux1@myseneca.ca
 Student #   : 129198164
 Section     : SEE
 Date        : July 15, 2019
 ============================================================================
 */

/*
 ============================================================================
 Description : Error module
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

	// clear error
	void Error::clear() {
		delete[] m_message;
		m_message = nullptr;
	}

	// check if clear
	bool Error::isClear() const {
		return (m_message == nullptr || m_message[0] == '\0') ? true : false;
	}


	void Error::message(const char* str) {
		clear();
		if (str != nullptr) {
			int length = strlen(str) + 1;

			m_message = new char[length];
			strncpy(m_message, str, length);
		} else {
			m_message = nullptr;
		}
	}

	// returns error message or nullptr
	const char* Error::message() const {
		if (m_message != nullptr) {
			return m_message;
		} else {
			return nullptr;
		}
	}

	// send the error code to output stream
	std::ostream& operator<<(std::ostream& ostr, Error& rhs) {
		if (rhs.m_message != nullptr) {
			ostr << rhs.message();
		}

		return ostr;
	}

}
