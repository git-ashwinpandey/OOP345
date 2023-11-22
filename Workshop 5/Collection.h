#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iostream>

namespace sdds {
	template<typename T>
	class Collection {
		std::string m_name;
		T* collection;
		size_t noOfItems;
		void (*m_observer)(const Collection<T>&, const T&);

	public:
		Collection(const std::string& name) {
			m_name = name;
			collection = nullptr;
			noOfItems = 0;
			m_observer = nullptr;
		}

		Collection(const T&) = delete;
		Collection& operator=(const T&) = delete;

		~Collection() {
			delete[] collection;
		}

		const std::string& name() const {
			return m_name;
		}

		size_t size() const {
			return noOfItems;
		}

		void setObserver(void (*observer)(const Collection<T>&, const T&)) {
			m_observer = observer;
		}

		Collection<T>& operator+=(const T& item) {
			bool itemExists = false;
			for (size_t i = 0; i < noOfItems; i++) {
				if (item.title() == collection[i].title()) {
					itemExists = true;
					return *this;
				}
			}

			if (!itemExists) {
				T* temp = new T[noOfItems + 1];
				for (size_t i = 0; i < noOfItems; i++) {
					temp[i] = collection[i];
				}
				temp[noOfItems] = item;
				delete[] collection;
				collection = temp;
				noOfItems++;
			}

			if (m_observer) {
				m_observer(*this, item);
			}

			return *this;
		}

		T& operator[](size_t idx) const {
			if (idx >= noOfItems) {
				throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(noOfItems) + "] items.");
			}
			return collection[idx];
			
		}

		T* operator[](const std::string& title) const {
			for (size_t i = 0; i < noOfItems; i++) {
				if (collection[i].title() == title) {
					return &collection[i];
				}
			}
			return nullptr;
		}

		void display(std::ostream& os) const {
			for (size_t i = 0; i < noOfItems; ++i) {
				os << collection[i];
			}
		}
	};

	/*template <typename T>
	std::ostream& operator<<(std::ostream& os, const Collection<T>& collection) {
		for (size_t i = 0; i < collection.size(); ++i) {
			os << collection[i];
		}
		return os;
	}*/
	template <typename T>
	std::ostream& operator<<(std::ostream& os, const Collection<T>& collection) {
		collection.display(os);
		return os;
	}
}

#endif // !SDDS_COLLECTION_H
