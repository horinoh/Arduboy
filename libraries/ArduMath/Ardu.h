#ifndef _ARDU_h
#define _ARDU_h

//!< WProgram.h はバージョンアップで arduino.h に変わっ
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#endif 