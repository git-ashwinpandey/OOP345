#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H

#include <iostream>

namespace sdds {
	class Movie {
		std::string movieTitle;
		size_t releaseYear;
		std::string description;
		
	public:
		Movie();
		Movie(const Movie& src);
		Movie& operator=(const Movie& src);
		Movie(Movie&& src);
		Movie& operator=(Movie&& src);

		const std::string& title() const;
		Movie(const std::string& strMovie);
		void display(std::ostream& os) const;

		template<typename T>
		void fixSpelling(T& spellChecker) {
			spellChecker(movieTitle);
			spellChecker(description);
		}
	};

	std::ostream& operator<<(std::ostream& os, const Movie& movie);
	std::string trim2(const std::string& str);
}

#endif // !SDDS_MOVIE_H
