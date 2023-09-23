#include <iomanip>
#include "AirportModels.h"

namespace sdds {
	Airport::Airport() {
		airportCode[0] = '\0';
		airportName = nullptr;
		airportCity = nullptr;
		airportState[0] = '\0';
		airportCountry[0] = '\0';
		airportLat = 0;
		airportLong = 0;
	}

    Airport::Airport(const Airport &src) {
        *this = src;
    }

    Airport& Airport::operator=(const Airport &src) {
        if (this == &src)
            return *this;

        strcpy(airportCode, src.airportCode);
        strcpy(airportState, src.airportState);
        strcpy(airportCountry, src.airportCountry);
        airportLat = src.airportLat;
        airportLong = src.airportLong;

        delete[] airportName;
        delete[] airportCity;

        if (src.airportCity != nullptr && src.airportName != nullptr) {
            airportName = new char[strlen(src.airportName) + 1];
            airportCity = new char[strlen(src.airportCity) + 1];
            strcpy(airportName, src.airportName);
            strcpy(airportCity, src.airportCity);
        } else {
            airportCity = nullptr;
            airportName = nullptr;
        }
        return *this;
    }

    Airport::~Airport() {
        delete[] airportName;
        delete[] airportCity;
    }

    Airport::operator bool() const {
        return (airportName == nullptr || airportCity == nullptr);
    }

    void Airport::display(std::ostream &os) {
        if (*this) {
            os << "Airport Code : " << std::left << std::setw(30) << airportCode << '\n'
               << "Airport Name : " << std::left << std::setw(30) << airportName << '\n'
               << "Airport City : " << std::left << std::setw(30) << airportCity << '\n'
               << "Airport State : " << std::left << std::setw(30) << airportState << '\n'
               << "Airport Country : " << std::left << std::setw(30) << airportCountry << '\n'
               << "Airport Latitude : " << std::left << std::setw(30) << std::fixed << std::setprecision(6) << airportLat << '\n'
               << "Airport Longitude : " << std::left << std::setw(30) << std::fixed << std::setprecision(6) << airportLong;
        }
    }

    std::ostream& operator<<(std::ostream& os, Airport& airport) {
        airport.display(os);
        return os;
    }


    //AirportLogs
    AirportLog::AirportLog() {
        counter = 0;
        airportList = nullptr;
    }

    AirportLog::AirportLog(const char *filename) {
        counter = 0;
        airportList = nullptr;

        if (filename != nullptr) {

        }
    }


}