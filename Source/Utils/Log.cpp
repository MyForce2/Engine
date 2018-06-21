
#include "Log.h"


#include <iostream>
#include <ctime>

namespace Engine {
	namespace Utils {

		const char* Log::LOG_PATH = "Log.txt";
		Log* Log::log = nullptr;

		Log::Log() : fileHandle() {
			fileHandle.open(LOG_PATH);
			memset(buffer, 0, BUFFER_SIZE);
			time_t now = time(0);
			ctime_s(buffer, BUFFER_SIZE, &now);
			std::string text = "Log started on : " + std::string(buffer);
			fileHandle << text;
		}

		Log::~Log() {
			time_t now = time(0);
			ctime_s(buffer, BUFFER_SIZE, &now);
			std::string text = "Log ended on : " + std::string(buffer);
			fileHandle << text;
			fileHandle.close();
		}

		void Log::logError(const std::string& message) {
			time_t now = time(0);
			ctime_s(buffer, BUFFER_SIZE, &now);
			std::string bufferText(buffer);
			bufferText.replace(bufferText.find('\n'), 1, "");
			std::string text = "[" + bufferText + "] " + "[Error] " + message + '\n';
			fileHandle.write(text.c_str(), text.length());
		}

		void Log::logWarning(const std::string& message) {
			time_t now = time(0);
			ctime_s(buffer, BUFFER_SIZE, &now);
			std::string bufferText(buffer);
			bufferText.replace(bufferText.find('\n'), 1, "");
			std::string text = "[" + bufferText + "] " + "[Warning] " + message + '\n';
			fileHandle.write(text.c_str(), text.length());
		}

		void Log::logInfo(const std::string& message) {
			time_t now = time(0);
			ctime_s(buffer, BUFFER_SIZE, &now);
			std::string bufferText(buffer);
			bufferText.replace(bufferText.find('\n'), 1, "");
			std::string text = "[" + bufferText + "] " +  "[Info] " + message + '\n';
			fileHandle.write(text.c_str(), text.length());
		}

		Log* Log::getLog() {
			if (log == nullptr)
				log = new Log();
			return log;
		}

		void Log::closeLog() {
			delete log;
		}
	}
}