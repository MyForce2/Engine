#include "Clock.h"

using namespace std;
using namespace chrono;

namespace Engine {
	namespace Utils {

		Clock::Clock() {
			start = high_resolution_clock::now();
		}

		Clock::~Clock() {

		}

		void Clock::reset() {
			start = high_resolution_clock::now();
		}

		float Clock::getTimePassed() const {
			auto now = high_resolution_clock::now();
			duration<float> duration = now - start;
			return duration.count();
		}
	}
}