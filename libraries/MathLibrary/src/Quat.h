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
#include <Mat3.h>

template<typename T = SQ7x8>
class Quat
{
public:
	Quat() { *this = Identity(); }
	Quat(const T& x, const T& y, const T& z, const T& w) { m[Component::X] = x; m[Component::Y] = y; m[Component::Z] = z; m[Component::W] = w; }
	Quat(const Mat3<T>& m) {
		auto x = m[0][0] - m[1][1] - m[2][2];
		auto y = m[1][1] - m[0][0] - m[2][2];
		auto z = m[2][2] - m[0][0] - m[1][1];
		const auto w = m[0][0] + m[1][1] + m[2][2];
		auto bigVal = w;
		auto bigComp = Component::W;
		if (x > bigVal) { bigVal = x; bigComp = Component::X; }
		if (y > bigVal) { bigVal = y; bigComp = Component::Y; }
		if (z > bigVal) { bigVal = z; bigComp = Component::Z; }
		bigVal = sqrtFixed(bigVal + 1) * 0.5f;
		const auto tmp = 0.25f / bigVal;
		x = tmp * (m[0][1] - m[1][0]);
		y = tmp * (m[1][2] - m[2][1]);
		z = tmp * (m[2][0] - m[0][2]);
		switch (bigComp)
		{
		default: m[Component::X] = y; m[Component::Y] = z; m[Component::Z] = x; m[Component::W] = bigVal; break;
		case  Component::X: m[Component::X] = bigVal; m[Component::Y] = x; m[Component::Z] = z; m[Component::W] = y; break;
		case  Component::Y: m[Component::X] = x; m[Component::Y] = bigVal; m[Component::Z] = y; m[Component::W] = z; break;
		case  Component::Z: m[Component::X] = z; m[Component::Y] = y; m[Component::Z] = bigVal; m[Component::W] = x; break;
		}
	}

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
		const auto Q = Conjugate() * Quat<T>(v.X(), v.Y(), v.Z(), 0) * *this;
		return Vec3<T>(Q.X(), Q.Y(), Q.Z());
	}
	//ToAxisAngle()

	static constexpr Quat<T> Identity() { return { 0, 0, 0, 1 }; }
	//static constexpr Quat<T> FromPitchYawRoll(const T& p, const T& y, const T& r) {
	//	const auto hp = p * 0.5f;
	//	const auto hy = y * 0.5f;
	//	const auto hr = r * 0.5f;
	//}
	//static constexpr Quat<T> FromTwoVec() {}

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
template<typename T> constexpr Quat<T> operator/(const Quat<T>& lhs, const T& rhs) { return lhs * (1 / rhs); }
template<typename T> constexpr Quat<T> operator*(const Quat<T>& lhs, const Quat<T>& rhs) {
	using namespace Component;
	return Quat<T>(rhs[W] * lhs[X] + rhs[X] * lhs[W] + rhs[Y] * lhs[Z] - rhs[Z] * lhs[Y],
		rhs[W] * lhs[Y] - rhs[X] * lhs[Z] + rhs[Y] * lhs[W] + rhs[Z] * lhs[X],
		rhs[W] * lhs[Z] + rhs[X] * lhs[Y] - rhs[Y] * lhs[X] + rhs[Z] * lhs[W],
		rhs[W] * lhs[W] - rhs[X] * lhs[X] - rhs[Y] * lhs[Y] - rhs[Z] * lhs[Z]);
}

#endif

