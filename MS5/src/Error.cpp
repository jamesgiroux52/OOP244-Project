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

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Error.h"

using namespace std;

namespace aid {

	// Constructor
	Error::Error(const char* errorMsg) {
		if (errorMsg != nullptr) {
			m_message = nullptr;
			message(errorMsg);
		} else {
			m_message = nullptr;
		}
	}

	// destructor
	Error::~Error() {
		delete[] m_message;
		m_message = nullptr;
	}

	// deallocate memory for error message
	void Error::clear() {
		if (m_message != nullptr) {
			delete[] m_message;
			m_message = nullptr;
		}
	}

	// check for message
	bool Error::isClear() const {
		return (m_message == nullptr || m_message[0] == '\0') ? true : false;
	}

	// set message
	void Error::message(const char* str) {
		clear();

		if (str != nullptr) {
			m_message = new char[strlen(str) + 1];
			strncpy(m_message, str, strlen(str) + 1);
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
	std::ostream& operator<<(std::ostream& ostr, Error& rhs) {
		if (rhs.m_message != nullptr) {
			ostr << rhs.message();
		}

		return ostr;
	}
}
