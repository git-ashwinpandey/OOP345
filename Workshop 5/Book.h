#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>

namespace sdds {
	class Book {
		std::string author;
		std::string bookTitle;
		std::string bookCountry;
		size_t pubYear;
		double bookPrice;
		std::string description;

	public:
		Book();
		Book(const Book& src);
		Book& operator=(const Book& src);
		Book(Book&& src);
		Book& operator=(Book&& src);

		const std::string& title() const;
		const std::string& country() const;
		const size_t& year() const;
		double& price();

		void setPrice(double newPrice);
		Book(const std::string& strBook);

		void display(std::ostream&) const;

		template<typename T>
		void fixSpelling(T& spellChecker) {
			spellChecker(description);
		}
	};

	std::ostream& operator<<(std::ostream& os, const Book& book);

	std::string trim(const std::string& str);
}
#endif // !SDDS_BOOK_H
