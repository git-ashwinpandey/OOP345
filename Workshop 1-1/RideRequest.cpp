#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "RideRequest.h"

double g_taxrate = 0;
double g_discount = 0;

namespace sdds {
	RideRequest::RideRequest() {
		name[0] = '\0';
		desc = nullptr;
		price = 0.0;
		discount = false;
		
	}

	RideRequest::~RideRequest() {
		delete[] desc;
		desc = nullptr;
	}

	RideRequest::RideRequest(const RideRequest& other) {
		// Copy the member variables from 'other' to 'this'
		strcpy(name, other.name);

		if (other.desc) {
			// Allocate new memory for 'desc' and copy the description
			int length = strlen(other.desc);
			desc = new char[length + 1];
			strcpy(desc, other.desc);
		}
		else {
			desc = nullptr;
		}

		price = other.price;
		discount = other.discount;
	}

	RideRequest& RideRequest::operator=(const RideRequest& other) {
		if (this != &other) {  // Check for self-assignment
			// Copy the member variables from 'other' to 'this'
			strcpy(name, other.name);

			// Deallocate existing memory
			delete[] desc;
			desc = nullptr;

			if (other.desc) {
				// Allocate new memory for 'desc' and copy the description
				int length = strlen(other.desc);
				desc = new char[length + 1];
				strcpy(desc, other.desc);
			}

			price = other.price;
			discount = other.discount;
		}
		return *this;
	}


	void RideRequest::read(std::istream& is) {
		char t_discount;
		char t_desc[255];
		t_discount = '\0'; // Initialize t_discount
		t_desc[0] = '\0';  // Initialize t_desc
		if (is.good()) {

			is.getline(name, 10, ',');
			is.getline(t_desc, 255, ',');
			int length = strlen(t_desc);
			delete[] desc;
			desc = new char[length + 1];
			strcpy(desc, t_desc);
			is >> price;
			is.ignore();
			is >> t_discount;
		}

		if (t_discount == 'Y' || t_discount == 'y') {
			discount = true;
		}
		else {
			discount = false;
		}
		is.ignore();
	}

	void RideRequest::display() {
		// Increment the displayCounter each time display() is called
		static int displayCounter = 0;
		displayCounter++;

		std::cout << std::left << std::setw(2) << displayCounter << ". ";

		// Check if the customer name is empty
		if (name[0] == '\0') {
			std::cout << "No Ride Request" << std::endl;
			return;
		}

		std::cout << std::left << std::setw(10) << name << "|";
		std::cout << std::left << std::setw(25) << desc << "|";

		double priceWithTax = price + (price * g_taxrate);

		std::cout << std::fixed << std::setprecision(2) << std::left << std::setw(12) << priceWithTax << "|";

		if (discount) {
			double priceWithDiscount = priceWithTax - g_discount;
			std::cout << std::right << std::setw(13) << priceWithDiscount;
		}

		std::cout << std::endl;
	}
}