// Vec2.h

#ifndef _Vec2_h
#define _Vec2_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <FixedPoints.h>
#include <FixedPointsCommon.h>

#include <Common.h>

template<typename T = SQ7x8>
class Vec2
{
public:
	Vec2() { *this = Zero(); }
	Vec2(const T& x, const T& y) { m[Component::X] = x; m[Component::Y] = y; }

	T& operator[](const uint8_t i) { return m[i]; }
	const T& operator[](const uint8_t i) const { return m[i]; }
	const T& X() const { return m[Component::X]; }
	const T& Y() const { return m[Component::Y]; }

	T LengthSquared() const { return Dot(*this, *this); }
	T Length() const { return sqrtFixed(LengthSquared()); }
	Vec2<T> Normalize() const { return *this / Length(); }

	const String ToString() const {
		return String(static_cast<float>(m[Component::X])) + "," + String(static_cast<float>(m[Component::Y]));
	}
	operator const String() const { return ToString(); }

	static constexpr Vec2<T> Zero() { return { 0, 0 }; }
	static constexpr Vec2<T> AxisX() { return { 1, 0 }; }
	static constexpr Vec2<T> AxisY() { return { 1, 0 }; }

private:
	T m[2];
};

template<typename T> constexpr T Dot(const Vec2<T>& lhs, const Vec2<T>& rhs) {
	using namespace Component;
	return lhs[X] * rhs[X] + lhs[Y] * rhs[Y];
}
template<typename T> constexpr Vec2<T> operator+(const Vec2<T>& lhs, const Vec2<T>& rhs) {
	using namespace Component;
	return { lhs[X] + rhs[X], lhs[Y] + rhs[Y] };
}
template<typename T> constexpr Vec2<T> operator-(const Vec2<T>& lhs, const Vec2<T>& rhs) {
	using namespace Component;
	return { lhs[X] - rhs[X], lhs[Y] - rhs[Y] };
}
template<typename T> constexpr Vec2<T> operator*(const Vec2<T>& lhs, const T& rhs) {
	using namespace Component;
	return { lhs[X] * rhs, lhs[Y] * rhs };
}
template<typename T> constexpr Vec2<T> operator*(const T& lhs, const Vec2<T>& rhs) { return rhs * lhs; }
template<typename T> constexpr Vec2<T> operator/(const Vec2<T>& lhs, const T& rhs) { return lhs * (1 / rhs); }


#endif

