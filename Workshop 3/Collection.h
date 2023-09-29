#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

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

	public:
		Collection() {
			m_size = 0;
		}

		T getSmallestItem() {
			return m_smallestItem;
		}

		T getLargestItem() {
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
			os << "(smallest,largest) items: (" << m_smallestItem << "," << m_largestItem << ")" << std::endl;
			os << "size/capacity: " << m_size << "/" << C << std::endl;
			os << "Contents: [";
			for (unsigned i = 0; i < m_size; i++) {
				os << m_items[i];
				if (i < m_size - 1) {
					os << ",";
				}
			}
			os << "]" << std::endl;
			return os;
		}

	};

	// Specialization for T = Book and C = 10
	template <>
	Book Collection<Book, 10>::m_smallestItem;

	template <>
	Book Collection<Book, 10>::m_largestItem;
}

#endif // !SDDS_COLLECTION_H