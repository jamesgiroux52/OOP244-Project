/*
 ============================================================================
 Name        : Error.h
 Author      : James Giroux - jgiroux1@myseneca.ca
 Student #   : 129198164
 Section     : SEE
 Date        : July 25, 2019
 ============================================================================
 */

/*
 ============================================================================
 Description : Error header file
 ============================================================================
 */


#ifndef AID_ERROR_H
#define AID_ERROR_H

#include <iostream>

namespace aid {
	class Error {
		// private message member
		char* m_message;
	public:
		// public logic
		explicit Error(const char* errorMessage = nullptr);
		Error(const Error& em) = delete;
		Error& operator=(const Error& em) = delete;
		virtual ~Error();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
		friend std::ostream& operator<<(std::ostream&, Error&);
	};
}

#endif // !AID_ERROR_H
