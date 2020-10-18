// Mat3.h

#ifndef _Mat3_h
#define _Mat3_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <FixedPoints.h>
#include <FixedPointsCommon.h>

#include <Vec3.h>
#include <Mat2.h>

template<typename T = SQ15x16>
class Mat3
{
public:
	Mat3() { *this = Identity(); }
	Mat3(const Vec3<T>& c0, const Vec3<T>& c1, const Vec3<T>& c2) { m[0] = c0; m[1] = c1; m[2] = c2; }

	Vec3<T>& operator[](const uint8_t i) { return m[i]; }
	const Vec3<T>& operator[](const uint8_t i) const { return m[i]; }

	const String ToString() const { return m[0].ToString() + ",\n" + m[1].ToString() + ",\n" + m[2].ToString(); }
	operator const String() const { return ToString(); }

	Mat3<T> Transpose() const { return { { m[0][0], m[1][0], m[2][0] }, { m[0][1], m[1][1], m[2][1] }, { m[0][2], m[1][2], m[2][2] } }; }
	T Determinant() const {
		return m[0][0] * Mat2<T>({ m[1][1], m[1][2] }, { m[2][1], m[2][2] }).Determinant() 
			- m[1][0] * Mat2<T>({ m[0][1], m[0][2] }, { m[2][1], m[2][2] }).Determinant() 
			+ m[2][0] * Mat2<T>({ m[0][1], m[0][2] }, { m[1][1], m[1][2] }).Determinant();
	}
	Mat3<T> Inverse(const T& Det) const {
		const auto c0 = Vec3<>({ 
			 Mat2<T>({ m[1][1], m[1][2]}, { m[2][1], m[2][2] }).Determinant(),
			-Mat2<T>({ m[0][1], m[0][2]}, { m[2][1], m[2][2] }).Determinant(), 
			 Mat2<T>({ m[0][1], m[0][2]}, { m[1][1], m[1][2] }).Determinant() });
		const auto c1 = Vec3<>({
			-Mat2<T>({ m[1][0], m[1][2] }, { m[2][0], m[2][2] }).Determinant(), 
			 Mat2<T>({ m[0][0], m[0][2] }, { m[2][0], m[2][2] }).Determinant(), 
			-Mat2<T>({ m[0][0], m[0][2] }, { m[1][0], m[1][2] }).Determinant() });
		const auto c2 = Vec3<>({ 
			 Mat2<T>({ m[1][0], m[1][1] }, { m[2][0], m[2][1] }).Determinant(), 
			-Mat2<T>({ m[0][0], m[0][1] }, { m[2][0], m[2][1] }).Determinant(),
			 Mat2<T>({ m[0][0], m[0][1] }, { m[1][0], m[1][1] }).Determinant() });
		return Mat3<>({ c0, c1, c2 }) / Det;
	}

	static Mat3<T> Identity() { return { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } }; }

private:
	Vec3<T> m[3];
};

template<typename T> Mat3<T> operator+(const Mat3<T>& lhs, const Mat3<T>& rhs) { return { lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2] }; }
template<typename T> Mat3<T> operator-(const Mat3<T>& lhs, const Mat3<T>& rhs) { return { lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2] }; }
template<typename T> Mat3<T> operator*(const Mat3<T>& lhs, const T& rhs) { return { lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs }; }
template<typename T> Mat3<T> operator*(const T& lhs, const Mat3<T>& rhs) { return rhs * lhs; }
template<typename T> Mat3<T> operator/(const Mat3<T>& lhs, const T& rhs) { return lhs * (T(1.0) / rhs); }
template<typename T> Mat3<T> operator*(const Mat3<T>& lhs, const Mat3<T>& rhs) {
	const auto l0 = Vec3<T>({ rhs[0][0], rhs[1][0], rhs[2][0] });
	const auto l1 = Vec3<T>({ rhs[0][1], rhs[1][1], rhs[2][1] });
	const auto l2 = Vec3<T>({ rhs[0][2], rhs[1][2], rhs[2][2] });
	return {
		{ Dot(lhs[0], l0), Dot(lhs[0], l1), Dot(lhs[0], l2) },
		{ Dot(lhs[1], l0), Dot(lhs[1], l1), Dot(lhs[1], l2) },
		{ Dot(lhs[2], l0), Dot(lhs[2], l1), Dot(lhs[2], l2) },
	};
}
template<typename T> Vec3<T> operator*(const Vec3<T>& lhs, const Mat3<T>& rhs) {
	return { 
		Dot(lhs, { rhs[0][0], rhs[1][0], rhs[2][0] }),
		Dot(lhs, { rhs[0][1], rhs[1][1], rhs[2][1] }), 
		Dot(lhs, { rhs[0][2], rhs[1][2], rhs[2][2] }),
	}; 
}

#endif

