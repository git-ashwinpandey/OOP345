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
        Airport& operator=(&src);
    }

    Airport& Airport::operator=(const Airport &src) {
        return *this;
    }

}