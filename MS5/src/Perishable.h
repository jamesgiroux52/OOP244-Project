/*
 ============================================================================
 Name        : Perishable.h
 Author      : James Giroux - jgiroux1@myseneca.ca
 Student #   : 129198164
 Section     : SEE
 Date        : July 31, 2019
 ============================================================================
 */

/*
 ============================================================================
 Description : Perishable header file
 ============================================================================
 */

#ifndef AID_PERISHABLE_H_
#define AID_PERISHABLE_H_

#include "Date.h"
#include "Good.h"

namespace aid {

	class Perishable : public Good {
		Date m_expDate;
	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};

	//iGood* CreateProduct(char tag);
}

#endif /* AID_PERISHABLE_H_ */
