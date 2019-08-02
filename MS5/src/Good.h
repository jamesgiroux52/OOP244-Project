/*
 ============================================================================
 Name        : Good.h
 Author      : James Giroux - jgiroux1@myseneca.ca
 Student #   : 129198164
 Section     : SEE
 Date        : July 31, 2019
 ============================================================================
 */

/*
 ============================================================================
 Description : Good header file
 ============================================================================
 */


#ifndef AID_GOOD_H_
#define AID_GOOD_H_

#include <fstream>
#include "Error.h"
#include "iGood.h"

namespace aid {
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class Good : public iGood{
		// private data members
		char m_typeOfGood;
		char m_sku[max_sku_length + 1];
		char m_unit[max_unit_length + 1];
		char* m_name;
		int m_quantityOnHand;
		int m_quantityNeeded;
		double m_price;
		bool m_taxable;
		Error m_error;
	protected:
		// Protected member functions:
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char*);
		bool isClear() const;

	public:
		// Public member functions:

		// Constructors
		Good(const char type = 'N');
		Good(const char* sku, const char* name, const char* unit, int qty = 0, bool taxed = true, double price = 0, int qtyNeeded = 0);
		// copy constructor
		Good(Good&);
		// copy assignment operator
		Good& operator=(const Good&);
		// destructor
		~Good();

		// file logic
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);

		// Operator overloads and logic
		bool operator==(const char*) const;
		double total_cost() const;
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		void quantity(int);
		bool operator>(const char*) const;
		bool operator>(const iGood&) const;
		int operator+=(int);

	};

	// Helper functions:
	std::ostream& operator<<(std::ostream&, const iGood&);
	std::istream& operator>>(std::istream&, iGood&);
	double operator+=(double&, const iGood&);
}

#endif /* AID_GOOD_H_ */
