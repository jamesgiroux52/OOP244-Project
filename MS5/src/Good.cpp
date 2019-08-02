/*
 ============================================================================
 Name        : Good.cpp
 Author      : James Giroux - jgiroux1@myseneca.ca
 Student #   : 129198164
 Section     : SEE
 Date        : July 31, 2019
 ============================================================================
 */

/*
 ============================================================================
 Description : Good module file
 ============================================================================
 */

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "Good.h"

using namespace std;

namespace aid {

	void Good::name(const char* name) {
		if (name != nullptr) {
			int length = strlen(name);
			m_name = new char[length + 1];
			strncpy(m_name, name, length);
			m_name[length] = '\0';
		} else {
			m_name = nullptr;
		}
	}

	// return name
	const char* Good::name() const{
		return m_name;
	}

	// return sku
	const char* Good::sku() const {
		return m_sku;
	}

	// return unit
	const char* Good::unit() const {
		return m_unit;
	}

	// return taxable
	bool Good::taxed() const {
		return m_taxable;
	}

	// return price
	double Good::itemPrice() const {
		return m_price;
	}

	// return price + taxed
	double Good::itemCost() const {
		return m_taxable ? m_price * (1.0 + tax_rate) : m_price;
	}

	void Good::message(const char * msg) {
		m_error.message(msg);
	}

	bool Good::isClear() const {
		return m_error.isClear();
	}

	// Constructor
	Good::Good(const char type) {
		m_typeOfGood = type;
		m_sku[0] = '\0';
		m_unit[0] = '\0';
		m_name = nullptr;
		m_quantityOnHand = 0;
		m_quantityNeeded = 0;
		m_price = 0;
		m_taxable = false;
		m_error.message();
	}

	// Seven argument Constructor
	Good::Good(const char* sku, const char* pname,
			const char* unit, int qty, bool taxed, double price, int qtyNeeded) {
		if (sku != nullptr && pname != nullptr && unit != nullptr) {
			strncpy(m_sku, sku, max_sku_length);
			m_sku[max_sku_length] = '\0';
			name(pname);
			strncpy(m_unit, unit, max_unit_length);
			m_unit[max_unit_length] = '\0';
		}
		m_quantityOnHand = qty;
		m_taxable = taxed;
		m_price = price;
		m_quantityNeeded = qtyNeeded;
	}

	// Copy Constructor
	Good::Good(Good& obj) {
		m_name = nullptr;
		*this = obj;
	}

	// Destructor
	Good::~Good() {
		delete[] m_name;
		m_name = nullptr;
	}

	// Copy Assignment Operator
	Good& Good::operator=(const Good& obj) {
		if (this != &obj) {
			strcpy(m_sku, obj.m_sku);
			strcpy(m_unit, obj.m_unit);
			name(obj.m_name);
			m_quantityOnHand = obj.m_quantityOnHand;
			m_taxable = obj.m_taxable;
			m_price = obj.m_price;
			m_quantityNeeded = obj.m_quantityNeeded;
		}

		return *this;
	}

	bool Good::operator==(const char* sku) const {
		return (strcmp(m_sku, sku) == 0);
	}

	bool Good::operator>(const char* sku) const {
		return strcmp(m_sku, sku) > 0;
	}

	bool Good::operator>(const iGood& obj) const {
		return strcmp(m_name, obj.name()) > 0;
	}

	int Good::operator+=(int add) {
		return (m_quantityOnHand += (add > 0 ? add : 0));
	}

	double Good::total_cost() const {
		return itemCost() * m_quantityOnHand;
	}

	void Good::quantity(int no) {
		m_quantityOnHand = no;
	}

	bool Good::isEmpty() const {
		return m_name == nullptr && m_sku[0] == '\0' && m_unit[0] == '\0' &&
				m_quantityOnHand == 0 && m_price == 0 && m_taxable == false;
	}

	int Good::qtyNeeded() const {
		return m_quantityNeeded;
	}

	int Good::quantity() const {
		return m_quantityOnHand;
	}

	std::fstream& Good::store(std::fstream& file, bool newLine) const {
		file << m_typeOfGood << "," << m_sku << ',' << m_name << ',' << m_unit
			<< ',' << m_taxable << ',' << m_price << ',' << quantity() << ',' << qtyNeeded();

		if (newLine) {
			file << endl;
		}

		return file;
	}

