#ifndef _MATH_h
#define _MATH_h

#include "Ardu.h"

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

template<typename T> constexpr T toRadian(const T& lhs) { return lhs / 180.0f * T::Pi; }
template<typename T> constexpr T toDegree(const T& lhs) { return lhs / T::Pi * 180.0f; }

template<typename T> constexpr T sinFixed(const T& radian) { return T(sin(static_cast<float>(radian))); } //!< #PERFORMANCE_TODO 一旦floatにしているので効率が悪い
template<typename T> constexpr T cosFixed(const T& radian) { return T(cos(static_cast<float>(radian))); } //!< #PERFORMANCE_TODO

template<typename T> constexpr T sqrtFixed(const T& lhs) { return T(sqrt(static_cast<float>(lhs))); } //!< #PERFORMANCE_TODO

#endif

