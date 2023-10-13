#include <iostream>
#include <iomanip>
#include "Book.h"

namespace sdds {
	Book::Book() {
		author = "\0";
		bookTitle = "\0";
		bookCountry = "\0";
		pubYear = -1;
		bookPrice = -1;
		description = "\0";
	}

	Book::Book(const Book& src) {
		this->author = src.author;
		this->bookTitle = src.bookTitle;
		this->bookCountry = src.bookCountry;
		this->pubYear = src.pubYear;
		this->bookPrice = src.bookPrice;
		this->description = src.description;
	}

	Book& Book::operator=(const Book& src) {
		if (this != &src) {
			this->author = src.author;
			this->bookTitle = src.bookTitle;
			this->bookCountry = src.bookCountry;
			this->pubYear = src.pubYear;
			this->bookPrice = src.bookPrice;
			this->description = src.description;
		}
		return *this;
	}

	Book::Book(Book&& src) {
		*this = std::move(src);
	}

	Book& Book::operator=(Book&& src) {
		if (this != &src) {
			this->author = src.author;
			this->bookTitle = src.bookTitle;
			this->bookCountry = src.bookCountry;
			this->pubYear = src.pubYear;
			this->bookPrice = src.bookPrice;
			this->description = src.description;

			src.author = "\0";
			src.bookTitle = "\0";
			src.bookCountry = "\0";
			src.pubYear = -1;
			src.bookPrice = -1;
			src.description = "\0";
		}
		return *this;
	}

	const std::string& Book::title() const {
		return bookTitle;
	}

	const std::string& Book::country() const {
		return bookCountry;
	}

	const size_t& Book::year() const {
		return pubYear;
	}

	double& Book::price() {
		return bookPrice;
	}

	void Book::setPrice(double newPrice) {
		this->bookPrice = newPrice;
	}

	Book::Book(const std::string& strBook) {
		size_t currentIndex = 0, nextIndex = -1;

		std::string bookObj = trim(strBook);

		nextIndex = bookObj.find_first_of(",", currentIndex);
		if (nextIndex != std::string::npos) {
			author = trim(bookObj.substr(currentIndex, nextIndex));
			currentIndex = nextIndex;
		}

		nextIndex = bookObj.find_first_of(",", nextIndex + 1);
		if (nextIndex != std::string::npos) {
			bookTitle = trim(bookObj.substr(currentIndex + 1, nextIndex - currentIndex - 1));
			currentIndex = nextIndex;
		}

		nextIndex = bookObj.find_first_of(",", nextIndex + 1);
		if (nextIndex != std::string::npos) {
			bookCountry = trim(bookObj.substr(currentIndex + 1, nextIndex - currentIndex - 1));
			currentIndex = nextIndex;
		}

		nextIndex = bookObj.find_first_of(",", nextIndex + 1);
		if (nextIndex != std::string::npos) {
			bookPrice = strtod((bookObj.substr(currentIndex + 1, nextIndex - currentIndex - 1)).c_str(), nullptr);
			currentIndex = nextIndex;
		}

		nextIndex = bookObj.find_first_of(",", nextIndex + 1);
		if (nextIndex != std::string::npos) {
			pubYear = strtoul((bookObj.substr(currentIndex + 1, nextIndex - currentIndex - 1)).c_str(), nullptr, 10);
			currentIndex = nextIndex;
		}

		while (nextIndex != std::string::npos) {
			description = description + " " + trim(bookObj.substr(currentIndex + 1, nextIndex - currentIndex));
			currentIndex = nextIndex;
			nextIndex = bookObj.find_first_of(",", nextIndex + 1);
		}

		description = description + " " + trim(bookObj.substr(currentIndex + 1)) + " ";
		description = trim(description);
	}

	void Book::display(std::ostream& os) const {
		os << std::setw(20) << std::right << author << " | ";
		os << std::setw(22) << std::right << bookTitle << " | ";
		os << std::setw(5) << std::right << bookCountry << " | ";
		os << std::setw(4) << pubYear << " | ";
		os << std::setw(6) << std::right << std::fixed << std::setprecision(2) << bookPrice << " | ";
		os << std::setw(20) << std::left << description;
	}


	std::ostream& operator<<(std::ostream& os, const Book& book) {
		book.display(os);
		return os;
	}


	std::string trim(const std::string& str) {
		size_t start = str.find_first_not_of(" ");
		size_t end = str.find_last_not_of(" ");

		if (start == std::string::npos || end == std::string::npos)
			return "";

		return str.substr(start, end - start + 1);
	}


}