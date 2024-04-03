// Name: Ashwin Pandey
// Seneca Student ID: 156027211
// Seneca email: apandey21@myseneca.ca
// Date of completion: 7th November, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"


namespace sdds {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() {
		m_cntItem = 0;
		m_lstItem = nullptr;
	}

	CustomerOrder::CustomerOrder(const std::string& src) {
		Utilities util;
		size_t index = 0;
		bool more = true;

		m_name = util.extractToken(src, index, more);
		m_product = util.extractToken(src, index, more);

		while (more) {
			std::string tempItem{};
			tempItem = util.extractToken(src, index, more);

			Item** tempList = new Item * [m_cntItem + 1];
			for (size_t i = 0; i < m_cntItem; i++) {
				tempList[i] = m_lstItem[i];
			}
			tempList[m_cntItem] = new Item(tempItem);
			delete[] m_lstItem;
			m_lstItem = tempList;
			tempList = nullptr;
			m_cntItem++;
		}
		CustomerOrder::m_widthField = std::max(CustomerOrder::m_widthField, util.getFieldWidth());
	}

	CustomerOrder::~CustomerOrder() {
		deallocateResource();
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& src) {
		throw std::runtime_error("No copy");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept{
		*this = std::move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept{
		if (this != &src) {
			deallocateResource();

			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;

			src.m_name.clear();;
			src.m_product.clear();
			src.m_cntItem = 0;
			src.m_lstItem = nullptr;
		}

		return *this;
	}

	void CustomerOrder::deallocateResource() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	bool CustomerOrder::isOrderFilled() const {
		
		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}
	

	
	
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
				if (station.getQuantity() > 0) {
					m_lstItem[i]->m_isFilled = true;
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					
					os << "    Filled " << m_name << ", " << m_product
						<< " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
					break;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product
						<< " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}
	

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			os << std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";
			os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		}
	}
}