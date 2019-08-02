/*
 ============================================================================
 Name        : Good.cpp
 Author      : James Giroux - jgiroux1@myseneca.ca
 Student #   : 129198164
 Section     : SEE
 Date        : July 25, 2019
 ============================================================================
 */

/*
 ============================================================================
 Description : Good module
 ============================================================================
 */

#define _CRT_SECURE_NO_WARNINGS
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
			m_Name = new char[length + 1];
			strcpy(m_Name, name);
			m_Name[length] = '\0';
		} else {
			m_Name = nullptr;
		}
	}

	// return name
	const char * Good::name() const{
		return m_Name;
	}

	// return sku
	const char * Good::sku() const {
		return m_Sku;
	}

	// return unit
	const char * Good::unit() const {
		return m_Unit;
	}

	// return taxable
	bool Good::taxed() const {
		return m_Taxable;
	}

	// return price
	double Good::itemPrice() const {
		return m_Price;
	}

	// return price + taxed
	double Good::itemCost() const {
		return m_Taxable ? m_Price * (1.0 + tax_rate) : m_Price;
	}

	void Good::message(const char * msg) {
		m_Error.message(msg);
	}

	bool Good::isClear() const {
		return m_Error.isClear();
	}

	// Constructor
	Good::Good(const char type) {
		m_TypeGood = type;
		m_Sku[0] = '\0';
		m_Unit[0] = '\0';
		m_Name = nullptr;
		m_QuantityHand = 0;
		m_QuantityNeeded = 0;
		m_Price = 0;
		m_Taxable = false;
		m_Error.message();
	}

	// Seven argument Constructor
	Good::Good(const char* sku, const char* pname,
			const char* unit, int qty, bool taxed, double price, int qtyNeeded) {
		strncpy(m_Sku, sku, max_sku_length);
		m_Sku[max_sku_length] = '\0';
		name(pname);
		strncpy(m_Unit, unit, max_unit_length);
		m_Unit[max_unit_length] = '\0';
		m_QuantityHand = qty;
		m_Taxable = taxed;
		m_Price = price;
		m_QuantityNeeded = qtyNeeded;
	}

	// Copy Constructor
	Good::Good(Good& obj) {
		m_Name = nullptr;
		*this = obj;
	}

	// Distructor
	Good::~Good() {
		delete[] m_Name;
		m_Name = nullptr;
	}

	// Copy Assignment Operator
	Good & Good::operator=(const Good& obj) {
		if (this != &obj) {
			strcpy(m_Sku, obj.m_Sku);
			strcpy(m_Unit, obj.m_Unit);
			name(obj.m_Name);
			m_QuantityHand = obj.m_QuantityHand;
			m_Taxable = obj.m_Taxable;
			m_Price = obj.m_Price;
			m_QuantityNeeded = obj.m_QuantityNeeded;
		}

		return *this;
	}

	bool Good::operator==(const char* sku) const {
		return (strcmp(m_Sku, sku) == 0);
	}

	bool Good::operator>(const char* sku) const {
		return strcmp(m_Sku, sku) > 0;
	}

	bool Good::operator>(const Good & obj) const {
		return strcmp(m_Name, obj.name()) > 0;
	}

	int Good::operator+=(int add) {
		return (m_QuantityHand += (add > 0 ? add : 0));
	}

	double Good::total_cost() const {
		return itemCost() * m_QuantityHand;
	}

	void Good::quantity(int no) {
		m_QuantityHand = no;
	}

	bool Good::isEmpty() const {
		return m_Name == nullptr && m_Sku[0] == '\0' && m_Unit[0] == '\0' &&
				m_QuantityHand == 0 && m_Price == 0 && m_Taxable == false;
	}

	int Good::qtyNeeded() const {
		return m_QuantityNeeded;
	}

	int Good::quantity() const {
		return m_QuantityHand;
	}

	std::fstream & Good::store(std::fstream & file, bool newLine) const {
		file << m_TypeGood << "," << m_Sku << ',' << m_Name << ',' << m_Unit
			<< ',' << m_Taxable << ',' << quantity() << ',' << qtyNeeded();
		if (newLine) {
			file << endl;

		}

		return file;
	}

	std::fstream & Good::load(std::fstream & file) {
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

	std::ostream & Good::write(std::ostream & os, bool linear) const {
		if (!m_Error.isClear()) {
			os << m_Error.message();
		} else if (!isEmpty()) {
			char N[75];
			int qt = m_QuantityHand;

			if (linear) {
				strncpy(N, m_Name, 20);
				N[20] = 0;
				os << std::setw(max_sku_length) << std::left << m_Sku << "|" << std::setw(20) << std::left << N << "|"
					<< std::setw(7) << std::fixed << std::setprecision(2) << std::right << itemCost() << "|" << std::setw(4) << std::right << qt << "|" << std::setw(10) << std::left << m_Unit << "|" << std::setw(4) << std::right << m_QuantityNeeded << "|";
			} else {
				strncpy(N, m_Name, 74);
				N[74] = 0;
				os << " Sku: " << m_Sku << std::endl
					<< " Name (no spaces): " << N << std::endl
					<< " Price: " << m_Price << std::endl
					<< " Price after tax: ";
				if (m_Taxable) {
					os << itemCost() << std::endl;
				} else {
					os << " N/A" << std::endl;
					os << " Quantity on hand: " << qt << " " << m_Unit << std::endl
						<< " Quantity needed: " << m_QuantityNeeded;
				}
			}
		}

		return os;
	}

	std::istream & Good::read(std::istream & is) {
		char tmpSku[max_sku_length + 1];
		char tmpUnit[max_unit_length + 1];
		char tmpName[max_name_length + 1];
		int tmpQty;
		int tmpQtyNeeded;
		double tmpPrice;
		char tax;

		if (!is.fail()) m_Error.clear();

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
			m_Error.message("Only (Y)es or (N)o are acceptable");
		}

		if (m_Error.isClear() && is.fail()) {
			m_Error.message("Invalid Price Entry");
		}

		if (m_Error.isClear()) {
			std::cout << " Quantity on hand: ";
			std::cin >> tmpQty;
		}

		if (m_Error.isClear() && is.fail()) {
			m_Error.message("Invalid Quantity Entry");
		}

		if (m_Error.isClear()) {
			std::cout << " Quantity needed: ";
			std::cin >> tmpQtyNeeded;
			std::cin.ignore();
		}

		if (m_Error.isClear() && is.fail()) {
			m_Error.message("Invalid Quantity Needed Entry");
		}

		if (!is.fail())
			*this = Good(tmpSku, tmpName, tmpUnit, tmpQty, tax == 'y' || tax == 'Y', tmpPrice, tmpQtyNeeded);

		return is;
	}


	// helper functions
	std::ostream & operator<<(std::ostream & os, const Good & obj) {
		return obj.write(os, true);
	}

	std::istream & operator>>(std::istream& is, Good & obj) {
		return obj.read(is);
	}

	double operator+=(double & add, const Good & obj) {
		return obj.total_cost() + add;
	}
}