	std::fstream& Good::load(std::fstream& file) {
		char tmpSku[max_sku_length + 1];
		char tmpUnit[max_unit_length + 1];
		char tmpName[max_name_length + 1];
		int tmpQty;
		int tmpQtyNeeded;
		double tmpPrice;
		char tax;

		file.getline(tmpSku, 1999, '\t');
		file.getline(tmpName, 1999, '\t');
		file.getline(tmpUnit, 1999, '\t');

		file >> tax;
		file.ignore();
		file >> tmpPrice;
		file.ignore();
		file >> tmpQty;
		file.ignore();
		file >> tmpQtyNeeded;
		file.ignore();

		*this = Good(tmpSku, tmpName, tmpUnit, tmpQty, tax != '0', tmpPrice, tmpQtyNeeded);

		return file;
	}

	std::ostream& Good::write(std::ostream& os, bool linear) const {
		if (!m_error.isClear()) {
			os << m_error.message();
		} else if (!isEmpty()) {
			char N[75];
			int qt = m_quantityOnHand;

			if (linear) {
				strncpy(N, m_name, 20);
				N[20] = 0;
				os << std::setw(max_sku_length) << std::left << m_sku << "|" << std::setw(20) << std::left << N << "|"
					<< std::setw(7) << std::fixed << std::setprecision(2) << std::right << itemCost() << "|" << std::setw(4) << std::right << qt << "|" << std::setw(10) << std::left << m_unit << "|" << std::setw(4) << std::right << m_quantityNeeded << "|";
			} else {
				strncpy(N, m_name, 74);
				N[74] = 0;
				os << " Sku: " << m_sku << std::endl
					<< " Name (no spaces): " << N << std::endl
					<< " Price: " << m_price << std::endl
					<< " Price after tax: ";
				if (m_taxable) {
					os << itemCost() << std::endl;
				} else {
					os << " N/A" << std::endl;
				}
				os << " Quantity on Hand: " << qt << " " << m_unit << std::endl
					<< " Quantity needed: " << m_quantityNeeded;
			}
		}

		return os;
	}

	std::istream& Good::read(std::istream& is) {
		char tmpSku[max_sku_length + 1];
		char tmpUnit[max_unit_length + 1];
		char tmpName[max_name_length + 1];
		int tmpQty;
		int tmpQtyNeeded;
		double tmpPrice;
		char tax;

		if (!is.fail()) m_error.clear();

		std::cout << " Sku: ";
		is.getline(tmpSku, max_sku_length, '\n');
		std::cout << " Name (no spaces): ";
		is.getline(tmpName, 74, '\n');
		std::cout << " Unit: ";
		is.getline(tmpUnit, 10, '\n');
		std::cout << " Taxed? (y/n): ";
		is >> tax;

		if (tax == 'y' || tax == 'Y' || tax == 'n' || tax == 'N') {
			std::cin.ignore(1000, '\n');
			std::cout << " Price: ";
			is >> tmpPrice;
		} else {
			is.setstate(std::ios::failbit);
			m_error.message("Only (Y)es or (N)o are acceptable");
		}

		if (m_error.isClear() && is.fail()) {
			m_error.message("Invalid Price Entry");
		}

		if (m_error.isClear()) {
			std::cout << " Quantity on hand: ";
			std::cin >> tmpQty;
		}

		if (m_error.isClear() && is.fail()) {
			m_error.message("Invalid Quantity Entry");
		}

		if (m_error.isClear()) {
			std::cout << " Quantity needed: ";
			std::cin >> tmpQtyNeeded;
			std::cin.ignore();
		}

		if (m_error.isClear() && is.fail()) {
			m_error.message("Invalid Quantity Needed Entry");
		}

		if (!is.fail())
			*this = Good(tmpSku, tmpName, tmpUnit, tmpQty, tax == 'y' || tax == 'Y', tmpPrice, tmpQtyNeeded);

		return is;
	}


	// helper functions
	std::ostream& operator<<(std::ostream& os, const iGood & obj) {
		return obj.write(os, true);
	}

	std::istream& operator>>(std::istream& is, iGood& obj) {
		return obj.read(is);
	}

	double operator+=(double& add, const iGood& obj) {
		return obj.total_cost() + add;
	}
}






