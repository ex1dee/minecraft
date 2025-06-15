#include "Files.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <filesystem>

std::string Files::getFullPath(const std::string& dirPath, const std::string& fileName) {
	return dirPath + "/" + fileName;
}

std::string Files::getPathSegmentAfter(const std::string& path, const std::string& prefix) {
	int i;

	for (i = 0; i < path.size(); ++i) {
		if (path[i] != prefix[i])
			return path.substr(i);
	}

	return path;
}

std::string Files::getDirectory(const std::string& path) {
	return path.substr(0, getLastSeparatorIndex(path));
}

std::string Files::getLastPathSegment(const std::string& path) {
	return path.substr(getLastSeparatorIndex(path) + 1);
}

std::string Files::getFileExtension(const std::string& path) {
	return path.substr(path.find_first_of('.') + 1);
}

std::string Files::getPathBeforeExtension(const std::string& path) {
	return path.substr(0, path.find_last_of('.'));
}

int Files::getLastSeparatorIndex(const std::string& path) {
	int l1 = path.find_last_of('/');
	if (l1 >= std::string::npos) l1 = -1;

	int l2 = path.find_last_of('\\');
	if (l2 == std::string::npos) l2 = -1;

	return std::max(l1, l2);
}

std::string Files::read(const std::string& path) {
	std::string data;
	std::fstream file;
	std::stringstream stream;

	file.open(path);
	stream << file.rdbuf();
	close(file);

	return stream.str();
}

void Files::write(const std::string& path, const std::string& data) {
	std::fstream file;

	open(file, path);
	file << data;
	close(file);
}

void Files::open(std::fstream& file, const std::string& path) {
	file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	file.open(path, std::ios::out);
}

void Files::close(std::fstream& file) {
	file.close();
}

std::vector<std::string> Files::getFolderFiles(const std::string& dirPath, bool onlyDirectories, const std::string& extension) {
	return getFolderFiles<std::filesystem::directory_iterator>(dirPath, onlyDirectories, extension);
}

std::vector<std::string> Files::getFolderFilesDeep(const std::string& dirPath, bool onlyDirectories, const std::string& extension) {
	return getFolderFiles<std::filesystem::recursive_directory_iterator>(dirPath, onlyDirectories, extension);
}

bool Files::isDirectory(const std::string& path) {
	return std::filesystem::is_directory(path);
}

bool Files::exists(const std::string& path) {
	return std::filesystem::exists(path);
}