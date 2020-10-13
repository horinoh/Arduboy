// Vec4.h

#ifndef _Vec4_h
#define _Vec4_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Common.h>
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

template<typename T = SQ15x16>
class Vec4
{
public:
	Vec4() { m[X] = 0.0; m[Y] = 0.0; m[Z] = 0.0; m[W] = 0.0; }
	Vec4(const T& xx, const T& yy, const T& zz, const T& ww) { m[X] = xx; m[Y] = yy; m[Z] = zz; m[W] = ww; }

	T& operator[](const uint8_t i) { return m[i]; }
	const T& operator[](const uint8_t i) const { return m[i]; }
	T& x() { return m[X]; }
	const T& x() const { return m[X]; }
	T& y() { return m[Y]; }
	const T& y() const { return m[Y]; }
	T& z() { return m[Z]; }
	const T& z() const { return m[Z]; }
	T& w() { return m[W]; }
	const T& w() const { return m[W]; }

	T LengthSquared() const { return m[X] * m[X] + m[Y] * m[Y] + m[Z] * m[Z] + m[W] * m[W]; }
	T Length() const { return T(sqrt(static_cast<float>(LengthSquared))); } //!< TODO ˆê’Ufloat‚É‚µ‚Äsqrt‚ðŽg—p‚µ‚Ä‚¢‚é
	Vec4<T> Normalize() const { return *this / Length(); }

	String ToString() const { return String(static_cast<float>(m[X])) + ", " + String(static_cast<float>(m[Y])) + ", " + String(static_cast<float>(m[Z])) + ", " + String(static_cast<float>(m[W])); }
	operator const char* () const { return ToString().c_str(); }

private:
	T m[4];
};

template<typename T> T Dot(const Vec4<T>& lhs, const Vec4<T>& rhs) { return lhs[X] * rhs[X] + lhs[Y] * rhs[Y] + lhs[Z] * rhs[Z] + lhs[W] * rhs[W]; }
template<typename T> Vec4<T> operator+(const Vec4<T>& lhs, const Vec4<T>& rhs) { return Vec4<T>(lhs[X] + rhs[X], lhs[Y] + rhs[Y], lhs[Z] + rhs[Z], lhs[W] + rhs[W]); }
template<typename T> Vec4<T> operator-(const Vec4<T>& lhs, const Vec4<T>& rhs) { return Vec4<T>(lhs[X] - rhs[X], lhs[Y] - rhs[Y], lhs[Z] - rhs[Z], lhs[W] - rhs[W]); }
template<typename T> Vec4<T> operator*(const Vec4<T>& lhs, const T& rhs) { return Vec4<T>(lhs[X] * rhs, lhs[Y] * rhs, lhs[Z] * rhs, lhs[W] * rhs); }
template<typename T> Vec4<T> operator*(const T& lhs, const Vec4<T>& rhs) { return Vec4<T>(lhs * rhs[X], lhs * rhs[Y], lhs * rhs[Z], lhs * rhs[W]); }
template<typename T> Vec4<T> operator/(const Vec4<T>& lhs, const T& rhs) { return Vec4<T>(lhs[X] / rhs, lhs[Y] / rhs, lhs[Z] / rhs, lhs[W] / rhs); }

#endif

