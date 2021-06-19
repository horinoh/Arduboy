#ifndef _MAT3_h
#define _MAT3_h

#include "Ardu.h"

#include <FixedPoints.h>
#include <FixedPointsCommon.h>

#include <Vec3.h>
#include <Mat2.h>
#include <Quat.h>

template<typename T = SQ7x8>
class Mat3
{
public:
	Mat3() { *this = Identity(); }
	Mat3(const Vec3<T>& c0, const Vec3<T>& c1, const Vec3<T>& c2) { m[0] = c0; m[1] = c1; m[2] = c2; }
	/*
	#TODO
	Mat3(const Quat<T>& q) {
		const auto xx = q.X() * q.X();
		const auto yy = q.Y() * q.Y();
		const auto zz = q.Z() * q.Z();
		const auto xy = q.X() * q.Y();
		const auto xz = q.X() * q.Z();
		const auto yz = q.Y() * q.Z();
		const auto wx = q.W() * q.X();
		const auto wy = q.W() * q.Y();
		const auto wz = q.W() * q.Z();
		m[0] = { 1 - 2 * (yy + zz), 2 * (xy + wz), 2 * (xz - wy) };
		m[1] = { 2 * (xy - wz), 1 - 2 * (xx + zz), 2 * (yz + wx) };
		m[2] = { 2 * (xz + wy), 2 * (yz - wx), 1 - 2 * (xx + yy) };
	}
	*/
	Vec3<T>& operator[](const uint8_t i) { return m[i]; }
	const Vec3<T>& operator[](const uint8_t i) const { return m[i]; }

	const String ToString() const { return m[0].ToString() + ",\n" + m[1].ToString() + ",\n" + m[2].ToString(); }
	operator const String() const { return ToString(); }

	constexpr Mat3<T> Transpose() const { return { { m[0][0], m[1][0], m[2][0] }, { m[0][1], m[1][1], m[2][1] }, { m[0][2], m[1][2], m[2][2] } }; }
	constexpr T Determinant() const {
		return m[0][0] * Mat2<T>({ m[1][1], m[1][2] }, { m[2][1], m[2][2] }).Determinant() 
			- m[1][0] * Mat2<T>({ m[0][1], m[0][2] }, { m[2][1], m[2][2] }).Determinant() 
			+ m[2][0] * Mat2<T>({ m[0][1], m[0][2] }, { m[1][1], m[1][2] }).Determinant();
	}
	constexpr Mat3<T> Inverse(const T& Det) const {
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

	static constexpr Mat3<T> Identity() { return { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } }; }
	static constexpr Mat3<T> Scale(const T& s) { return { { s, 0, 0 },{ 0, s, 0 }, { 0, 0, s } }; }
	static constexpr Mat3<T> Scale(const T& x, const T& y, const T& z) { return { { x, 0, 0 }, { 0, y, 0 }, { 0, 0, z } }; }
	static Mat3<T> RotateX(const T& Rad) { 
		const T C(cosFixed(Rad)), S(sinFixed(Rad));
		return { Vec3<T>::AxisX(), { 0, C, S }, { 0, -S, C } };
	} 
	static Mat3<T> RotateY(const T& Rad) {
		const T C(cosFixed(Rad)), S(sinFixed(Rad));
		return { { C, 0, -S }, Vec3<T>::AxisY(), { S, 0, C } };
	}
	static Mat3<T> RotateZ(const T& Rad) {
		const T C(cosFixed(Rad)), S(sinFixed(Rad));
		return { { S, C, 0 }, { -C, S, 0 }, Vec3<T>::AxisZ() };
	}
	static Mat3<T> RotateAxis(const T& Rad, const Vec3<T>& Axis) {
		const T C(cosFixed(Rad)), S(sinFixed(Rad));
		const T C1(1 - C);
		const T XY(Axis.X() * Axis.Y()), YZ(Axis.Y() * Axis.Z()), ZX(Axis.Z() * Axis.X());
		return { 
			{ C + C1 * Axis.X() * Axis.X(), C1 * XY + S * Axis.Z(), C1 * ZX - S * Axis.Y() },
			{ C1 * XY - S * Axis.Z(), C1 * Axis.Y() * Axis.Y + C, C1 * YZ + S * Axis.X() },
			{ C1 * ZX + S * Axis.Y(), C1 * YZ - S * Axis.X(), C1 * Axis.Z() * Axis.Z() + C },
		};
	}

private:
	Vec3<T> m[3];
};

template<typename T> constexpr Mat3<T> operator+(const Mat3<T>& lhs, const Mat3<T>& rhs) { return { lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2] }; }
template<typename T> constexpr Mat3<T> operator-(const Mat3<T>& lhs, const Mat3<T>& rhs) { return { lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2] }; }
template<typename T> constexpr Mat3<T> operator*(const Mat3<T>& lhs, const T& rhs) { return { lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs }; }
template<typename T> constexpr Mat3<T> operator*(const T& lhs, const Mat3<T>& rhs) { return rhs * lhs; }
template<typename T> constexpr Mat3<T> operator/(const Mat3<T>& lhs, const T& rhs) { return lhs * (1 / rhs); }
template<typename T> constexpr Mat3<T> operator*(const Mat3<T>& lhs, const Mat3<T>& rhs) {
	const auto l0 = Vec3<T>({ rhs[0][0], rhs[1][0], rhs[2][0] });
	const auto l1 = Vec3<T>({ rhs[0][1], rhs[1][1], rhs[2][1] });
	const auto l2 = Vec3<T>({ rhs[0][2], rhs[1][2], rhs[2][2] });
	return {
		{ Dot(lhs[0], l0), Dot(lhs[0], l1), Dot(lhs[0], l2) },
		{ Dot(lhs[1], l0), Dot(lhs[1], l1), Dot(lhs[1], l2) },
		{ Dot(lhs[2], l0), Dot(lhs[2], l1), Dot(lhs[2], l2) },
	};
}
template<typename T> constexpr Vec3<T> operator*(const Vec3<T>& lhs, const Mat3<T>& rhs) {
	return { 
		Dot(lhs, { rhs[0][0], rhs[1][0], rhs[2][0] }),
		Dot(lhs, { rhs[0][1], rhs[1][1], rhs[2][1] }), 
		Dot(lhs, { rhs[0][2], rhs[1][2], rhs[2][2] }),
	}; 
}

#endif

