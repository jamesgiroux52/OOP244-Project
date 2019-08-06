/*
 ============================================================================
 Name        : Date.cpp
 Author      : James Giroux - jgiroux1@myseneca.ca
 Student #   : 129198164
 Section     : SEE
 Date        : July 5, 2019
 ============================================================================
 */

/*
 ============================================================================
 Description : Date Module
 ============================================================================
 */

#include "Date.h"

namespace aid {

	// number of days in month
	int Date::mdays(int mon, int year) const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month]
				+ int(
						(month == 1) * ((year % 4 == 0) && (year % 100 != 0))
								|| (year % 400 == 0));
	}

	// sets error code
	void Date::errCode(int err) {
		m_error = err;
	}

	// compare date
	int Date::compare() const {
		return m_year * 372 + m_month * 31 + m_day;
	}

	// default constructor
	Date::Date() {
		m_year = 0;
		m_month = 0;
		m_day = 0;
		m_error = NO_ERROR;
	}

	// three argument constructor
	Date::Date(int year, int month, int day) {

		*this = Date();

		if (year >= min_year && year <= max_year) {
			if (month >= 1 && month <= 12) {
				if (day >= 1 && day <= mdays(month, year)) {
					m_year = year;
					m_month = month;
					m_day = day;
					m_error = NO_ERROR;
					compare();
				} else {
					errCode(DAY_ERROR);
				}
			} else {
				errCode(MON_ERROR);
			}
		} else {
			errCode(YEAR_ERROR);
		}
	}

	// comparison operators
	bool Date::operator==(const Date& rhs) const {
		return compare() == rhs.compare() ? true : false;
	}

	bool Date::operator!=(const Date& rhs) const {
		return compare() != rhs.compare() ? true : false;
	}

	bool Date::operator<(const Date& rhs) const {
		return compare() < rhs.compare() ? true : false;
	}

	bool Date::operator>(const Date& rhs) const {
		return compare() > rhs.compare() ? true : false;
	}

	bool Date::operator<=(const Date& rhs) const {
		return compare() <= rhs.compare() ? true : false;
	}

	bool Date::operator>=(const Date& rhs) const {
		return compare() >= rhs.compare() ? true : false;
	}

	// returns error code as integer
	int Date::errCode() const {
		return m_error;
	}

	// returns true if there is an error
	bool Date::bad() const {
		return m_error != NO_ERROR ? true : false;
	}

	// read function
	std::istream& Date::read(std::istream& istr) {

		char symbol;

		istr.clear();
		istr >> m_year >> symbol >> m_month >> symbol >> m_day;

		if (istr.fail()) {
			*this = Date();
			errCode(CIN_FAILED);
		} else if (min_year > m_year || m_year > max_year) {
			*this = Date();
			errCode(YEAR_ERROR);
		} else if (1 > m_month || m_month > 12) {
			*this = Date();
			errCode(MON_ERROR);
		} else if (m_day > mdays(m_month, m_year)) {
			*this = Date();
			errCode(DAY_ERROR);
		} else if (compare() < min_date) {
			*this = Date();
			errCode(PAST_ERROR);
		}

		return istr;
	}

	// write function
	std::ostream& Date::write(std::ostream& ostr) const {

		ostr << m_year << "/";
		if (m_month >= 10) {
			ostr << m_month;
		} else {
			ostr << '0' << m_month;
		}

		ostr << "/";
		if (m_day >= 10) {
			ostr << m_day;
		} else {
			ostr << '0' << m_day;
		}

		return ostr;
	}

	// helper input and output functions
	std::ostream& operator<<(std::ostream& ostr, Date& obj) {
		obj.write(ostr);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, Date& obj) {
		obj.read(istr);
		return istr;
	}
}
