// Common.h

#ifndef _Common_h
#define _Common_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace Component {
	static constexpr uint8_t X = 0;
	static constexpr uint8_t Y = 1;
	static constexpr uint8_t Z = 2;
	static constexpr uint8_t W = 3;
}

#define countof(x) (sizeof(x)/sizeof(x[0]))

template<typename T> constexpr T fractFixed(const T& lhs) { return lhs - floorFixed(lhs); }
template<typename T> constexpr T fracFixed(const T& lhs) { return fractFixed(lhs); }

template<typename T> constexpr T lerpFixed(const T& lhs, const T& rhs, const T& t) { return lhs * (1 - t) + rhs * t; }
template<typename T> constexpr T mixFixed(const T& lhs, const T& rhs, const T& t) { return lerpFixed(lhs, rhs, t); }

template<typename T> constexpr T sinFixed(const T& radian) { return T(sin(static_cast<float>(radian))); } //!< #TODO ˆê’Ufloat‚É‚µ‚Ä‚¢‚é
template<typename T> constexpr T cosFixed(const T& radian) { return T(cos(static_cast<float>(radian))); } //!< #TODO ˆê’Ufloat‚É‚µ‚Ä‚¢‚é

template<typename T> constexpr T sqrtFixed(const T& lhs) { return T(sqrt(static_cast<float>(lhs))); } //!< #TODO ˆê’Ufloat‚É‚µ‚Ä‚¢‚é

#endif

