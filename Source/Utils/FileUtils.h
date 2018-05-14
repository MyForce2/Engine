#pragma once


#include <string>
#include <iostream>
#include <fstream>

namespace Engine {
	namespace Utils {

		std::string readFile(const std::string& path) {
			std::fstream reader;
			std::string data = "";
			reader.open(path.c_str());
			if (!reader) {
				std::cout << "Failed to open file : " << path << std::endl;
				return "";
			}
			std::string line;
			while (std::getline(reader, line))
				data += line + '\n';
			return data;
		}

	}
}