/*
 ============================================================================
 Name        : Perishable.cpp
 Author      : James Giroux - jgiroux1@myseneca.ca
 Student #   : 129198164
 Section     : SEE
 Date        : July 31, 2019
 ============================================================================
 */

/*
 ============================================================================
 Description : Perishable module
 ============================================================================
 */

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Perishable.h"

using namespace std;

namespace aid {

	// create a perishable good
	Perishable::Perishable() :
			Good('P') {
	}

	// store the expiry date in the file
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
		Good::store(file, false);
		Date tmpDate;
		tmpDate = m_expDate;

		if (newLine == false) {
			file << "," << tmpDate;
		} else {
			file << "," << tmpDate << endl;
		}

		return file;
	}

	// load the expiry date from the file
	std::fstream& Perishable::load(std::fstream& file) {
		Good::load(file);
		file.ignore();
		m_expDate.read(file);
		file.ignore();
		return file;
	}

	// display the expiry date
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		if (m_error.message() != nullptr)
			os << m_error.message();

		if (!isEmpty() && isClear()) {
			Good::write(os, linear);
			if (!linear) {
				os << endl << " Expiry date: ";
				m_expDate.write(os);
			} else {
				m_expDate.write(os);
			}
		}

		return os;

	}

	// gets the expiry date from user
	std::istream& Perishable::read(std::istream& is) {
		Good::read(is);

		if (!is.fail()) {
			std::cout << " Expiry date (YYYY/MM/DD): ";
			Date temporary;
			temporary.read(is);

			if (temporary.errCode()) {
				is.setstate(std::ios::failbit);
				switch (temporary.errCode()) {
				case CIN_FAILED:
					m_error.message("Invalid Date Entry");
					break;
				case DAY_ERROR:
					m_error.message("Invalid Day in Date Entry");
					break;
				case MON_ERROR:
					m_error.message("Invalid Month in Date Entry");
					break;
				case YEAR_ERROR:
					m_error.message("Invalid Year in Date Entry");
					break;
				case PAST_ERROR:
					m_error.message("Invalid Expiry in Date Entry");
					break;
				}
			} else {
				m_expDate = temporary;
			}
		}
		return is;

	}

	// return the expiry date
	const Date& Perishable::expiry() const {
		return m_expDate;
	}

	// create a product of correct type
	iGood* CreateProduct(char tag) {
		iGood* obj = nullptr;

		if (tag == 'N' || tag == 'n') {
			obj = new Good();
		} else if (tag == 'P' || tag == 'p') {
			obj = new Perishable();
		}

		return obj;
	}
}
