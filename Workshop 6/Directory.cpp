#include <iostream>
#include <iomanip>
#include "Directory.h"


namespace sdds {
	Directory::Directory(std::string name) {
		m_name = name;
	}
	Directory::~Directory() {
		for (Resource* resource : m_contents) {
			delete resource;
		}
	}

	void Directory::update_parent_path(const std::string& path) {
		m_parent_path = path;
		for (Resource* resource : m_contents) {
			resource->update_parent_path(m_parent_path + m_name);
		}
	}

	NodeType Directory::type() const {
		return NodeType::DIR;
	}

	std::string Directory::path() const {
		return m_parent_path + m_name;
	}
	std::string Directory::name() const {
		return m_name;
	}

	int Directory::count() const {
		return m_contents.size();
	}
	size_t Directory::size() const {
		size_t totalSize = 0u;
		int noOfItems = count();
		for (int i = 0; i < noOfItems; i++) {
			totalSize += m_contents[i]->size();
		}
		return totalSize;
	}

	Directory& Directory::operator+=(Resource* resource) {
		int itemCount = count();
		for (int i = 0; i < itemCount; i++) {
			if (m_contents[i]->name() == resource->name()) {
				throw("Resource already exists");
			}
		}
		resource->update_parent_path(m_parent_path + m_name);
		m_contents.push_back(resource);
		return *this;
	}

	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flag) {
		if (flag.empty()) {
			for (int i = 0; i < count(); i++) {
				if (m_contents[i]->name() == name) {
					return m_contents[i];
				}
			}
		}
		else {
			for (int i = 0; i < count(); i++) {
				if (m_contents[i]->type() == NodeType::DIR) {
					return dynamic_cast<Directory*>( m_contents[i])->find(name, flag);
				}
				else if (m_contents[i]->name() == name) {
					return m_contents[i];
				}
			}
		}
		
		return nullptr;
	}

	void Directory::remove(const std::string& name, const std::vector<OpFlags>& flag) {
		Resource* resourceToRemove = find(name);
		if (!resourceToRemove) {
			throw std::invalid_argument(name + " does not exist in " + m_name);
		}

		if (!flag.empty()) {
			for (const OpFlags& flag : flag) {
				if (flag == OpFlags::RECURSIVE) {
					if (resourceToRemove->type() == NodeType::DIR) {
						delete resourceToRemove;

						for (auto it = m_contents.begin(); it != m_contents.end(); ++it) {
							if (*it == resourceToRemove) {
								m_contents.erase(it);
							}
						}
					}
					else {
						throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
					}
				}
			}
		}
		else {
			if (resourceToRemove->type() == NodeType::DIR) {
				throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
			}
			// Delete a file
			for (size_t i = 0; i < m_contents.size(); ++i) {
				if (m_contents[i] == resourceToRemove) {
					delete m_contents[i];
					m_contents.erase(m_contents.begin() + i);
					break;
				}
			}
		}
	}

	void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const {
		os << "Total size: " << size() << " bytes" << std::endl;
		bool formatFlag = false;
		for (FormatFlags flag : flags) {
			if (flag == FormatFlags::LONG) {
				formatFlag = true;
			}
		}
		for (int i = 0; i < count(); i++) {
			if (m_contents[i]->type() == NodeType::DIR) {
				os << "D";
			}
			else {
				os << "F"; 
			}
			os << " | " << std::setw(15) << std::left << m_contents[i]->name() << " |";
			if (formatFlag) {
				if (m_contents[i]->type() == NodeType::DIR) {
					os << " " <<  std::setw(2) << std::right << m_contents[i]->count() << " | ";
					os << std::setw(10) << std::right << std::to_string(m_contents[i]->size()) + " bytes" << " | ";
				}
				else {
					os << "    | ";
					os << std::setw(10) << std::right << std::to_string(m_contents[i]->size()) + " bytes" << " | ";
				}
			}
			os << std::endl;
		}
	}
}