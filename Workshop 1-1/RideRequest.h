//*****************************
//Name: Ashwin Pandey
//ID : 156027211
//Email : apandey21@myseneca.ca
//Section : NRA
//Date : 17th September, 2023
//* ****************************

#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

extern double g_taxrate;
extern double g_discount;

namespace sdds {
	class RideRequest {
		char name[10];
		char* desc;
		double price;
		bool discount;

	public:
		RideRequest();
		~RideRequest();
		void read(std::istream&);
		void display();
		RideRequest(const RideRequest& other);
		RideRequest& operator=(const RideRequest& other);
	};
}

#endif //!SDDS_RIDEREQUEST_H