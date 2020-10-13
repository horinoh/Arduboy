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

template<typename T = SQ15x16>
class Mat2
{
public:
	Mat2(){}
	Mat2(const Vec2<T>& c0, const Vec2<T>& c1) { m[0] = c0; m[1] = c1; }

	T& operator[](const uint8_t i) { return m[i]; }
	const T& operator[](const uint8_t i) const { return m[i]; }

	String ToString() const { return m[0].ToString() + ",\n" + m[1].ToString(); }
	operator const char* () const { return ToString().c_str(); }

private:
	Vec2<T> m[2];
};

//!< TODO
//Determinant
//Inverse
//Scale
//Translate
//operator*(M, M)
//operator*(V, M) ... transform

#endif

