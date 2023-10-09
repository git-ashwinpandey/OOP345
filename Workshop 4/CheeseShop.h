#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H

#include <iostream>
#include "Cheese.h"

namespace sdds {
	class CheeseShop {
		std::string shopName;
		int noOfCheese;
		const Cheese** cheeseList;
	public:
		CheeseShop(const std::string& name = "No Name");
		CheeseShop(const CheeseShop& src);
		CheeseShop& operator=(const CheeseShop& src);
		~CheeseShop();
		CheeseShop(CheeseShop&& src);
		CheeseShop& operator=(CheeseShop&& src);
		CheeseShop& addCheese(const Cheese&);
		void display(std::ostream&) const;
	};

	std::ostream& operator<<(std::ostream& os, const CheeseShop& cheese);
}
#endif // !SDDS_CHEESESHOP_H

