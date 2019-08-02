/*
 ============================================================================
 Name        : ms4_MyGood.h
 Author      : James Giroux - jgiroux1@myseneca.ca
 Student #   : 129198164
 Section     : SEE
 Date        : July 27, 2019
 ============================================================================
 */

/*
 ============================================================================
 Description : MyGood header file
 ============================================================================
 */


#ifndef AID_MYPRODUCT_H__
#define AID_MYPRODUCT_H__
#include "iGood.h"
#include "iGood.h"
#include "iGood.h" // Good.h is included three times on purpose.

namespace aid {
  class MyGood : public iGood {
    char text_[10000];
	char sku[4];
	char name_[20];
	int value;
  public:
    MyGood(const char* name);
    std::fstream& store(std::fstream& file, bool addNewLine)const;
    std::fstream& load(std::fstream& file);
    std::ostream& write(std::ostream& os, bool linear)const;
    std::istream& read(std::istream& is);
	bool operator==(const char*) const;
	double total_cost() const;
	const char* name() const;
	void quantity(int);
	int qtyNeeded() const;
	int quantity() const;
	int operator+=(int);
	bool operator>(const iGood&) const;
  };
}

#endif /* MS4_MYGOOD_H_ */
