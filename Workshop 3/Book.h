/*
*****************************
Workshop 3
Name: Ashwin Pandey
ID : 156027211
Email : apandey21@myseneca.ca
Section : NRA
Date : 30th September, 2023
*****************************
*/

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>

namespace sdds {
	class Book
	{
		std::string m_title{};
		unsigned m_numChapters{};
		unsigned m_numPages{};
	public:
		Book();
		Book(const std::string& title, unsigned nChapters, unsigned nPages);

		Book(const Book& other);
		Book& operator=(const Book& other);
		bool operator>(const Book& other) const;
		bool operator<(const Book& other) const;
		operator bool();
		bool isValid() const;
		std::ostream& print(std::ostream& os) const;

	};
	std::ostream& operator<<(std::ostream& os, const Book& bk);
}


#endif // !SDDS_BOOK_H

