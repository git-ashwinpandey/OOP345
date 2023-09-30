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

#ifndef SDDS_ORDERED_COLLECTION_H
#define SDDS_ORDERED_COLLECTION_H

#include "Collection.h"

namespace sdds {
	template <typename T>
	class OrderedCollection : public Collection<T, 72> {
	public:
		bool operator+=(const T& item) {
			if (this->size() < this->capacity()) {
				unsigned index = 0;
				while (index < this->size() && item > this->operator[](index)) {
					++index;
				}
				for (unsigned i = this->size(); i > index; --i) {
					this->operator[](i) = this->operator[](i - 1);
				}
				this->operator[](index) = item;
				this->setSmallestItem(item);
				this->setLargestItem(item);
				this->incrSize();
				return true;
			}
			return false;
		}
	};
}

#endif // !SDDS_ORDERED_COLLECTION_H