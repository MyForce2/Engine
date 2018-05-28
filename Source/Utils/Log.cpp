
#include "Log.h"

namespace Engine {
	namespace Utils {

		void logError(const std::string& message) {
			std::cout << "[Error] " << message << '\n';
		}

		void logWarning(const std::string& message) {
			std::cout << "[Warning] " << message << '\n';
		}

		void logMessage(const std::string& message) {
			std::cout << "[Log message] " << message << '\n';
		}

	}
}