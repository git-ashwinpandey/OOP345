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

	Book::operator bool() const {
		return (m_title[0] != '\0' && m_numChapters > 0 && m_numPages > 0);
	}

	std::ostream& Book::print(std::ostream& os) const {
		if (*this) {
			std::string titleField = m_title + "," + std::to_string(m_numChapters) + "," + std::to_string(m_numPages);
			double avgPageChap = double(m_numPages) / double(m_numChapters);
			os << std::setw(56) << std::right << titleField << " |" << " (" << std::setw(9) << std::left << std::fixed << std::setprecision(6) << avgPageChap << std::setw(5) << ")";
		}
		else {
			os << "| Invalid Book data";
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