// Mat4.h

#ifndef _Mat4_h
#define _Mat4_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <FixedPoints.h>
#include <FixedPointsCommon.h>

#include <Vec4.h>
#include <Mat3.h>

template<typename T = SQ15x16>
class Mat4
{
public:
	Mat4() { *this = Identity(); }
	Mat4(const Vec4<T>& c0, const Vec4<T>& c1, const Vec4<T>& c2, const Vec4<T>& c3) { m[0] = c0; m[1] = c1; m[2] = c2; m[3] = c3; }

	Vec4<T>& operator[](const uint8_t i) { return m[i]; }
	const Vec4<T>& operator[](const uint8_t i) const { return m[i]; }

	const String ToString() const { return m[0].ToString() + ",\n" + m[1].ToString() + ",\n" + m[2].ToString() + ",\n" + m[3].ToString(); }
	operator const String() const { return ToString(); }

	Mat4<T> Transpose() const { return { { m[0][0], m[1][0], m[2][0], m[3][0] }, { m[0][1], m[1][1], m[2][1], m[3][1] }, { m[0][2], m[1][2], m[2][2], m[3][2] }, { m[0][3], m[1][3], m[2][3], m[3][3] } }; }
	T Determinant() const {
		return m[0][0] * Mat3<T>({ m[1][1], m[1][2], m[1][3] }, { m[2][1], m[2][2], m[2][3] }, { m[3][1], m[3][2], m[3][3] }).Determinant()
			- m[1][0] * Mat3<T>({ m[0][1], m[0][2], m[0][3] }, { m[2][1], m[2][2], m[2][3] }, { m[3][1], m[3][2], m[3][3] }).Determinant()
			+ m[2][0] * Mat3<T>({ m[0][1], m[0][2], m[0][3] }, { m[1][1], m[1][2], m[1][3] }, { m[3][1], m[3][2], m[3][3] }).Determinant()
			- m[3][0] * Mat3<T>({ m[0][1], m[0][2], m[0][3] }, { m[1][1], m[1][2], m[1][3] }, { m[2][1], m[2][2], m[2][3] }).Determinant();
	}
	Mat4<T> Inverse(const T& Det) const {
		const auto c0 = Vec4<>({
			 Mat3<T>({ m[1][1], m[1][2], m[1][3] }, { m[2][1], m[2][2], m[2][3] }, { m[3][1], m[3][2], m[3][3] }).Determinant(),
			-Mat3<T>({ m[0][1], m[0][2], m[0][3] }, { m[2][1], m[2][2], m[2][3] }, { m[3][1], m[3][2], m[3][3] }).Determinant(),
			 Mat3<T>({ m[0][1], m[0][2], m[0][3] }, { m[1][1], m[1][2], m[1][3] }, { m[3][1], m[3][2], m[3][3] }).Determinant(),
			-Mat3<T>({ m[0][1], m[0][2], m[0][3] }, { m[1][1], m[1][2], m[1][3] }, { m[2][1], m[2][2], m[2][3] }).Determinant() });
		const auto c1 = Vec4<>({ 
			-Mat3<T>({ m[1][0], m[1][2], m[1][3] }, { m[2][0], m[2][2], m[2][3] }, { m[3][0], m[3][2], m[3][3] }).Determinant(),
			 Mat3<T>({ m[0][0], m[0][2], m[0][3] }, { m[2][0], m[2][2], m[2][3] }, { m[3][0], m[3][2], m[3][3] }).Determinant(),
			-Mat3<T>({ m[0][0], m[0][2], m[0][3] }, { m[1][0], m[1][2], m[1][3] }, { m[3][0], m[3][2], m[3][3] }).Determinant(),
			 Mat3<T>({ m[0][0], m[0][2], m[0][3] }, { m[1][0], m[1][2], m[1][3] }, { m[2][0], m[2][2], m[2][3] }).Determinant() });
		const auto c2 = Vec4<>({
			 Mat3<T>({ m[1][0], m[1][1], m[1][3] }, { m[2][0], m[2][1], m[2][3] }, { m[3][0], m[3][1], m[3][3] }).Determinant(),
			-Mat3<T>({ m[0][0], m[0][1], m[0][3] }, { m[2][0], m[2][1], m[2][3] }, { m[3][0], m[3][1], m[3][3] }).Determinant(),
			 Mat3<T>({ m[0][0], m[0][1], m[0][3] }, { m[1][0], m[1][1], m[1][3] }, { m[3][0], m[3][1], m[3][3] }).Determinant(),
			-Mat3<T>({ m[0][0], m[0][1], m[0][3] }, { m[1][0], m[1][1], m[1][3] }, { m[2][0], m[2][1], m[2][3] }).Determinant() });
		const auto c3 = Vec4<>({
			-Mat3<T>({ m[1][0], m[1][1], m[1][2] }, { m[2][0], m[2][1], m[2][2] }, { m[3][0], m[3][1], m[3][2] }).Determinant(),
			 Mat3<T>({ m[0][0], m[0][1], m[0][2] }, { m[2][0], m[2][1], m[2][2] }, { m[3][0], m[3][1], m[3][2] }).Determinant(),
			-Mat3<T>({ m[0][0], m[0][1], m[0][2] }, { m[1][0], m[1][1], m[1][2] }, { m[3][0], m[3][1], m[3][2] }).Determinant(),
			 Mat3<T>({ m[0][0], m[0][1], m[0][2] }, { m[1][0], m[1][1], m[1][2] }, { m[2][0], m[2][1], m[2][2] }).Determinant() });
		return Mat4<>({ c0, c1, c2, c3 }) / Det;
	}

