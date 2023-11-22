// Name: Ashwin Pandey
// Seneca Student ID: 156027211
// Seneca email: apandey21@myseneca.ca
// Date of completion: 7th November, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

namespace sdds {
	char Utilities::m_delimiter = ' ';

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		size_t startPos = next_pos;
		std::string token {};

		if (str[startPos] == m_delimiter) {
			more = false;
			throw std::runtime_error("No token");
		}
		else {
			size_t endPos = str.find(m_delimiter, next_pos);

			if (endPos == std::string::npos) {
				more = false;
				endPos = str.length();
			}
			else {
				more = true;
			}

			token = trim(str.substr(startPos, endPos - startPos));

			if (token.length() > m_widthField) {
				m_widthField = token.length();
			}

			next_pos = endPos + 1;
		}

		return token;
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}

	std::string trim(const std::string& str) {
		size_t start = str.find_first_not_of(" ");
		size_t end = str.find_last_not_of(" ");

		if (start == std::string::npos || end == std::string::npos)
			return "";

		return str.substr(start, end - start + 1);
	}
}