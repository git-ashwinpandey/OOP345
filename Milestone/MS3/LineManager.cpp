// Name: Ashwin Pandey
// Seneca Student ID: 156027211
// Seneca email: apandey21@myseneca.ca
// Date of completion: 23rd November, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <fstream>
#include <istream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
#include <string>

namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		std::ifstream f(file);
		if (!f) {
			throw std::string("Unable to open file ") + file + " for reading.";
		}

		Utilities util;
		std::string record;

		// Read records from the file
		while (std::getline(f, record)) {
			bool more = true;
			size_t index = 0;
			std::string currentStationName = util.extractToken(record, index, more);
			std::string nextStationName = more ? util.extractToken(record, index, more) : "";

			// Find the station with the current name
			auto itCurrent = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
				return station->getItemName() == currentStationName;
				});

			// Find the station with the next name, or if nextStationName is empty, set it to nullptr
			auto itNext = nextStationName.empty() ? stations.end() :
				std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
				return station->getItemName() == nextStationName;
					});

			if (itCurrent != stations.end()) {
				// Store the current station in m_activeLine
				m_activeLine.push_back(*itCurrent);
				// Set the next station for the current station
				(*itCurrent)->setNextStation(itNext != stations.end() ? *itNext : nullptr);
			}
			else {
				throw std::string("Invalid linkage in the file.");
			}
		}

		// Find the first station in the assembly line
		auto itFirst = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
			return std::none_of(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* other) {
				return other->getNextStation() == station;
				});
			});

		if (itFirst != m_activeLine.end()) {
			m_firstStation = *itFirst;
		}

		m_cntCustomerOrder = g_pending.size();
	}

	void LineManager::reorderStations() {
		if (m_activeLine.empty() || m_firstStation == nullptr) {
			return; // Nothing to reorder
		}

		std::vector<Workstation*> reorderedStations;

		Workstation* currentStation = m_firstStation;
		while (currentStation != nullptr) {
			reorderedStations.push_back(currentStation);
			currentStation = currentStation->getNextStation();
		}

		m_activeLine = reorderedStations;
	}

	bool LineManager::run(std::ostream& os) {
		static size_t iterationCount = 0;  // Keep track of the current iteration number
		++iterationCount;
		bool result = false;
		os << "Line Manager Iteration: " << iterationCount << std::endl;

		if (!g_pending.empty()) {
			*m_firstStation +=(std::move(g_pending.front()));  // Move the order to m_firstStation
			g_pending.pop_front();
		}

		for (auto& station : m_activeLine) {
			station->fill(os);  // Execute one fill operation for each station
		}

		for (auto& station : m_activeLine) {
			station->attemptToMoveOrder();  // Attempt to move an order down the line for each station
			
		}

		for (auto& station : m_activeLine) {
			result = station->allOrderFilled();  // Check if any orders left at any station
			if (result == false) {
				break;
			}
		}
		
		return result;
	}

	void LineManager::display(std::ostream& os) const {
		for (const auto& station : m_activeLine) {
			station->display(os);
		}
	}

}