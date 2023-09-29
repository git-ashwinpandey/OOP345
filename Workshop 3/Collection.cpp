#include "Collection.h"

namespace sdds {
	template <>
	int Collection<int, 10>::m_smallestItem = 9999;

	template <>
	int Collection<int, 10>::m_largestItem = -9999;

	template <>
	double Collection<double, 10>::m_smallestItem = 9999.0;

	template <>
	double Collection<double, 10>::m_largestItem = -9999.0;


	template <>
	Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);

	template <>
	Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);
}