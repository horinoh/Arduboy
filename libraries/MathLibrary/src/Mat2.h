// Mat2.h

#ifndef _Mat2_h
#define _Mat2_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <FixedPoints.h>
#include <FixedPointsCommon.h>

#include <Vec2.h>

template<typename T = SQ7x8>
class Mat2
{
public:
	Mat2() { *this = Identity(); }
	Mat2(const Vec2<T>& c0, const Vec2<T>& c1) { m[0] = c0; m[1] = c1; }

	Vec2<T>& operator[](const uint8_t i) { return m[i]; }
	const Vec2<T>& operator[](const uint8_t i) const { return m[i]; }

	const String ToString() const { return m[0].ToString() + ",\n" + m[1].ToString(); }
	operator const String() const { return ToString(); }

	constexpr Mat2<T> Transpose() const { return { { m[0][0], m[1][0] }, { m[0][1], m[1][1] } }; }
	constexpr T Determinant() const { return m[0][0] * m[1][1] - m[0][1] * m[1][0]; }
	constexpr Mat2<T> Inverse(const T& Det) const { return Mat2<T>({ m[1][1], -m[0][1] }, { -m[1][0], m[0][0] }) / Det; }

	static constexpr Mat2<T> Identity() { return { { 1, 0 }, { 0, 1 } }; }
	static constexpr Mat2<T> Scale(const T& s) { return { { s, 0 },{ 0, s } }; }
	static constexpr Mat2<T> Scale(const T& x, const T& y) { return { { x, 0 }, { 0, y } }; }
	static Mat2<T> Rotate(const T& Rad) { const T C(cosFixed(Rad)), S(sinFixed(Rad)); return { { C, S }, { -S, C } }; }

private:
	Vec2<T> m[2];
};

template<typename T> constexpr Mat2<T> operator+(const Mat2<T>& lhs, const Mat2<T>& rhs) { return { lhs[0] + rhs[0], lhs[1] + rhs[1] }; }
template<typename T> constexpr Mat2<T> operator-(const Mat2<T>& lhs, const Mat2<T>& rhs) { return { lhs[0] - rhs[0], lhs[1] - rhs[1] }; }
template<typename T> constexpr Mat2<T> operator*(const Mat2<T>& lhs, const T& rhs) { return { lhs[0] * rhs, lhs[1] * rhs }; }
template<typename T> constexpr Mat2<T> operator*(const T& lhs, const Mat2<T>& rhs) { return rhs * lhs; }
template<typename T> constexpr Mat2<T> operator/(const Mat2<T>& lhs, const T& rhs) { return lhs * (1 / rhs); }
template<typename T> constexpr Mat2<T> operator*(const Mat2<T>& lhs, const Mat2<T>& rhs) {
	const auto l0 = Vec2<T>({ rhs[0][0], rhs[1][0] });
	const auto l1 = Vec2<T>({ rhs[0][1], rhs[1][1] });
	return { 
		{ Dot(lhs[0], l0), Dot(lhs[0], l1)}, 
		{ Dot(lhs[1], l0), Dot(lhs[1], l1)} 
	};
}
template<typename T> constexpr Vec2<T> operator*(const Vec2<T>& lhs, const Mat2<T>& rhs) {
	return {
		Dot(lhs, { rhs[0][0], rhs[1][0] }),
		Dot(lhs, { rhs[0][1], rhs[1][1] }),
	};
}

#endif

