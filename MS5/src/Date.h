/*
 ============================================================================
 Name        : Date.h
 Author      : James Giroux - jgiroux1@myseneca.ca
 Student #   : 129198164
 Section     : SEE
 Date        : July 5, 2019
 ============================================================================
 */

/*
 ============================================================================
 Description : Date header
 ============================================================================
 */

#ifndef AID_DATE_H_
#define AID_DATE_H_

#include <iostream>

namespace aid {

	const int min_year = 2018;
	const int max_year = 2038;
	const int min_date = 751098;
	const int NO_ERROR = 0; //  No error - the date is valid
	const int CIN_FAILED = 1; // --istream failed on information entry
	const int DAY_ERROR = 2; // --Day value is invalid
	const int MON_ERROR = 3;  //--Month value is invalid
	const int YEAR_ERROR = 4;  //--Year value is invalid
	const int PAST_ERROR = 5;  //--Date value is invalid

	// Date class
	class Date {
		// members
		int m_year;
		int m_month;
		int m_day;
		int m_error;
		// private functions
		int mdays(int year, int month) const;
		void errCode(int err);
		int compare() const;
	public:
		// constructors
		Date();
		Date(int year, int month, int day);
		// relational operators
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		// queries and modifiers
		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};

	// free helpers
	std::ostream& operator<<(std::ostream& ostr, Date&);
	std::istream& operator>>(std::istream& istr, Date&);
}

#endif /* DATE_H_ */
