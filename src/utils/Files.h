#ifndef FILES_H
#define FILES_H

#include <string>
#include <vector>

class Files {
public:
	static bool exists(const std::string& path);
	static bool isDirectory(const std::string& path);
	static std::string getDirectory(const std::string& path);
	static void write(const std::string& path, const std::string& data);
	static void open(std::fstream& file, const std::string& path);
	static void close(std::fstream& file);
	static std::string read(const std::string& path);
	static std::vector<std::string> getFolderFiles(const std::string& dirPath);
	static std::string getFullPath(const std::string& dirPath, const std::string& fileName);
};

#endif