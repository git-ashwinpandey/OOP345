#include "Filesystem.h"

namespace sdds {
	Filesystem::Filesystem(std::string fileName, std::string rootDir) {
		Directory* newDir = new Directory(rootDir);
		m_root = newDir;
		m_current = m_root;
		readFile(fileName, *newDir);
	}

	Filesystem::~Filesystem() {
		delete m_root;
	}

	// Move constructor
	Filesystem::Filesystem(Filesystem&& other) {
		m_root = other.m_root;
		m_current = other.m_current;

		other.m_root = nullptr;
		other.m_current = nullptr;
	}

	// Move assignment operator
	Filesystem& Filesystem::operator=(Filesystem&& other) {
		if (this != &other) {
			delete m_root;
			m_root = other.m_root;
			m_current = other.m_current;

			other.m_root = nullptr;
			other.m_current = nullptr;
		}
		return *this;
	}

	void Filesystem::readFile(std::string fileName, Directory& dir) {
		std::fstream file(fileName);
		if (file) {
			std::string line, path, file_content{};

			while (std::getline(file, line)) {
				line = trim(line);
				int seperatorIDX = line.find("|");
				if (seperatorIDX != int(std::string::npos)) {
					path = trim(line.substr(0, seperatorIDX));
					file_content = trim(line.substr(seperatorIDX + 1, std::string::npos));
				}
				else {
					path = trim(line.substr(0, seperatorIDX));
				}
				createFileSystem(path, file_content, dir);
			}
		}
		else {
			delete &dir;
			throw std::invalid_argument("Could not open the specified file for reading.");
		}
	}

	void Filesystem::createFileSystem(std::string file, std::string description, Directory& dir) {
		Directory* tempDir = &dir;
		int findPathIDX = file.find("/");
		int currentIDX{}, nextIDX{};
		std::string path {};
		while (findPathIDX != int(std::string::npos)) {
			nextIDX = findPathIDX;
			path = file.substr(currentIDX, nextIDX + 1 - currentIDX);
			if (tempDir->find(path) == nullptr) {
				Directory* addDir = new Directory(path);
				*tempDir += addDir;
				tempDir = addDir;
			}
			else {
				tempDir = dynamic_cast<Directory*>(dir.find(path));
			}	
			currentIDX = nextIDX + 1;
			findPathIDX = file.find("/", currentIDX);
		}
		path = file.substr(currentIDX, std::string::npos);
		if (!path.empty()) {
			File* tempFile = new File(path, description);
			*tempDir += tempFile;
		}
	}

	std::string trim(const std::string& str) {
		size_t start = str.find_first_not_of(" ");
		size_t end = str.find_last_not_of(" ");

		if (start == std::string::npos || end == std::string::npos)
			return "";

		return str.substr(start, end - start + 1);
	}

	Filesystem& Filesystem::operator+=(Resource* resource) {
		*m_current += resource;
		return *this;
	}

	Directory* Filesystem::change_directory(const std::string& changeTo) {
		if (changeTo[0] == '\0') {
			m_current = m_root;
			return m_current;
		} else {
			if (m_current->find(changeTo) != nullptr) {
				m_current = dynamic_cast<Directory*>(m_current->find(changeTo));
				return m_current;
			}
			else {
				throw std::invalid_argument("Cannot change directory! " + changeTo + " not found.");
			}
		}
	}

	Directory* Filesystem::get_current_directory() const {
		return m_current;
	}
}