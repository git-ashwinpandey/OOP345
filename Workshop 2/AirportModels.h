
#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <iostream>

namespace sdds {
	struct Airport {
	private:
		char airportCode[4];
		char* airportName;
		char* airportCity;
		char airportState[3];
		char airportCountry[4];
		double airportLat;
		double airportLong;
	public:
		Airport();
		Airport(const Airport& src);
		Airport& operator=(const Airport& src);
        operator bool() const;
		//Airport(Airport&& src);
		//Airport& operator=(Airport&& src);
		~Airport();
		void display(std::ostream& os);
	};

	std::ostream& operator<<(std::ostream& os, Airport& airport);


	class AirportLog {
        int counter;
        Airport* airportList;
	public:
		AirportLog();
		AirportLog(const char* filename);
		void addAirport(const Airport& airport);
		Airport& findAirport(char* state, char* country);
		Airport& operator[](size_t index);
		operator size_t() const;
	};
}

#endif // !SDDS_AIRPORTMODELS_H

