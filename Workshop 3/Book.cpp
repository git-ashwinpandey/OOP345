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
			os << m_title << ',' << m_numChapters << "," << m_numPages << " | (" << double(m_numPages / m_numPages) << ")" << std::endl;
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