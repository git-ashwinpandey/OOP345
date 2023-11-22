#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "SpellChecker.h"



namespace sdds {
	SpellChecker::SpellChecker(const char* filename) {
		std::ifstream file(filename);
		if (!file) {
			throw "Bad file name!";
		}
		//std::string line {};
		size_t cnt = 0;
		do {
			std::string line {};
			std::getline(file, line);
			line = sdds::trim(line);
			size_t currentIndex = 0, nextIndex = -1;
			nextIndex = line.find_first_of(" ", currentIndex);
			if (nextIndex != std::string::npos) {
				m_badWords[cnt] = line.substr(currentIndex, nextIndex);
				m_goodWords[cnt] = trim(line.substr(nextIndex + 1));
				cnt++;
			}
		} while (file);
		
	}

	void SpellChecker::operator()(std::string& text) {
		for (int i = 0; i < 6; i++) {
			size_t currentIndex = 0;
			size_t nextIndex = 0;

			while ((nextIndex = text.find(m_badWords[i], currentIndex)) != std::string::npos) {
				text.replace(nextIndex, m_badWords[i].length(), m_goodWords[i]);
				currentIndex = nextIndex + m_goodWords[i].length();
				timesChanged[i]++;
			}
		}
	}

	void SpellChecker::showStatistics(std::ostream& out) const {
		out << "Spellchecker Statistics" << std::endl;
		for (int i = 0; i < 6; i++) {
			out << std::setw(15) << m_badWords[i] << ": " << timesChanged[i] << " replacements" << std::endl;
		}
	}


}