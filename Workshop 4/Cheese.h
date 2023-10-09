#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

#include <iostream>

namespace sdds {
	class Cheese {
		std::string name;
		size_t weight;
		double price;
		std::string desc;

		void emptyState();
	public:
		Cheese();
		Cheese(const std::string& str);
		Cheese(const Cheese& src);
		Cheese& operator=(const Cheese& src);
		Cheese(Cheese&& src);
		Cheese& operator=(Cheese&& src);

		Cheese slice(size_t weight);
		void setWeight(size_t weight);

		//Getters
		std::string getName() const;
		size_t getWeight() const;
		double getPrice() const;
		std::string getDesc() const;
		void display(std::ostream& os) const;
	};
	std::string trim(const std::string& str);
	std::ostream& operator<<(std::ostream& os, const Cheese& cheese);
}

#endif // !SDDS_CHEESE_H
