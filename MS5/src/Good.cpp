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

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "Good.h"

using namespace std;

namespace aid {

	// set name member of good
	void Good::name(const char* name) {
		if (name != nullptr) {
			m_name = new char[max_name_length + 1];
			strncpy(m_name, name, max_name_length);
			m_name[max_name_length] = '\0';
		} else {
			m_name = new char;
			m_name[0] = '\0';
		}
	}

	// return name
	const char* Good::name() const {
		return (m_name != nullptr && m_name[0] != '\0') ? m_name : nullptr;
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

	// return price + taxed if taxable
	double Good::itemCost() const {
		return m_taxable ? m_price * (1.0 + tax_rate) : m_price;
	}

	// sets error message
	void Good::message(const char* msg) {
		m_error.message(msg);
	}

	// return true if there is no error
	bool Good::isClear() const {
		return m_error.isClear();
	}

	// safe empty state
	void Good::setEmpty(const char type) {
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

	// Constructor
	Good::Good(const char type) {
		setEmpty(type);
	}

	// Seven argument Constructor
	Good::Good(const char* sku, const char* pname, const char* unit, int qty,
			bool taxed, double price, int qtyNeeded) {
		bool valid = false;

		// validate all values passed and initialize object
		if (sku != nullptr && pname != nullptr && unit != nullptr && sku[0] != '\0'
				&& pname[0] != '\0' && unit[0] != '\0' && qtyNeeded >= 0 && qty >= 0
				&& price >= 0) {
			valid = true;

			// since there is no input for type of good I have to
			// use known input to set the type of good
			if (strcmp("box", pname) == 0) {
				m_typeOfGood = 'N';
			} else {
				m_typeOfGood = 'P';
			}

			name(pname);
			strncpy(m_sku, sku, max_sku_length);
			m_sku[max_sku_length] = '\0';
			strncpy(m_unit, unit, max_unit_length);
			m_unit[max_unit_length] = '\0';
			m_quantityOnHand = qty;
			m_taxable = taxed;
			m_price = price;
			m_quantityNeeded = qtyNeeded;
		}

		if (!valid) {
			if (m_typeOfGood == 'P' || m_typeOfGood == 'p') {
				setEmpty('P');
			} else {
				setEmpty('N');
			}
		}
	}

	// copy object eliminates duplicate code
	void Good::copyObj(const Good& obj) {
		name(obj.m_name);

		strncpy(m_sku, obj.m_sku, max_sku_length);
		m_sku[max_sku_length] = '\0';

		strncpy(m_unit, obj.m_unit, max_unit_length);
		m_unit[max_unit_length] = '\0';

		if (obj.m_quantityOnHand >= 0)
			m_quantityOnHand = obj.m_quantityOnHand;
		if (obj.m_quantityNeeded >= 0)
			m_quantityNeeded = obj.m_quantityNeeded;
		if (obj.m_price >= 0.0)
			m_price = obj.m_price;
		if (obj.m_error.message())
			m_error.message(obj.m_error.message());

		m_taxable = obj.m_taxable;
		m_typeOfGood = obj.m_typeOfGood;
	}

	// Copy Constructor
	Good::Good(const Good& obj) {
		copyObj(obj);
	}

	// Destructor
	Good::~Good() {
		delete[] m_name;
		m_name = nullptr;
	}

	// Copy Assignment Operator
	Good& Good::operator=(const Good& obj) {
		copyObj(obj);
		return *this;
	}

	// relational operators
	bool Good::operator==(const char* sku) const {
		return (strcmp(m_sku, sku) == 0);
	}

	bool Good::operator>(const char* sku) const {
		return strcmp(m_sku, sku) > 0;
	}

	bool Good::operator>(const iGood& obj) const {
		return strcmp(m_name, obj.name()) > 0;
	}

	// add to quantity on hand operator
	int Good::operator+=(int add) {
		return (m_quantityOnHand += (add > 0 ? add : 0));
	}

	// returns the total cost with tax if good is taxable
	double Good::total_cost() const {
		return itemCost() * m_quantityOnHand;
	}

	// sets quantity on hand
	void Good::quantity(int no) {
		m_quantityOnHand = no;
	}

	// check for empty state
	bool Good::isEmpty() const {
		return m_name == nullptr && m_sku[0] == '\0' && m_unit[0] == '\0'
				&& m_quantityOnHand == 0 && m_price == 0 && m_taxable == false;
	}

	// returns quantity needed
	int Good::qtyNeeded() const {
		return m_quantityNeeded;
	}

	// returns quantity on hand
	int Good::quantity() const {
		return m_quantityOnHand;
	}

	// store members in file
	std::fstream& Good::store(std::fstream& file, bool newLine) const {
		file << m_typeOfGood << "," << m_sku << ',' << m_name << ',' << m_unit
				<< ',' << m_taxable << ',' << m_price << ',' << quantity() << ','
				<< qtyNeeded();

		if (newLine)
			file << endl;

		return file;
	}

	// load record from file
	std::fstream& Good::load(std::fstream& file) {
		Good temp;
		temp.m_name = new char[max_name_length + 1];

		file.getline(temp.m_sku, max_sku_length, ',');
		file.getline(temp.m_name, max_name_length, ',');
		file.getline(temp.m_unit, max_unit_length, ',');

		file >> temp.m_taxable;
		file.ignore();
		file >> temp.m_price;
		file.ignore();
		file >> temp.m_quantityOnHand;
		file.ignore();
		file >> temp.m_quantityNeeded;

		if (!temp.isEmpty())
			*this = temp;

		return file;
	}

	// Display current instance's data on the screen
	std::ostream& Good::write(std::ostream& os, bool linear) const {
		if (!m_error.isClear()) {
			os << m_error.message();
		} else if (!isEmpty()) {
			char N[75];
			int qt = m_quantityOnHand;

			if (linear) {
				strncpy(N, m_name, 20);
				N[20] = '\0';
				os << std::setw(max_sku_length) << std::left << m_sku << "|"
						<< std::setw(20) << std::left << N << "|" << std::setw(7)
						<< std::fixed << std::setprecision(2) << std::right
						<< itemCost() << "|" << std::setw(4) << std::right << qt
						<< "|" << std::setw(10) << std::left << m_unit << "|"
						<< std::setw(4) << std::right << m_quantityNeeded << "|";
			} else {
				strncpy(N, m_name, 74);
				N[74] = '\0';
				os << " Sku: " << m_sku << std::endl << " Name (no spaces): " << N
						<< std::endl << " Price: " << m_price << std::endl
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

	// get input from user
	std::istream& Good::read(std::istream& is) {
		char sku[max_sku_length + 1];
		char name[max_name_length + 1];
		char unit[max_unit_length + 1];
		char tax;
		bool taxStatus;
		double price;
		int qntHand;
		int qntNeed;
		Error error;

		std::cout << " Sku: ";
		is >> sku;
		std::cout << " Name (no spaces): ";
		is >> name;
		std::cout << " Unit: ";
		is >> unit;
		std::cout << " Taxed? (y/n): ";
		is >> tax;

		if (tax == 'y' || tax == 'Y') {
			taxStatus = true;
		} else if (tax == 'n' || tax == 'N') {
			taxStatus = false;
		} else {
			is.setstate(std::ios::failbit);
			error.message("Only (Y)es or (N)o are acceptable");

		}

		if (!is.fail()) {
			std::cout << " Price: ";
			is >> price;

			if (is.fail()) {
				error.message("Invalid Price Entry");
			}
		}

		if (!is.fail()) {
			std::cout << " Quantity on hand: ";
			is >> qntHand;

			if (is.fail()) {
				error.message("Invalid Quantity Entry");
			}
		}

		if (!is.fail()) {
			std::cout << " Quantity needed: ";
			is >> qntNeed;

			if (is.fail()) {
				error.message("Invalid Quantity Needed Entry");
			}
		}

		if (!is.fail()) {
			Good temp(sku, name, unit, qntHand, taxStatus, price, qntNeed);
			m_error.message(error.message());
			*this = temp;
		} else {
			*this = Good();
			if (error.message() != nullptr)
				m_error.message(error.message());
		}

		return is;
	}

	// helper functions
	std::ostream& operator<<(std::ostream& os, const iGood& obj) {
		return obj.write(os, true);
	}

	std::istream& operator>>(std::istream& is, iGood& obj) {
		return obj.read(is);
	}

	double operator+=(double& add, const iGood& obj) {
		return obj.total_cost() + add;
	}
}