	static Mat4<T> Identity() { return { { 1.0, 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0 } }; }

private:
	Vec4<T> m[4];
};

template<typename T> Mat4<T> operator+(const Mat4<T>& lhs, const Mat4<T>& rhs) { return { lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2], lhs[3] + rhs[3] }; }
template<typename T> Mat4<T> operator-(const Mat4<T>& lhs, const Mat4<T>& rhs) { return { lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2], lhs[3] - rhs[3] }; }
template<typename T> Mat4<T> operator*(const Mat4<T>& lhs, const T& rhs) { return { lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs, lhs[3] * rhs }; }
template<typename T> Mat4<T> operator*(const T& lhs, const Mat4<T>& rhs) { return rhs * lhs; }
template<typename T> Mat4<T> operator/(const Mat4<T>& lhs, const T& rhs) { return lhs * (T(1.0) / rhs); }
template<typename T> Mat4<T> operator*(const Mat4<T>& lhs, const Mat4<T>& rhs) {
	const auto l0 = Vec4<T>({ rhs[0][0], rhs[1][0], rhs[2][0], rhs[3][0] });
	const auto l1 = Vec4<T>({ rhs[0][1], rhs[1][1], rhs[2][1], rhs[3][1] });
	const auto l2 = Vec4<T>({ rhs[0][2], rhs[1][2], rhs[2][2], rhs[3][2] });
	const auto l3 = Vec4<T>({ rhs[0][3], rhs[1][3], rhs[2][3], rhs[3][3] });
	return {
		{ Dot(lhs[0], l0), Dot(lhs[0], l1), Dot(lhs[0], l2), Dot(lhs[0], l3) },
		{ Dot(lhs[1], l0), Dot(lhs[1], l1), Dot(lhs[1], l2), Dot(lhs[1], l3) },
		{ Dot(lhs[2], l0), Dot(lhs[2], l1), Dot(lhs[2], l2), Dot(lhs[2], l3) },
		{ Dot(lhs[3], l0), Dot(lhs[3], l1), Dot(lhs[3], l2), Dot(lhs[3], l3) },
	};
}
template<typename T> Vec4<T> operator*(const Vec4<T>& lhs, const Mat4<T>& rhs) {
	return {
		Dot(lhs, { rhs[0][0], rhs[1][0], rhs[2][0], rhs[3][0] }),
		Dot(lhs, { rhs[0][1], rhs[1][1], rhs[2][1], rhs[3][1] }),
		Dot(lhs, { rhs[0][2], rhs[1][2], rhs[2][2], rhs[3][2] }),
		Dot(lhs, { rhs[0][3], rhs[1][3], rhs[2][3], rhs[3][3] }),
	};
}


#endif

