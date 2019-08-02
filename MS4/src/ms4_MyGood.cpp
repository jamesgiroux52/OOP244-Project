/*
 ============================================================================
 Name        : ms4_MyGood.cpp
 Author      : James Giroux - jgiroux1@myseneca.ca
 Student #   : 129198164
 Section     : SEE
 Date        : July 27, 2019
 ============================================================================
 */

/*
 ============================================================================
 Description : MyGood module
 ============================================================================
 */


#include "ms4_MyGood.h"

namespace aid
{
	iGood* CreateProduct(char tag) {
		if (tag == 'n')
			return new MyGood("Good");
		else
			return new MyGood("Perishable");
	}
}
