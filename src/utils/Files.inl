#include "Files.h"

template<typename T>
static std::vector<std::string> Files::getFolderFiles(const std::string& dirPath, bool onlyDirectories, const std::string& extension) {
	std::vector<std::string> files;

	if (isDirectory(dirPath)) {
		for (const auto& entry : T(dirPath)) {
			if (!onlyDirectories && !entry.is_regular_file())
				continue;

			std::string path = entry.path().string();

			if (extension.size() == 0 || getFileExtension(path) == extension)
				files.push_back(path);
		}
	}
	else {
		std::cerr << "Folder \"" << dirPath << "\" was not found\n";
	}

	return files;
}