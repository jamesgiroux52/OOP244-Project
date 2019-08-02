/*
 ============================================================================
 Name        : Good.h
 Author      : James Giroux - jgiroux1@myseneca.ca
 Student #   : 129198164
 Section     : SEE
 Date        : July 25, 2019
 ============================================================================
 */

/*
 ============================================================================
 Description : Good header file
 ============================================================================
 */


#ifndef AID_GOOD_H
#define	AID_GOOD_H


#include "Error.h"

namespace aid {
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class Good {
		// private data member
		char m_TypeGood;
		char m_Sku[max_sku_length + 1];
		char m_Unit[max_unit_length];
		char* m_Name; // contain the name of good
		int m_QuantityHand;
		int m_QuantityNeeded;
		double m_Price;
		bool m_Taxable;
		Error m_Error;
		// Protected member functions:
	protected:
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char*);
		bool isClear() const;

		// Public member functions:
	public:
		// Constructors
		Good(const char type = 'N');
		Good(const char* sku, const char* name, const char* unit, int qty = 0, bool taxed = true, double price = 0, int qtyNeeded = 0);
		Good(Good&);
		~Good();

		// Operator overloads
		Good& operator=(const Good&);
		bool operator==(const char*) const;
		bool operator>(const char*) const;
		bool operator>(const Good&) const;
		int operator+=(int);


		// logic
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;

		// file logic
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);

	};

	// Helper functions:
	std::ostream& operator<<(std::ostream&, const Good&);
	std::istream& operator>>(std::istream&, Good&);
	double operator+=(double&, const Good&);

}

#endif // AID_GOOD_H
