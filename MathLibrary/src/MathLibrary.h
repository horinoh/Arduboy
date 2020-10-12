/*
 Name:		MathLibrary.h
 Created:	10/12/2020 8:54:15 PM
 Author:	horin
 Editor:	http://www.visualmicro.com
*/

#ifndef _MathLibrary_h
#define _MathLibrary_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Vec2.h>
#include <Vec3.h>
#include <Vec4.h>

#include <Mat2.h>
#include <Mat3.h>
#include <Mat4.h>

#include <Quat.h>

//!< (追加先の)ソリューション右クリック - Add - Existing Project... - MathLibrary.vcxitems を追加する
//!< References右クリック - Add Reference... - MathLibraryにチェック

#endif

