#ifndef FILES_H
#define FILES_H

#include <string>
#include <vector>

class Files {
public:
	static bool exists(const char* path);
	static bool isDirectory(const char* path);
	static void write(const char* path, const std::string& data);
	static void open(std::fstream& file, const char* path);
	static void close(std::fstream& file);
	static std::string read(const char* path);
	static std::vector<std::string> getFolderFiles(const char* dirPath);
};

#endif