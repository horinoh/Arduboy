// Common.h

#ifndef _Common_h
#define _Common_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace Component {
	static constexpr uint8_t x = 0;
	static constexpr uint8_t y = 1;
	static constexpr uint8_t z = 2;
	static constexpr uint8_t w = 3;

	static constexpr uint8_t X = 0;
	static constexpr uint8_t Y = 1;
	static constexpr uint8_t Z = 2;
	static constexpr uint8_t W = 3;
}

#define size(x) (sizeof(x)/sizeof(x[0]))

#endif

