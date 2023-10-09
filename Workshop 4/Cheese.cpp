#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "Cheese.h"

namespace sdds {
	Cheese::Cheese() {
		emptyState();
	}

	Cheese::Cheese(const std::string& str) {
		std::string newStr = str;
		size_t currentIndex = 0;

		size_t nextIndex = newStr.find(",");
		if (nextIndex != std::string::npos) {
			name = trim(str.substr(currentIndex, nextIndex));
			currentIndex = nextIndex;
		}
		
		nextIndex = str.find_first_of(",", nextIndex + 1);
		if (nextIndex != std::string::npos) {
			weight = std::strtoul((str.substr(currentIndex + 1, nextIndex - currentIndex - 1)).c_str(), nullptr, 10);
			currentIndex = nextIndex;
		}
		
		nextIndex = str.find_first_of(",", nextIndex + 1);
		if (nextIndex != std::string::npos) {
			price = strtod((str.substr(currentIndex + 1, nextIndex - currentIndex - 1)).c_str(), nullptr);
			currentIndex = nextIndex;
		}
		
		nextIndex = str.find_first_of(",", nextIndex + 1);
		while (nextIndex != std::string::npos) {
			desc = desc + " " + trim(str.substr(currentIndex + 1, nextIndex - currentIndex - 1));
			currentIndex = nextIndex;
			nextIndex = str.find_first_of(",", nextIndex + 1);
		}

		desc = desc + " " + trim(str.substr(currentIndex + 1)) + " ";
	}

	Cheese::Cheese(const Cheese& src) {
		this->name = src.name;
		this->weight = src.weight;
		this->price = src.price;
		this->desc = src.desc;
	}

	Cheese& Cheese::operator=(const Cheese& src) {
		if (this != &src) {
			this->name = src.name;
			this->weight = src.weight;
			this->price = src.price;
			this->desc = src.desc;
		}
		return *this;
	}

	Cheese::Cheese(Cheese&& src) {
		*this = std::move(src);
	}

	Cheese& Cheese::operator=(Cheese&& src) {
		if (this != &src) {
			this->name = src.name;
			this->weight = src.weight;
			this->price = src.price;
			this->desc = src.desc;

			src.name = "NaC";
			src.weight = 0;
			src.price = 0.0;
			src.desc = "\0";
		}
		return *this;
	}

	Cheese Cheese::slice(size_t weight)
	{
		if (weight <= this->weight) {
			Cheese newCheese = *this;
			newCheese.setWeight(weight);
			this->weight -= weight;
			return newCheese;
		}
		return Cheese();
	}

	void Cheese::emptyState() {
		name = "NaC";
		weight = 0;
		price = 0.0;
		desc = "\0";
	}

	void Cheese::setWeight(size_t weight) {
		this->weight = weight;
	}

	std::string Cheese::getName() const{
		return name;
	}

	std::string Cheese::getDesc() const{
		return desc;
	}

	size_t Cheese::getWeight() const{
		return weight;
	}

	double Cheese::getPrice() const{
		return price;
	}

	void Cheese::display(std::ostream& os) const {
		os << "|" << std::setw(21) << std::left << name << "|"
			<< std::setw(5) << weight << "|" << std::fixed
			<< std::setprecision(2) << std::setw(5) << price << "|" 
			<< std::right <<  std::setw(34) << desc << "|" << std::endl;
	}


	std::ostream& operator<<(std::ostream& os, const Cheese& cheese) {
		cheese.display(os);
		return os;
	}

	std::string trim(const std::string& str) {
		size_t start = str.find_first_not_of(" ");
		size_t end = str.find_last_not_of(" ");

		if (start == std::string::npos || end == std::string::npos)
			return "";

		return str.substr(start, end - start + 1);
	}

}