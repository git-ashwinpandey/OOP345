#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H
#include <fstream>
#include "Directory.h"
#include "File.h"

namespace sdds {
	class Filesystem {
		Directory* m_root;
		Directory* m_current;
		void readFile(std::string fileName, Directory& dir);
		void createFileSystem(std::string file, std::string description, Directory& dir);
	public:
		Filesystem(std::string, std::string = {});
		~Filesystem();

		//Copy
		Filesystem(const Filesystem&) = delete;
		Filesystem& operator=(const Filesystem&) = delete;

		//Move
		Filesystem(Filesystem&&);
		Filesystem& operator=(Filesystem&&);

		Filesystem& operator+=(Resource*);
		Directory* change_directory(const std::string& changeTo = {});
		Directory* get_current_directory() const;

	};

	std::string trim(const std::string& str);
}

#endif // !SDDS_FILESYSTEM_H
