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

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

#include "Perishable.h"

using namespace std;

namespace aid {

	Perishable::Perishable() : Good('P') {
		m_expDate = Date();
	}

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

	std::fstream& Perishable::load(std::fstream& file) {
		Good::load(file);
		m_expDate.read(file);
		file.ignore();
		return file;
	}

	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		Good::write(os, linear);
		if (isClear() && !isEmpty()) {
			if (linear) {
				m_expDate.write(os);

			} else {
				os << '\n' << " Expiry date: ";
				m_expDate.write(os);
			}
		}
		return os;
	}

	std::istream& Perishable::read(std::istream& is) {
		Date tmp;
		Good::read(is);
		if (isClear()) {
			std::cout << " Expiry date (YYYY/MM/DD): ";
			std::cin >> tmp;
		}
		if (isClear() && tmp.bad()) {
			switch (tmp.errCode()) {
			case CIN_FAILED:
				message("Invalid Date Entry");
				break;
			case YEAR_ERROR:
				message("Invalid Year in Date Entry");
				break;
			case MON_ERROR:
				message("Invalid Month in Date Entry");
				break;
			case DAY_ERROR:
				message("Invalid Day in Date Entry");
				break;
			case PAST_ERROR:
				message("Invalid Expiry in Date Entry");
				break;
			}
			is.setstate(std::ios::failbit);
		}
		if (!is.fail()) {
			m_expDate = tmp;
		}

		return is;

	}

	const Date & Perishable::expiry() const {
		return m_expDate;
	}

	iGood* CreateProduct(char tag) {

		if (tag == 'N' || tag == 'n'){
			return new Good();
		} else if (tag == 'P' || tag == 'p') {
			return new Perishable();
		}

		return nullptr;
	}
}
