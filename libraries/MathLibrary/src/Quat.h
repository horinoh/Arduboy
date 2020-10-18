// Quat.h

#ifndef _Quat_h
#define _Quat_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <FixedPoints.h>
#include <FixedPointsCommon.h>

#include <Common.h>

template<typename T = SQ15x16>
class Quat
{
public:
	Quat() { *this = Identity(); }
	Quat(const T& x, const T& y, const T& z, const T& w) { m[Component::X] = x; m[Component::Y] = y; m[Component::Z] = z; m[Component::W] = w; }

	T& operator[](const uint8_t i) { return m[i]; }
	const T& operator[](const uint8_t i) const { return m[i]; }
	const T& X() const { return m[Component::X]; }
	const T& Y() const { return m[Component::Y]; }
	const T& Z() const { return m[Component::Z]; }
	const T& W() const { return m[Component::W]; }

	T LengthSquared() const { return Dot(*this, *this); }
	T Length() const { return T(sqrt(static_cast<float>(LengthSquared))); } //!< TODO ˆê’Ufloat‚É‚µ‚Äsqrt‚ðŽg—p‚µ‚Ä‚¢‚é
	Quat<T> Normalize() const { return *this / Length(); }

	String ToString() const { 
		return String(static_cast<float>(m[Component::X])) + "," + String(static_cast<float>(m[Component::Y])) + "," + String(static_cast<float>(m[Component::Z])) + "," + String(static_cast<float>(m[Component::W]));
	}
	operator const String() const { return ToString(); }

	static Quat<T> Identity() { return { 0.0, 0.0, 0.0, 1.0f }; }

private:
	T m[4];
};

template<typename T> T Dot(const Quat<T>& lhs, const Quat<T>& rhs) { 
	using namespace Component;
	return lhs[X] * rhs[X] + lhs[Y] * rhs[Y] + lhs[Z] * rhs[Z] + lhs[W] * rhs[W];
}
template<typename T> Quat<T> operator+(const Quat<T>& lhs, const Quat<T>& rhs) { 
	using namespace Component;
	return { lhs[X] + rhs[X], lhs[Y] + rhs[Y], lhs[Z] + rhs[Z], lhs[W] + rhs[W] };
}
template<typename T> Quat<T> operator-(const Quat<T>& lhs, const Quat<T>& rhs) { 
	using namespace Component;
	return { lhs[X] - rhs[X], lhs[Y] - rhs[Y], lhs[Z] - rhs[Z], lhs[W] - rhs[W] };
}
template<typename T> Quat<T> operator*(const Quat<T>& lhs, const T& rhs) {
	using namespace Component;
	return { lhs[X] * rhs, lhs[Y] * rhs, lhs[Z] * rhs, lhs[W] * rhs };
}
template<typename T> Quat<T> operator*(const T& lhs, const Quat<T>& rhs) { return rhs * lhs; }
template<typename T> Quat<T> operator/(const Quat<T>& lhs, const T& rhs) { return lhs * (T(1.0) / rhs); }

#endif

