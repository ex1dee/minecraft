#include "Files.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

std::string Files::read(const char* path) {
	std::string data;
	std::fstream file;
	std::stringstream stream;

	file.open(path);
	stream << file.rdbuf();
	close(file);

	return stream.str();
}

void Files::write(const char* path, const std::string& data) {
	std::fstream file;

	open(file, path);
	file << data;
	close(file);
}

void Files::open(std::fstream& file, const char* path) {
	file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	file.open(path, std::ios::out);
}

void Files::close(std::fstream& file) {
	file.close();
}

std::vector<std::string> Files::getFolderFiles(const char* dirPath) {
	std::vector<std::string> files;

	if (isDirectory(dirPath)) {
		for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
			files.push_back(entry.path().string());
		}
	} else {
		std::cout << "Folder \"" << dirPath << "\" was not found\n";
	}
	
	return files;
}

bool Files::isDirectory(const char* path) {
	return std::filesystem::is_directory(path);
}

bool Files::exists(const char* path) {
	return std::filesystem::exists(path);
}