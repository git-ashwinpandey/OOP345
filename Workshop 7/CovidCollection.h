#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H
#include <iostream>
#include <vector>
#include <list>


namespace sdds {
	struct Covid {
		std::string m_country{};
		std::string m_city{};
		std::string m_variant{};
		std::string severity {"General"};
		int m_year{};
		unsigned m_cases{};
		unsigned m_death{};
	};

	class CovidCollection {
		std::vector<Covid> covidCollection;
		void readFile(std::string);
	public:
		CovidCollection(const std::string);
		void display(std::ostream&, const std::string& country = "ALL") const;
		void sort(const std::string& field = "country");
		bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const;
		std::list<Covid> getListForDeaths(unsigned int deaths) const;
		void updateStatus();
	};
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
	std::string trim(const std::string& str);
}

#endif // !SDDS_COVIDCOLLECTION_H
