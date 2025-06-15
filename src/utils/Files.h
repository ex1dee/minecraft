#ifndef FILES_H
#define FILES_H

#include <iostream>
#include <string>
#include <vector>

class Files {
	template<typename T> static std::vector<std::string> getFolderFiles(const std::string& dirPath, bool onlyDirectories, const std::string& extension = "");
public:
	static bool exists(const std::string& path);
	static bool isDirectory(const std::string& path);
	static int getLastSeparatorIndex(const std::string& path);
	static void write(const std::string& path, const std::string& data);
	static void open(std::fstream& file, const std::string& path);
	static void close(std::fstream& file);
	static std::string read(const std::string& path);
	static std::string getDirectory(const std::string& path);
	static std::string getFileExtension(const std::string& path);
	static std::string getLastPathSegment(const std::string& path);
	static std::string getPathBeforeExtension(const std::string& path);
	static std::string getFullPath(const std::string& dirPath, const std::string& fileName);
	static std::string getPathSegmentAfter(const std::string& path, const std::string& prefix);
	static std::vector<std::string> getFolderFiles(const std::string& dirPath, bool onlyDirectories, const std::string& extension = "");
	static std::vector<std::string> getFolderFilesDeep(const std::string& dirPath, bool onlyDirectories, const std::string& extension = "");
};

#include "Files.inl"

#endif