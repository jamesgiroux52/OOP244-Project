/*
 ============================================================================
 Name        : Error.h
 Author      : James Giroux - jgiroux1@myseneca.ca
 Student #   : 129198164
 Section     : SEE
 Date        : July 15, 2019
 ============================================================================
 */

/*
 ============================================================================
 Description : Error header file
 ============================================================================
 */

#ifndef AID_ERROR_H_
#define AID_ERROR_H_

#include <iostream>

namespace aid {

	// error class
	class Error {
		char* m_message;
	public:
		explicit Error(const char* errorMessage = nullptr);
		Error(const Error& em);
		Error& operator=(const Error& em);
		~Error();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
		friend std::ostream& operator<<(std::ostream&, Error&);
	};
}

#endif /* AID_ERROR_H_ */
