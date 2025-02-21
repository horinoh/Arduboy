#ifndef _VEC4_h
#define _VEC4_h

#include "Ardu.h"

#include <FixedPoints.h>
#include <FixedPointsCommon.h>

#include <MathCmn.h>

template<typename T = SQ7x8>
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
	T Length() const { return sqrtFixed(LengthSquared()); }
	Vec4<T> Normalize() const { return *this / Length(); }

	const String ToString() const { 
		return String(static_cast<float>(m[Component::X])) + "," + String(static_cast<float>(m[Component::Y])) + "," + String(static_cast<float>(m[Component::Z])) + "," + String(static_cast<float>(m[Component::W]));
	}
	operator const String() const { return ToString(); }

	static constexpr Vec4<T> Zero() { return { 0, 0, 0, 0 }; }
	static constexpr Vec4<T> AxisX() { return { 1, 0, 0, 0 }; }
	static constexpr Vec4<T> AxisY() { return { 0, 1, 0, 0 }; }
	static constexpr Vec4<T> AxisZ() { return { 0, 0, 1, 0 }; }
	static constexpr Vec4<T> AxisW() { return { 0, 0, 0, 1 }; }

private:
	T m[4];
};

template<typename T> constexpr T Dot(const Vec4<T>& lhs, const Vec4<T>& rhs) {
	using namespace Component;
	return lhs[X] * rhs[X] + lhs[Y] * rhs[Y] + lhs[Z] * rhs[Z] + lhs[W] * rhs[W];
}
template<typename T> constexpr Vec4<T> operator+(const Vec4<T>& lhs, const Vec4<T>& rhs) {
	using namespace Component;
	return { lhs[X] + rhs[X], lhs[Y] + rhs[Y], lhs[Z] + rhs[Z], lhs[W] + rhs[W] };
}
template<typename T> constexpr Vec4<T> operator-(const Vec4<T>& lhs, const Vec4<T>& rhs) {
	using namespace Component;
	return { lhs[X] - rhs[X], lhs[Y] - rhs[Y], lhs[Z] - rhs[Z], lhs[W] - rhs[W] };
}
template<typename T> constexpr Vec4<T> operator*(const Vec4<T>& lhs, const T& rhs) {
	using namespace Component;
	return { lhs[X] * rhs, lhs[Y] * rhs, lhs[Z] * rhs, lhs[W] * rhs };
}
template<typename T> constexpr Vec4<T> operator*(const T& lhs, const Vec4<T>& rhs) { return rhs * lhs; }
template<typename T> constexpr Vec4<T> operator/(const Vec4<T>& lhs, const T& rhs) { return lhs * (1 / rhs); }

#endif

