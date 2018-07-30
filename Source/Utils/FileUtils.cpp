
#include <fstream>
#include <iostream>

#include "FileUtils.h"
#include "Log.h"

namespace Engine {
	namespace Utils {

		using namespace std;

		std::string readFile(const std::string& path) {
			ifstream reader;
			reader.open(path);
			if (!reader) {
				Log::getLog()->logError("Failed to open file [" + path + ']');
				return "";
			}
			reader.seekg(0, ios::end);
			int size = int(reader.tellg());
			char* buffer = new char[size + 1]();
			reader.seekg(ios::beg);
			reader.read(buffer, size);
			std::string text(buffer);
			delete[] buffer;
			return text;
		}

		void readFile(const std::string& path, std::string& data) {
			data = readFile(path);
		}
	}
}