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

#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iomanip>
#include <iostream>
#include "Book.h"

namespace sdds {
	template <typename T, unsigned C>
	class Collection {
		T m_items[C];
		static T m_smallestItem;
		static T m_largestItem;
		unsigned m_size;

	protected:
		void setSmallestItem(const T& item) {
			if (item < m_smallestItem) {
				m_smallestItem = item;
			}
		}
		void setLargestItem(const T& item) {
			if (item > m_largestItem) {
				m_largestItem = item;
			}
		}
		T& operator[](unsigned index) {
			if (index <= m_size) {
				return m_items[index];
			}
			else {
				throw std::out_of_range("Index out of bounds");
			}
		}

		void incrSize() {
			m_size++;
		}

	public:
		Collection() {
			m_size = 0;
		}

		static T getSmallestItem() {
			return m_smallestItem;
		}

		static T getLargestItem() {
			return m_largestItem;
		}
		unsigned size() const {
			return m_size;
		}

		unsigned capacity() const {
			return C;
		}

		bool operator+=(const T& item) {
			if (size() < capacity()) {
				m_items[m_size++] = item;
				setSmallestItem(item);
				setLargestItem(item);
				return true;
			}
			return false;
		}

		std::ostream& print(std::ostream& os) {
			os << "[";
			for (unsigned i = 0; i < m_size; i++) {
				os << std::setprecision(1) << m_items[i];
				if (i < m_size - 1) {
					os << ",";
				}
			}
			os << "]" << std::endl;
			return os;
		}

	};

	template <>
	Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);

	template <>
	Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);

	template <typename T, unsigned C>
	T Collection<T, C>::m_smallestItem = 9999;

	template <typename T, unsigned C>
	T Collection<T, C>::m_largestItem = -9999;



	template <>
	Book Collection<Book, 72>::m_smallestItem = Book("", 1, 10000);
	template <>
	Book Collection<Book, 72>::m_largestItem = Book("", 10000, 1);
	
	
	template<>
	std::ostream& Collection<Book, 10>::print(std::ostream& os) {
		os << "|" << std::setw(76) << std::setfill('-') << " " << "|" << std::endl << std::setfill(' ');
		for (unsigned i = 0; i < m_size; i++) {
			os << "| " << std::setw(65);
			os << std::setprecision(1) << m_items[i] << " |" << std::endl;
		}
		os << "|" << std::setw(76) << std::setfill('-') << " " << "|" << std::endl << std::setfill(' ');
		return os;
	}

	template<>
	std::ostream& Collection<Book, 72>::print(std::ostream& os) {
		os << "|" << std::setw(76) << std::setfill('-') << " " << "|" << std::endl << std::setfill(' ');
		for (unsigned i = 0; i < m_size; i++) {
			os << "| " << std::setw(65);
			os << std::setprecision(1) << m_items[i] << " |" << std::endl;
		}
		os << "|" << std::setw(76) << std::setfill('-') << " " << "|" << std::endl << std::setfill(' ');
		return os;
	}
}

#endif // !SDDS_COLLECTION_H