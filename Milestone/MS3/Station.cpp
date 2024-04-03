// Name: Ashwin Pandey
// Seneca Student ID: 156027211
// Seneca email: apandey21@myseneca.ca
// Date of completion: 7th November, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <string>
#include <algorithm>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"


namespace sdds {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& line) {
		Utilities l_util;
		size_t start_pos = 0;
		bool more = true;
		m_id = ++id_generator;

		m_item = l_util.extractToken(line, start_pos, more);
		m_serial = std::stoul(l_util.extractToken(line, start_pos, more));
		m_stock = std::stoi(l_util.extractToken(line, start_pos, more));

		Station::m_widthField = std::max(Station::m_widthField, l_util.getFieldWidth());

		m_description = l_util.extractToken(line, start_pos, more);
	}

	const std::string& Station::getItemName() const {
		return m_item;
	}

	size_t Station::getNextSerialNumber() {
		return m_serial++;
	}

	size_t Station::getQuantity() const {
		return m_stock;
	}

	void Station::updateQuantity() {
		if (m_stock > 0) {
			--m_stock;
		}
	}

	void Station::display(std::ostream& os, bool full) const {
		
		os << std::setw(3) << std::setfill('0') << std::right << m_id << " | ";
		os << std::setw(Station::m_widthField) << std::setfill(' ') << std::left << m_item << " | ";
		os << std::setw(6) << std::setfill('0') << std::right << m_serial << " | ";

		if (full) {
			os << std::setw(4) << std::setfill(' ') << m_stock << " | ";
			os << m_description;
		}
		os << std::endl;
	}
}