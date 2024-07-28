#include "Files.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

std::string Files::read(const char* path) {
	std::string data;
	std::ifstream file;
	std::stringstream stream;

	file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	file.open(path);
	stream << file.rdbuf();
	file.close();

	return stream.str();
}

void Files::write(const char* path, std::string data) {
	std::fstream file;

	file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	file.open(path, std::ios::out);
	file << data;
	file.close();
}

bool Files::exists(const char* path) {
	std::fstream file(path);

	return file.good();
}

std::vector<std::string> Files::getFolderFiles(const char* dirPath) {
	std::vector<std::string> files;

	if (std::filesystem::exists(dirPath) && std::filesystem::is_directory(dirPath)) {
		for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
			files.push_back(entry.path().string());
		}
	} else {
		std::cout << "Folder \"" << dirPath << "\" was not found\n";
	}
	
	return files;
}