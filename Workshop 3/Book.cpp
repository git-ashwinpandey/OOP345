#include <iomanip>
#include <string>
#include "Book.h"

namespace sdds {
	Book::Book() {
		m_title = "\0";
		m_numChapters = 0;
		m_numPages = 0;
	}

	Book::Book(const std::string& title, unsigned nChapters, unsigned nPages) {
		m_title = title;
		m_numChapters = nChapters;
		m_numPages = nPages;
	}

	// Copy constructor implementation
	Book::Book(const Book& other) {
		// Copy the attributes from the other Book object
		m_title = other.m_title;
		m_numChapters = other.m_numChapters;
		m_numPages = other.m_numPages;
	}

	// Copy assignment operator implementation
	Book& Book::operator=(const Book& other) {
		if (this != &other) { // Self-assignment check
			// Copy the attributes from the other Book object
			m_title = other.m_title;
			m_numChapters = other.m_numChapters;
			m_numPages = other.m_numPages;
		}
		return *this;
	}

	// Custom comparison function implementation
	bool Book::operator>(const Book& other) const {
		// Compare based on the ratio of pages to chapters
		double thisRatio = static_cast<double>(m_numPages) / m_numChapters;
		double otherRatio = static_cast<double>(other.m_numPages) / other.m_numChapters;
		return thisRatio > otherRatio;
	}

	bool Book::operator<(const Book& other) const {
		// Compare based on the ratio of pages to chapters
		double thisRatio = static_cast<double>(m_numPages) / m_numChapters;
		double otherRatio = static_cast<double>(other.m_numPages) / other.m_numChapters;
		return thisRatio < otherRatio;
	}

	Book::operator bool() {
		double avgPageChap = double(m_numPages) / double(m_numChapters);
		return avgPageChap;
	}

	bool Book::isValid() const {
		return (m_title[0] != '\0' && m_numChapters > 0 && m_numPages > 0);
	}

	std::ostream& Book::print(std::ostream& os) const {
		if (isValid()) {
			std::string titleField = m_title + "," + std::to_string(m_numChapters) + "," + std::to_string(m_numPages);
			double avgPageChap = double(m_numPages) / double(m_numChapters);
			os << std::setw(56) << std::right << titleField << " |" << " (" << std::setw(9) << std::left << std::fixed << std::setprecision(6) << avgPageChap << std::setw(5) << ")";
		}
		else {
			os << "| Invalid book data";
		}
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Book& bk) {
		if (os) {
			return bk.print(os);
		}
		return os;
	}

}