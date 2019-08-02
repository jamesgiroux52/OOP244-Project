/*
 ============================================================================
 Name        : ms3_MyGood.h
 Author      : James Giroux - jgiroux1@myseneca.ca
 Student #   : 129198164
 Section     : SEE
 Date        : July 25, 2019
 ============================================================================
 */

/*
 ============================================================================
 Description : MyGood header file
 ============================================================================
 */
#ifndef AID_MS3_MYGOOD_H_
#define AID_MS3_MYGOOD_H_

#include <fstream>
#include "Good.h"

namespace aid {
	class MyGood : public Good {
	public:
		MyGood();
		MyGood(const char* sku, const char* name, const char* unit, int qty = 0,
			bool isTaxed = true, double price = 0.0, int qtyNeeded = 0);
		const char* sku() const;
		const char* name() const;
		const char* unit() const;
		bool taxed() const;
		double price() const;
		double cost() const;
	};

	class Test {
		MyGood product;
		const char* filename;
	public:
		Test(const char* file);
		Test(const char* file, const char* theSku, const char* theName);
		std::fstream& store(std::fstream& file, bool addNewLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		int operator+=(int value);
		bool operator==(const char* sku) const;
		friend std::ostream& operator<<(std::ostream& os, const Test& test);
		friend double operator+=(double& d, const Test& test);
		friend std::istream& operator>>(std::istream& is, Test& test);
	};
}

#endif /* MS3_MYGOOD_H_ */
