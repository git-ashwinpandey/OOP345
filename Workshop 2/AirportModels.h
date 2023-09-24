
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
		Airport(const char* code, const char* name, const char* city, 
			const char* state, const char* country, double latitude, double longitude);
		Airport(const Airport& src);
		Airport& operator=(const Airport& src);
        operator bool() const;
		//Airport(Airport&& src);
		//Airport& operator=(Airport&& src);
		~Airport();
		void display(std::ostream& os);
		const char* getState() const;
		const char* getCountry() const;
	};

	std::ostream& operator<<(std::ostream& os, Airport& airport);


	class AirportLog {
        int noOfRecords;
		char* m_filename;
        Airport* airportList;
		void readFile();
		void countRecords();
		void copyFrom(const AirportLog& src);
		void clear();
	public:
		AirportLog();
		AirportLog(const char* filename);

		AirportLog(const AirportLog& src); // Copy constructor
		AirportLog& operator=(const AirportLog& src); // Copy assignment operator
		AirportLog(AirportLog&& src);
		AirportLog& operator=(AirportLog&& src);
		~AirportLog();
		

		void addAirport(const Airport& airport);
		AirportLog findAirport(const char* state, const char* country);
		Airport& operator[](size_t index) const;
		operator size_t() const;
		
	};
}

#endif // !SDDS_AIRPORTMODELS_H

