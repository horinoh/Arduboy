// Vec4.h

#ifndef _Vec4_h
#define _Vec4_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <FixedPoints.h>
#include <FixedPointsCommon.h>

#include <Common.h>

template<typename T = SQ15x16>
class Vec4
{
public:
	Vec4() { *this = Zero(); }
	Vec4(const T& x, const T& y, const T& z, const T& w) { m[Component::X] = x; m[Component::Y] = y; m[Component::Z] = z; m[Component::W] = w; }

	T& operator[](const uint8_t i) { return m[i]; }
	const T& operator[](const uint8_t i) const { return m[i]; }
	const T& X() const { return m[Component::X]; }
	const T& Y() const { return m[Component::Y]; }
	const T& Z() const { return m[Component::Z]; }
	const T& W() const { return m[Component::W]; }

	T LengthSquared() const { return Dot(*this, *this); }
	T Length() const { return T(sqrt(static_cast<float>(LengthSquared))); } //!< TODO ˆê’Ufloat‚É‚µ‚Äsqrt‚ðŽg—p‚µ‚Ä‚¢‚é
	Vec4<T> Normalize() const { return *this / Length(); }

	const String ToString() const { 
		return String(static_cast<float>(m[Component::X])) + "," + String(static_cast<float>(m[Component::Y])) + "," + String(static_cast<float>(m[Component::Z])) + "," + String(static_cast<float>(m[Component::W]));
	}
	operator const String() const { return ToString(); }

	static Vec4<T> Zero() { return { 0.0, 0.0, 0.0, 0.0 }; }
	static Vec4<T> AxisX() { return { 1.0, 0.0, 0.0, 0.0 }; }
	static Vec4<T> AxisY() { return { 0.0, 1.0, 0.0, 0.0 }; }
	static Vec4<T> AxisZ() { return { 0.0, 0.0, 1.0, 0.0 }; }
	static Vec4<T> AxisW() { return { 0.0, 0.0, 0.0, 1.0 }; }

private:
	T m[4];
};

template<typename T> T Dot(const Vec4<T>& lhs, const Vec4<T>& rhs) {
	using namespace Component;
	return lhs[X] * rhs[X] + lhs[Y] * rhs[Y] + lhs[Z] * rhs[Z] + lhs[W] * rhs[W];
}
template<typename T> Vec4<T> operator+(const Vec4<T>& lhs, const Vec4<T>& rhs) {
	using namespace Component;
	return { lhs[X] + rhs[X], lhs[Y] + rhs[Y], lhs[Z] + rhs[Z], lhs[W] + rhs[W] };
}
template<typename T> Vec4<T> operator-(const Vec4<T>& lhs, const Vec4<T>& rhs) {
	using namespace Component;
	return { lhs[X] - rhs[X], lhs[Y] - rhs[Y], lhs[Z] - rhs[Z], lhs[W] - rhs[W] };
}
template<typename T> Vec4<T> operator*(const Vec4<T>& lhs, const T& rhs) { 
	using namespace Component;
	return { lhs[X] * rhs, lhs[Y] * rhs, lhs[Z] * rhs, lhs[W] * rhs };
}
template<typename T> Vec4<T> operator*(const T& lhs, const Vec4<T>& rhs) { return rhs * lhs; }
template<typename T> Vec4<T> operator/(const Vec4<T>& lhs, const T& rhs) { return lhs * (T(1.0) / rhs); }

#endif

