#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>
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

	Airport::Airport(const char* code, const char* name, const char* city, 
		const char* state, const char* country, double latitude, double longitude) {
		strcpy(airportCode, code);
		strcpy(airportState, state);
		strcpy(airportCountry, country);

		airportName = new char[strlen(name) + 1];
		strcpy(airportName, name);

		airportCity = new char[strlen(city) + 1];
		strcpy(airportCity, city);

		airportLat = latitude;
		airportLong = longitude;
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
		if (airportName != nullptr && airportCity != nullptr) {
			return true;
		}
		return false;
    }

	const char* Airport::getState() const {
		return airportState;
	}

	const char* Airport::getCountry() const {
		return airportCountry;
	}


    void Airport::display(std::ostream &os) {
		if (*this) {
			os << std::right << std::setfill('.') << std::setw(20) << "Airport Code" << " : " << std::left << std::setw(30) << airportCode << std::endl
				<< std::right << std::setfill('.') << std::setw(20) << "Airport Name" << " : " << std::left << std::setw(30) << airportName << std::endl
				<< std::right << std::setfill('.') << std::setw(20) << "City" << " : " << std::left << std::setw(30) << airportCity << std::endl
				<< std::right << std::setfill('.') << std::setw(20) << "State" << " : " << std::left << std::setw(30) << airportState << std::endl
				<< std::right << std::setfill('.') << std::setw(20) << "Country" << " : " << std::left << std::setw(30) << airportCountry << std::endl
				<< std::right << std::setfill('.') << std::setw(20) << "Latitude" << " : " << std::left << std::setw(30) << airportLat << std::endl;
			os << std::right << std::setfill('.') << std::setw(20) << "Longitude" << " : " << std::left << std::setw(30) << airportLong << std::endl;
		}
		else {
			os << "Empty Airport";
		}
    }

    std::ostream& operator<<(std::ostream& os, Airport& airport) {
        airport.display(os);
        return os;
    }


    //AirportLogs
    AirportLog::AirportLog() {
		noOfRecords = 0;
        airportList = nullptr;
		m_filename = nullptr;
    }

    AirportLog::AirportLog(const char *filename) {
		noOfRecords = 0;
        airportList = nullptr;
		m_filename = nullptr;

        if (filename != nullptr) {
			m_filename = new char[strlen(filename) + 1];
			strcpy(m_filename, filename);
		}
		else {
			std::cout << "Error reading file: " << filename << std::endl;
		}
		countRecords();
		airportList = new Airport[noOfRecords];
		readFile();
    }

	void AirportLog::countRecords() {
		int numOfLines = 0;
		if (m_filename != nullptr) {
			std::ifstream file(m_filename);
			if (file.is_open()) {
				char c;
				while (file.get(c)) {
					if (c == '\n') {
						numOfLines++;
					}
				}
				// Check for an extra line at the end of the file
				if (file.eof() && numOfLines > 0) {
					numOfLines--;
				}
				file.close();
				noOfRecords = numOfLines;
			}
			else {
				std::cerr << "Error opening file: " << m_filename << std::endl;
			}
		}
	}

	void AirportLog::readFile() {
		std::ifstream file;

		if (m_filename == nullptr) {
			std::cerr << "Error: File name is not provided." << std::endl;
			return;
		}

		file.open(m_filename);

		if (!file.is_open()) {
			std::cerr << "Error opening file: " << m_filename << std::endl;
			return;
		}

		// Read and discard the header line
		char t_header[255];
		if (!file.getline(t_header, 255, '\n')) {
			std::cerr << "Error reading header from file: " << m_filename << std::endl;
			file.close();
			return;
		}

		int t_counter = 0;
		char t_airportCode[4];
		char t_airportName[256];
		char t_airportCity[256];
		char t_airportState[3];
		char t_airportCountry[4];
		double t_airportLat;
		double t_airportLong;

		while (file) {
			if (!file.getline(t_airportCode, 4, ',')) {
				break; // Stop when there's no more data
			}
			if (!file.getline(t_airportName, 255, ',') ||
				!file.getline(t_airportCity, 255, ',') ||
				!file.getline(t_airportState, 3, ',') ||
				!file.getline(t_airportCountry, 4, ',') ||
				!(file >> t_airportLat) || // Check for successful conversion
				!(file.ignore(), file >> t_airportLong)) {
				std::cerr << "Error reading data from file: " << m_filename << std::endl;
				break;
			}
			file.ignore();

			airportList[t_counter++] = Airport(t_airportCode, t_airportName, t_airportCity, t_airportState,
				t_airportCountry, t_airportLat, t_airportLong);
		}

		noOfRecords = t_counter; // Update the number of records
		file.close();
	}


	void AirportLog::addAirport(const Airport& airport) {
		// Create a temporary new array with space for the new airport
		Airport* temp = new Airport[noOfRecords + 1];

		// Copy existing airports into the new array
		for (int i = 0; i < noOfRecords; ++i) {
			temp[i] = airportList[i];
		}

		// Add the new airport
		temp[noOfRecords] = airport;

		// Increment the record count
		++noOfRecords;

		// Deallocate the old array and update the pointer
		delete[] airportList;
		airportList = temp;
	}

	AirportLog AirportLog::findAirport(const char* state, const char* country) {
		AirportLog result;

		for (int i = 0; i < noOfRecords; ++i) {
			if (strcmp(airportList[i].getState(), state) == 0 && strcmp(airportList[i].getCountry(), country) == 0) {
				result.addAirport(airportList[i]);
			}
		}

		return result;
	}

	Airport& AirportLog::operator[](size_t index) const {
		if (index < static_cast<size_t> (noOfRecords)) {
			return airportList[index];
		}
		else {
			static Airport emptyAirport;
			return emptyAirport;
		}
		
	}

	AirportLog::operator size_t() const {
		return noOfRecords;
	}

	AirportLog::AirportLog(const AirportLog& src) {
		copyFrom(src);
	}

	// Implement copy assignment operator
	AirportLog& AirportLog::operator=(const AirportLog& src) {
		if (this == &src)
			return *this;

		clear();
		copyFrom(src);

		return *this;
	}

	// Helper function to copy from another AirportLog
	void AirportLog::copyFrom(const AirportLog& src) {
		noOfRecords = src.noOfRecords;

		if (src.m_filename != nullptr) {
			m_filename = new char[strlen(src.m_filename) + 1];
			strcpy(m_filename, src.m_filename);
		}
		else {
			m_filename = nullptr;
		}

		if (src.airportList != nullptr) {
			airportList = new Airport[noOfRecords];
			for (int i = 0; i < noOfRecords; ++i) {
				airportList[i] = src.airportList[i];
			}
		}
		else {
			airportList = nullptr;
		}
	}

	AirportLog::AirportLog(AirportLog&& src) {
		noOfRecords = src.noOfRecords;
		m_filename = src.m_filename;
		airportList = src.airportList;

		// Reset the source object
		src.noOfRecords = 0;
		src.m_filename = nullptr;
		src.airportList = nullptr;
	}

	AirportLog& AirportLog::operator=(AirportLog&& src) {
		if (this == &src)
			return *this;

		// Clear the current object
		clear();

		// Move resources from the source object
		noOfRecords = src.noOfRecords;
		m_filename = src.m_filename;
		airportList = src.airportList;

		// Reset the source object
		src.noOfRecords = 0;
		src.m_filename = nullptr;
		src.airportList = nullptr;

		return *this;
	}

	void AirportLog::clear() {
		delete[] m_filename;
		delete[] airportList;
		m_filename = nullptr;
		airportList = nullptr;
	}

	AirportLog::~AirportLog() {
		clear();
	}

}