// Quat.h

#ifndef _Quat_h
#define _Quat_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Common.h>
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

template<typename T = SQ15x16>
class Quat
{
public:
	Quat() { m[X] = 0.0; m[Y] = 0.0; m[Z] = 0.0; m[W] = 0.0; }
	Quat(const T& xx, const T& yy, const T& zz, const T& ww) { m[X] = xx; m[Y] = yy; m[Z] = zz; m[W] = ww; }

	T& operator[](const uint8_t i) { return m[i]; }
	const T& operator[](const uint8_t i) const { return m[i]; }
	const T& x() const { return m[X]; }
	const T& y() const { return m[Y]; }
	const T& z() const { return m[Z]; }
	const T& w() const { return m[W]; }

	T LengthSquared() const { return Dot(*this, *this); }
	T Length() const { return T(sqrt(static_cast<float>(LengthSquared))); } //!< TODO ˆê’Ufloat‚É‚µ‚Äsqrt‚ðŽg—p‚µ‚Ä‚¢‚é
	Quat<T> Normalize() const { return *this / Length(); }

	String ToString() const { return String(static_cast<float>(m[X])) + "," + String(static_cast<float>(m[Y])) + "," + String(static_cast<float>(m[Z])) + "," + String(static_cast<float>(m[W])); }
	operator const String() const { return ToString(); }

	static Quat<T> Identity() { return Quat<T>(T(0.0), T(0.0), T(0.0), T(1.0)); }

private:
	T m[4];
};

template<typename T> T Dot(const Quat<T>& lhs, const Quat<T>& rhs) { return lhs[X] * rhs[X] + lhs[Y] * rhs[Y] + lhs[Z] * rhs[Z] + lhs[W] * rhs[W]; }
template<typename T> Quat<T> operator+(const Quat<T>& lhs, const Quat<T>& rhs) { return Quat<T>(lhs[X] + rhs[X], lhs[Y] + rhs[Y], lhs[Z] + rhs[Z], lhs[W] + rhs[W]); }
template<typename T> Quat<T> operator-(const Quat<T>& lhs, const Quat<T>& rhs) { return Quat<T>(lhs[X] - rhs[X], lhs[Y] - rhs[Y], lhs[Z] - rhs[Z], lhs[W] - rhs[W]); }
template<typename T> Quat<T> operator*(const Quat<T>& lhs, const T& rhs) { return Quat<T>(lhs[X] * rhs, lhs[Y] * rhs, lhs[Z] * rhs, lhs[W] * rhs); }
template<typename T> Quat<T> operator*(const T& lhs, const Quat<T>& rhs) { return Quat<T>(lhs * rhs[X], lhs * rhs[Y], lhs * rhs[Z], lhs * rhs[W]); }
template<typename T> Quat<T> operator/(const Quat<T>& lhs, const T& rhs) { return Quat<T>(lhs[X] / rhs, lhs[Y] / rhs, lhs[Z] / rhs, lhs[W] / rhs); }

#endif

