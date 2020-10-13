// Vec3.h

#ifndef _Vec3_h
#define _Vec3_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Common.h>
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

template<typename T = SQ15x16>
class Vec3
{
public:
	Vec3() { m[X] = 0.0; m[Y] = 0.0; m[Z] = 0.0; }
	Vec3(const T& xx, const T& yy, const T& zz) { m[X] = xx; m[Y] = yy; m[Z] = zz; }

	T& operator[](const uint8_t i) { return m[i]; }
	const T& operator[](const uint8_t i) const { return m[i]; }
	T& x() { return m[X]; }
	const T& x() const { return m[X]; }
	T& y() { return m[Y]; }
	const T& y() const { return m[Y]; }
	T& z() { return m[Z]; }
	const T& z() const { return m[Z]; }

	T LengthSquared() const { return m[X] * m[X] + m[Y] * m[Y] + m[Z] * m[Z]; }
	T Length() const { return T(sqrt(static_cast<float>(LengthSquared))); } //!< TODO ˆê’Ufloat‚É‚µ‚Äsqrt‚ðŽg—p‚µ‚Ä‚¢‚é
	Vec3<T> Normalize() const { return *this / Length(); }

	String ToString() const { return String(static_cast<float>(m[X])) + ", " + String(static_cast<float>(m[Y])) + ", " + String(static_cast<float>(m[Z])); }
	operator const char* () const { return ToString().c_str(); }

private:
	T m[3];
};

template<typename T> T Dot(const Vec3<T>& lhs, const Vec3<T>& rhs) { return lhs[X] * rhs[X] + lhs[Y] * rhs[Y] + lhs[Z] * rhs[Z]; }
template<typename T> Vec3<T> Cross(const Vec3<T> & lhs, const Vec3<T> & rhs) { return Vec3<T>(lhs[Y] * rhs[Z] - lhs[Z] * rhs[Y], lhs[Z] * rhs[X] - lhs[X] * rhs[Z], lhs[X] * rhs[Y] - lhs[Y] * rhs[X]); }
template<typename T> Vec3<T> operator+(const Vec3<T>& lhs, const Vec3<T>& rhs) { return Vec3<T>(lhs[X] + rhs[X], lhs[Y] + rhs[Y], lhs[Z] + rhs[Z]); }
template<typename T> Vec3<T> operator-(const Vec3<T>& lhs, const Vec3<T>& rhs) { return Vec3<T>(lhs[X] - rhs[X], lhs[Y] - rhs[Y], lhs[Z] - rhs[Z]); }
template<typename T> Vec3<T> operator*(const Vec3<T>& lhs, const T& rhs) { return Vec3<T>(lhs[X] * rhs, lhs[Y] * rhs, lhs[Z] * rhs); }
template<typename T> Vec3<T> operator*(const T& lhs, const Vec3<T>& rhs) { return Vec3<T>(lhs * rhs[X], lhs * rhs[Y], lhs * rhs[Z]); }
template<typename T> Vec3<T> operator/(const Vec3<T>& lhs, const T& rhs) { return Vec3<T>(lhs[X] / rhs, lhs[Y] / rhs, lhs[Z] / rhs); }

#endif

