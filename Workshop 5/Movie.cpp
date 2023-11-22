#include <iostream>
#include <iomanip>
#include "Movie.h"

namespace sdds {
	Movie::Movie() {
		movieTitle = "\0";
		releaseYear = -1;
		description = "\0";
	}

	Movie::Movie(const std::string& strMovie) {
		size_t currentIndex = 0, nextIndex = -1;
		std::string movieObj = trim2(strMovie);

		nextIndex = movieObj.find_first_of(",", currentIndex);
		if (nextIndex != std::string::npos) {
			movieTitle = trim2(movieObj.substr(currentIndex, nextIndex - currentIndex));
			currentIndex = nextIndex;
		}

		nextIndex = movieObj.find_first_of(",", nextIndex + 1);
		if (nextIndex != std::string::npos) {
			releaseYear = strtoul((movieObj.substr(currentIndex + 1, nextIndex - currentIndex - 1)).c_str(), nullptr, 10);
			currentIndex = nextIndex;
		}

		while (nextIndex != std::string::npos) {
			description = description + " " + trim2(movieObj.substr(currentIndex + 1, nextIndex - currentIndex));
			currentIndex = nextIndex;
			nextIndex = movieObj.find_first_of(",", nextIndex + 1);
		}

		description = description + " " + trim2(movieObj.substr(currentIndex + 1)) + " ";
		description = trim2(description);

	}

	Movie::Movie(const Movie& src) {
		this->movieTitle = src.movieTitle;
		this->releaseYear = src.releaseYear;
		this->description = src.description;
	}

	Movie& Movie::operator=(const Movie& src) {
		if (this != &src) {
			this->movieTitle = src.movieTitle;
			this->releaseYear = src.releaseYear;
			this->description = src.description;
		}
		return *this;
	}

	Movie::Movie(Movie&& src) {
		*this = std::move(src);
	}

	Movie& Movie::operator=(Movie&& src) {
		if (this != &src) {
			this->movieTitle = src.movieTitle;
			this->releaseYear = src.releaseYear;
			this->description = src.description;

			src.movieTitle = "\0";
			src.releaseYear = -1;
			src.description = "\0";
		}
		return *this;
	}

	const std::string& Movie::title() const {
		return movieTitle;
	}

	void Movie::display(std::ostream& os) const{
		os << std::setw(40) << std::right << movieTitle << " | ";
		os << std::setw(4) << std::right << releaseYear << " | ";
		os << std::right << description << std::endl;
	}

	std::ostream& operator<<(std::ostream& os, const Movie& movie) {
		movie.display(os);
		return os;
	}

	std::string trim2(const std::string& str) {
		size_t start = str.find_first_not_of(" ");
		size_t end = str.find_last_not_of(" ");

		if (start == std::string::npos || end == std::string::npos)
			return "";

		return str.substr(start, end - start + 1);
	}
}