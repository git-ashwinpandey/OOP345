#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H

#include "Cheese.h"

namespace sdds {
	class CheeseParty {
		const Cheese** cheeseList;
		int noOfItems;
	public:
		CheeseParty();
		~CheeseParty();
		CheeseParty(const CheeseParty& src);
		CheeseParty& operator=(const CheeseParty& src);
		CheeseParty(CheeseParty&& src);
		CheeseParty& operator=(CheeseParty&& src);

		CheeseParty& addCheese(const Cheese&);
		CheeseParty& removeCheese();
		void display(std::ostream&) const;
	};

	std::ostream& operator<<(std::ostream& os, const CheeseParty& cheese);
}

#endif // !SDDS_CHEESEPARTY_H
