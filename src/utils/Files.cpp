#include "Files.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

std::string Files::getFullPath(const std::string& dirPath, const std::string& fileName) {
	return dirPath + "/" + fileName;
}

std::string Files::getDirectory(const std::string& path) {
	return path.substr(0, path.find_last_of('/'));
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

std::vector<std::string> Files::getFolderFiles(const std::string& dirPath) {
	std::vector<std::string> files;

	if (isDirectory(dirPath)) {
		for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
			files.push_back(entry.path().string());
		}
	} else {
		std::cerr << "Folder \"" << dirPath << "\" was not found\n";
	}
	
	return files;
}

bool Files::isDirectory(const std::string& path) {
	return std::filesystem::is_directory(path);
}

bool Files::exists(const std::string& path) {
	return std::filesystem::exists(path);
}