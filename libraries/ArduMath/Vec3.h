#ifndef _VEC3_h
#define _VEC3_h

#include "Ardu.h"

#include <FixedPoints.h>
#include <FixedPointsCommon.h>

#include <MathCmn.h>

template<typename T = SQ7x8>
class Vec3
{
public:
	Vec3() { *this = Zero(); }
	Vec3(const T& x, const T& y, const T& z) { m[Component::X] = x; m[Component::Y] = y; m[Component::Z] = z; }

	T& operator[](const uint8_t i) { return m[i]; }
	const T& operator[](const uint8_t i) const { return m[i]; }
	const T& X() const { return m[Component::X]; }
	const T& Y() const { return m[Component::Y]; }
	const T& Z() const { return m[Component::Z]; }

	T LengthSquared() const { return Dot(*this, *this); }
	T Length() const { return sqrtFixed(LengthSquared()); }
	Vec3<T> Normalize() const { return *this / Length(); }

	const String ToString() const {
		return String(static_cast<float>(m[Component::X])) + "," + String(static_cast<float>(m[Component::Y])) + "," + String(static_cast<float>(m[Component::Z]));
	}
	operator const String() const { return ToString(); }

	static constexpr Vec3<T> Zero() { return { 0, 0, 0 }; }
	static constexpr Vec3<T> AxisX() { return { 1, 0, 0 }; }
	static constexpr Vec3<T> AxisY() { return { 0, 1, 0 }; }
	static constexpr Vec3<T> AxisZ() { return { 0, 0, 1 }; }

private:
	T m[3];
};

template<typename T> constexpr T Dot(const Vec3<T>& lhs, const Vec3<T>& rhs) {
	using namespace Component;
	return lhs[X] * rhs[X] + lhs[Y] * rhs[Y] + lhs[Z] * rhs[Z];
}
template<typename T> constexpr Vec3<T> Cross(const Vec3<T>& lhs, const Vec3<T>& rhs) {
	using namespace Component;
	return { lhs[Y] * rhs[Z] - lhs[Z] * rhs[Y], lhs[Z] * rhs[X] - lhs[X] * rhs[Z], lhs[X] * rhs[Y] - lhs[Y] * rhs[X] };
}
template<typename T> constexpr Vec3<T> operator+(const Vec3<T>& lhs, const Vec3<T>& rhs) {
	using namespace Component;
	return { lhs[X] + rhs[X], lhs[Y] + rhs[Y], lhs[Z] + rhs[Z] };
}
template<typename T> constexpr Vec3<T> operator-(const Vec3<T>& lhs, const Vec3<T>& rhs) {
	using namespace Component;
	return { lhs[X] - rhs[X], lhs[Y] - rhs[Y], lhs[Z] - rhs[Z] };
}
template<typename T> constexpr Vec3<T> operator*(const Vec3<T>& lhs, const T& rhs) {
	using namespace Component;
	return { lhs[X] * rhs, lhs[Y] * rhs, lhs[Z] * rhs };
}
template<typename T> constexpr Vec3<T> operator*(const T& lhs, const Vec3<T>& rhs) { rhs * lhs; }
template<typename T> constexpr Vec3<T> operator/(const Vec3<T>& lhs, const T& rhs) { return lhs * (1 / rhs); }


#endif

