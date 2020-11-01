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

template<typename T> constexpr T toRadian(const T& lhs) { return lhs / 180.0f * T::Pi; }
template<typename T> constexpr T toDegree(const T& lhs) { return lhs / T::Pi * 180.0f; }

template<typename T> constexpr T sinFixed(const T& radian) { return T(sin(static_cast<float>(radian))); } //!< #TODO 一旦floatにしている
template<typename T> constexpr T cosFixed(const T& radian) { return T(cos(static_cast<float>(radian))); } //!< #TODO 一旦floatにしている

template<typename T> constexpr T sqrtFixed(const T& lhs) { return T(sqrt(static_cast<float>(lhs))); } //!< #TODO 一旦floatにしている


// M_2n = 1/(2n)^2 * [4 * M_n + 0, 4 * M_n + 2] 
//		             [4 * M_n + 3, 4 * M_n + 1]
// [2 x 2]
// 0 2
// 3 1
// [4 x 4]
//  0  8  0  8 + 0 0 2 2 =  0  8  2 10
// 12  4 12  4 + 0 0 2 2 = 12  4 14  6
//  0  8  0  8 + 3 3 1 1 =  3 11  1  9
// 12  4 12  4 + 3 3 1 1 = 15  7 13  5
// [8 x 8]
//  0 32  8 40  0 32  8 40 + 0 0 0 0 2 2 2 2 =  0 32  8 40  2 34 10 42
// 48 16 56 24 48 16 56 24 + 0 0 0 0 2 2 2 2 = 48 16 56 24 50 18 58 26
// 12 44  4 36 12 44  4 36 + 0 0 0 0 2 2 2 2 = 12 44  4 36 14 46  6 38
// 60 28 52 20 60 28 52 20 + 0 0 0 0 2 2 2 2 = 60 28 52 20 62 30 54 22
//  0 32  8 40  0 32  8 40 + 3 3 3 3 1 1 1 1 =  3 35 11 43  1 33  9 41
// 48 16 56 24 48 16 56 24 + 3 3 3 3 1 1 1 1 = 51 19 59 27 49 17 57 25
// 12 44  4 36 12 44  4 36 + 3 3 3 3 1 1 1 1 = 15 47  7 39 13 45  5 37
// 60 28 52 20 60 28 52 20 + 3 3 3 3 1 1 1 1 = 63 31 55 23 61 29 53 21
//!< C++11ではconstexor関数はreturnの一文のみでないといけないので注意 (In C++11, constexpr function must be one return sentence only)
constexpr uint8_t Bayer(const uint8_t i, const uint8_t j, const uint8_t n)
{
	//!< [ 4 * M_n, 4 * M_n ] 部
	//!< [ 4 * M_n, 4 * M_n ]
	return (n > 2 ? (Bayer(i % (n >> 1), j % (n >> 1), n >> 1) << 2) : 0)
		//!< [ 0, 2 ] 部
		//!< [ 3, 1 ]
		+ i / (n >> 1) | ((((i / (n >> 1)) & 1) ? !(j / (n >> 1)) : (j / (n >> 1))) << 1);
}

#endif

