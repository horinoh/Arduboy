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

template<typename T = SQ7x8>
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
	T Length() const { return sqrtFixed(LengthSquared()); }
	Quat<T> Normalize() const { return *this / Length(); }

	String ToString() const { 
		return String(static_cast<float>(m[Component::X])) + "," + String(static_cast<float>(m[Component::Y])) + "," + String(static_cast<float>(m[Component::Z])) + "," + String(static_cast<float>(m[Component::W]));
	}
	operator const String() const { return ToString(); }

	constexpr Quat<T> Conjugate() const { return Quat<T>(-m[Component::X], -m[Component::Y], -m[Component::Z], m[Component::W]); }
	constexpr Quat<T> Inverse() const { return Conjugate() / Dot(*this, *this); }
	constexpr Vec3<T> Transform(const Vec3<T>& v) const {
		const auto Q = Conjugate() * Quat<T>(v.X(), v.Y(), v.Z(), 0.0f) * *this;
		return Vec3<T>(Q.X(), Q.Y(), Q.Z());
	}

	static constexpr Quat<T> Identity() { return { 0.0f, 0.0f, 0.0f, 1.0f }; }
	//static constexpr Quat<T> FromPitchYawRoll(const T& p, const T& y, const T& r) {
	//	const auto hp = p * 0.5f;
	//	const auto hy = y * 0.5f;
	//	const auto hr = r * 0.5f;
	//}

private:
	T m[4];
};

template<typename T> constexpr T Dot(const Quat<T>& lhs, const Quat<T>& rhs) {
	using namespace Component;
	return lhs[X] * rhs[X] + lhs[Y] * rhs[Y] + lhs[Z] * rhs[Z] + lhs[W] * rhs[W];
}
template<typename T> constexpr Quat<T> operator+(const Quat<T>& lhs, const Quat<T>& rhs) {
	using namespace Component;
	return { lhs[X] + rhs[X], lhs[Y] + rhs[Y], lhs[Z] + rhs[Z], lhs[W] + rhs[W] };
}
template<typename T> constexpr Quat<T> operator-(const Quat<T>& lhs, const Quat<T>& rhs) {
	using namespace Component;
	return { lhs[X] - rhs[X], lhs[Y] - rhs[Y], lhs[Z] - rhs[Z], lhs[W] - rhs[W] };
}
template<typename T> constexpr Quat<T> operator*(const Quat<T>& lhs, const T& rhs) {
	using namespace Component;
	return { lhs[X] * rhs, lhs[Y] * rhs, lhs[Z] * rhs, lhs[W] * rhs };
}
template<typename T> constexpr Quat<T> operator*(const T& lhs, const Quat<T>& rhs) { return rhs * lhs; }
template<typename T> constexpr Quat<T> operator/(const Quat<T>& lhs, const T& rhs) { return lhs * (1.0f / rhs); }
template<typename T> constexpr Quat<T> operator*(const Quat<T>& lhs, const Quat<T>& rhs) {
	using namespace Component;
	return Quat<T>(rhs[W] * lhs[X] + rhs[X] * lhs[W] + rhs[Y] * lhs[Z] - rhs[Z] * lhs[Y],
		rhs[W] * lhs[Y] - rhs[X] * lhs[Z] + rhs[Y] * lhs[W] + rhs[Z] * lhs[X],
		rhs[W] * lhs[Z] + rhs[X] * lhs[Y] - rhs[Y] * lhs[X] + rhs[Z] * lhs[W],
		rhs[W] * lhs[W] - rhs[X] * lhs[X] - rhs[Y] * lhs[Y] - rhs[Z] * lhs[Z]);
}

#endif

