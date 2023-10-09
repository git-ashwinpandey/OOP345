#include <iostream>
#include <iomanip>
#include "CheeseParty.h"

namespace sdds {
	CheeseParty::CheeseParty() {
		cheeseList = nullptr;
		noOfItems = 0;
	}

	CheeseParty::CheeseParty(const CheeseParty& src) : cheeseList(nullptr), noOfItems(src.noOfItems) {
		if (noOfItems > 0) {
			cheeseList = new const Cheese * [noOfItems];
			for (int i = 0; i < noOfItems; ++i) {
				cheeseList[i] = src.cheeseList[i];
			}
		}
	}

	CheeseParty& CheeseParty::operator=(const CheeseParty& src) {
		if (this != &src) {
			// Deallocate existing resources
			delete[] cheeseList;

			// Copy data from src
			noOfItems = src.noOfItems;

			// Allocate new resources
			if (noOfItems > 0) {
				cheeseList = new const Cheese * [noOfItems];
				for (int i = 0; i < noOfItems; ++i) {
					cheeseList[i] = src.cheeseList[i];
				}
			}
			else {
				cheeseList = nullptr;
			}
		}
		return *this;
	}

	CheeseParty::CheeseParty(CheeseParty&& src) : cheeseList(src.cheeseList), noOfItems(src.noOfItems) {
		src.cheeseList = nullptr;
		src.noOfItems = 0;
	}

	CheeseParty& CheeseParty::operator=(CheeseParty&& src) {
		if (this != &src) {
			// Deallocate existing resources
			delete[] cheeseList;

			// Move data from src
			cheeseList = src.cheeseList;
			noOfItems = src.noOfItems;

			src.cheeseList = nullptr;
			src.noOfItems = 0;
		}
		return *this;
	}

	CheeseParty::~CheeseParty() {
		delete[] cheeseList;
	}

	CheeseParty& CheeseParty::addCheese(const Cheese& src) {
		// Check if the cheese is already in the list
		for (int i = 0; i < noOfItems; ++i) {
			if (cheeseList[i] == &src) {
				return *this; // Cheese is already in the list, do nothing
			}
		}

		// Resize the array and add the cheese
		const Cheese** newCheeseList = new const Cheese * [noOfItems + 1];
		for (int i = 0; i < noOfItems; ++i) {
			newCheeseList[i] = cheeseList[i];
		}
		newCheeseList[noOfItems] = &src;
		delete[] cheeseList;
		cheeseList = newCheeseList;
		++noOfItems;
		return *this;
	}

	CheeseParty& CheeseParty::removeCheese() {
		int removedCount = 0;
		for (int i = 0; i < noOfItems; ++i) {
			if (cheeseList[i]->getWeight() == 0) {
				cheeseList[i] = nullptr;
				removedCount++;
			}
		}

		if (removedCount > 0) {
			// Create a new array without removed cheeses
			const Cheese** newCheeseList = new const Cheese * [noOfItems - removedCount];
			int newIndex = 0;
			for (int i = 0; i < noOfItems; ++i) {
				if (cheeseList[i] != nullptr) {
					newCheeseList[newIndex] = cheeseList[i];
					newIndex++;
				}
			}
			delete[] cheeseList;
			cheeseList = newCheeseList;
			noOfItems -= removedCount;
		}

		return *this;
	}

	void CheeseParty::display(std::ostream& os) const {
		os << std::setw(26) << std::setfill('-') << '-' << std::endl;
		os << std::setfill(' ') << "Cheese Party" << std::endl;
		os << std::setw(26) << std::setfill('-') << '-' << std::endl << std::setfill(' ');
		if (noOfItems == 0) {
			os << "This party is just getting started!" << std::endl;
		}
		else {
			for (int i = 0; i < noOfItems; i++) {
				os << *cheeseList[i];
			}
		}
		os << std::setw(26) << std::setfill('-') << '-' << std::endl << std::setfill(' ');
	}
	
	std::ostream& operator<<(std::ostream& os, const CheeseParty& cheese) {
		cheese.display(os);
		return os;
	}
}