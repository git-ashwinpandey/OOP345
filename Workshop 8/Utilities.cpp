// Workshop 8 - Smart Pointers
// 2019/11 - Cornel


#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		// TODO: Add your code here to build a collection of Profiles.
		//         The result should contain only profiles from `allProfiles`
		//         which are not in `bannedProfiles` using Raw Pointers.


		bool matchFound = false; 
		size_t firstPara = allProfiles.size();
		size_t secPara = bannedProfiles.size();
		for (size_t i = 0; i < firstPara; i++) {
			for (size_t j = 0; j < secPara; j++) {
				if ((bannedProfiles[j].m_age == allProfiles[i].m_age) && (bannedProfiles[j].m_name.first_name == allProfiles[i].m_name.first_name)
					&& (bannedProfiles[j].m_name.last_name == allProfiles[i].m_name.last_name)) {
					matchFound = true;
					break;
				} 
			}
			if (!matchFound) {
				Profile* temp = new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);
				try {
					temp->validateAddress();
					result += temp;
					delete temp;
				}
				catch (const std::string& msg){
					delete temp;
					throw msg;
				}
			}
			matchFound = false;
		}
		return result;
	}

	DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		// TODO: Add your code here to build a collection of Profiles.
		//		   The result should contain only profiles from `allProfiles`
		//         which are not in `bannedProfiles` using Smart Pointers.
		bool matchFound = false;
		size_t firstPara = allProfiles.size();
		size_t secPara = bannedProfiles.size();
		for (size_t i = 0; i < firstPara; i++) {
			for (size_t j = 0; j < secPara; j++) {
				if ((bannedProfiles[j].m_age == allProfiles[i].m_age) && (bannedProfiles[j].m_name.first_name == allProfiles[i].m_name.first_name)
					&& (bannedProfiles[j].m_name.last_name == allProfiles[i].m_name.last_name)) {
					matchFound = true;
					break;
				}
			}
			if (!matchFound) {
				std::unique_ptr<Profile> temp = std::make_unique<Profile>(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);
				try {
					temp->validateAddress();
					result += std::move(temp);
				}
				catch (const std::string& msg) {
					throw msg;
				}
			}
			matchFound = false;
		}



		return result;
	}
}