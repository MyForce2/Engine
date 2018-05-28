#pragma once

#include <string>
#include <iostream>

#include "Utils\LinkedList.h"

namespace Engine {
	namespace Utils {

		void logError(const std::string& message);
		void logWarning(const std::string& message);
		void logMessage(const std::string& message);

	}
}
