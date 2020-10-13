// Vec2.h

#ifndef _Vec2_h
#define _Vec2_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Common.h>
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

template<typename T = SQ15x16>
class Vec2
{
public:
	Vec2() { m[X] = 0.0; m[Y] = 0.0; }
	Vec2(const T& xx, const T& yy) { m[X] = xx; m[Y] = yy; }

	T& operator[](const uint8_t i) { return m[i]; }
	const T& operator[](const uint8_t i) const { return m[i]; }
	T& x() { return m[X]; }
	const T& x() const { return m[X]; }
	T& y() { return m[Y]; }
	const T& y() const { return m[Y]; }

	T LengthSquared() const { return m[X] * m[X] + m[Y] * m[Y]; }
	T Length() const { return T(sqrt(static_cast<float>(LengthSquared))); } //!< TODO ˆê’Ufloat‚É‚µ‚Äsqrt‚ðŽg—p‚µ‚Ä‚¢‚é
	Vec2<T> Normalize() const { return *this / Length(); }

	String ToString() const { return String(static_cast<float>(m[X])) + ", " + String(static_cast<float>(m[Y])); }
	operator const char*() const { return ToString().c_str(); }

private:
	T m[2];
};

template<typename T> T Dot(const Vec2<T>& lhs, const Vec2<T>& rhs) { return lhs[X] * rhs[X] + lhs[Y] * rhs[Y]; }
template<typename T> Vec2<T> operator+(const Vec2<T>& lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs[X] + rhs[X], lhs[Y] + rhs[Y]); }
template<typename T> Vec2<T> operator-(const Vec2<T>& lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs[X] - rhs[X], lhs[Y] - rhs[Y]); }
template<typename T> Vec2<T> operator*(const Vec2<T>& lhs, const T& rhs) { return Vec2<T>(lhs[X] * rhs, lhs[Y] * rhs); }
template<typename T> Vec2<T> operator*(const T& lhs, const Vec2<T>& rhs) { return Vec2<T>(lhs * rhs[X], lhs * rhs[Y]); }
template<typename T> Vec2<T> operator/(const Vec2<T>& lhs, const T& rhs) { return Vec2<T>(lhs[X] / rhs, lhs[Y] / rhs); }

#endif

