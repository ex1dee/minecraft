#ifndef FILES_H
#define FILES_H

#include <string>
#include <vector>

class Files {
public:
	static std::string read(const char* path);
	static void write(const char* path, std::string data);
	static bool exists(const char* path);
	static std::vector<std::string> getFolderFiles(const char* dirPath);
};

#endif