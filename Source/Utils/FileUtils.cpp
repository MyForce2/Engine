
#include <fstream>

#include "FileUtils.h"
#include "Log.h"

namespace Engine {
	namespace Utils {

		std::string readFile(const std::string& path) {
			std::fstream reader;
			std::string data = "";
			reader.open(path.c_str());
			if (!reader) {
				logError("Failed to load file :" + path);
				return "";
			}
			std::string line;
			while (std::getline(reader, line))
				data += line + '\n';
			return data;
		}

		void readFile(const std::string& path, std::string& data) {
			std::fstream reader;
			reader.open(path.c_str());
			if (!reader) {
				logError("Failed to load file : " + path);
				return;
			}
			std::string line;
			while (std::getline(reader, line))
				data += line + '\n';
		}
	}
}