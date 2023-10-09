#include <iostream>
#include <iomanip>
#include "CheeseShop.h"

namespace sdds {
	CheeseShop::CheeseShop(const std::string& name) {
		shopName = name;
		cheeseList = nullptr;
		noOfCheese = 0;
	}

	CheeseShop& CheeseShop::addCheese(const Cheese& newCheese) {

		const Cheese** newCheeseList = new const Cheese * [noOfCheese + 1];
		for (int i = 0; i < noOfCheese; ++i) {
			newCheeseList[i] = cheeseList[i];
		}
		newCheeseList[noOfCheese] = new Cheese(newCheese);
		delete[] cheeseList;
		cheeseList = newCheeseList;
		++noOfCheese;
		return *this;
	}

	CheeseShop::CheeseShop(const CheeseShop& src) : shopName(src.shopName), noOfCheese(src.noOfCheese) {
		cheeseList = new const Cheese * [noOfCheese];
		for (int i = 0; i < noOfCheese; ++i) {
			cheeseList[i] = new Cheese(*src.cheeseList[i]);
		}
	}

	CheeseShop& CheeseShop::operator=(const CheeseShop& src) {
		if (this != &src) {
			// Deallocate existing resources
			for (int i = 0; i < noOfCheese; ++i) {
				delete cheeseList[i];
			}
			delete[] cheeseList;

			// Copy data from src
			shopName = src.shopName;
			noOfCheese = src.noOfCheese;

			// Allocate new resources
			cheeseList = new const Cheese * [noOfCheese];
			for (int i = 0; i < noOfCheese; ++i) {
				cheeseList[i] = new Cheese(*src.cheeseList[i]);
			}
		}
		return *this;
	}

	CheeseShop::~CheeseShop() {
		for (int i = 0; i < noOfCheese; i++) {
			delete cheeseList[i];
		}
		delete[] cheeseList;
	}

	CheeseShop::CheeseShop(CheeseShop&& src) : shopName(std::move(src.shopName)), noOfCheese(src.noOfCheese), cheeseList(src.cheeseList) {
		src.noOfCheese = 0;
		src.cheeseList = nullptr;
	}

	CheeseShop& CheeseShop::operator=(CheeseShop&& src) {
		if (this != &src) {
			// Deallocate existing resources
			for (int i = 0; i < noOfCheese; ++i) {
				delete cheeseList[i];
			}
			delete[] cheeseList;

			// Move data from src
			shopName = std::move(src.shopName);
			noOfCheese = src.noOfCheese;
			cheeseList = src.cheeseList;

			src.noOfCheese = 0;
			src.cheeseList = nullptr;
		}
		return *this;
	}

	void CheeseShop::display(std::ostream& os) const{
		os << std::setw(26) << std::setfill('-') << '-' << std::endl;
		os << std::setfill(' ') << shopName << std::endl;
		os << std::setw(26) << std::setfill('-') << '-' << std::endl << std::setfill(' ');
		if (noOfCheese == 0) {
			os << "This shop is out of cheese!" << std::endl;
		}
		else {
			for (int i = 0; i < noOfCheese; i++) {
				os << *cheeseList[i];
			}
		}
		os << std::setw(26) << std::setfill('-') << '-' << std::endl << std::setfill(' ');
	}

	std::ostream& operator<<(std::ostream& os, const CheeseShop& cheese) {
		cheese.display(os);
		return os;
	}
}